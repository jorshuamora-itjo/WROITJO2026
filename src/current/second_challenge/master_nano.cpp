#include <Arduino.h>
#include <Wire.h>
#include <NewPing.h>
#include <Pixy2.h>

#define DIRECCION_ESCLAVO 0x08
#define MPU6050_ADDR 0x68
 
// --- PINES DEL BOTÓN DE INICIO ---
#define PIN_BTN_OUT 3
#define PIN_BTN_IN  2

// --- PINES DE SENSORES ULTRASÓNICOS ---
#define MAX_DISTANCE 200
#define TRIG_FRONT 10
#define ECHO_FRONT 9
#define TRIG_DER 8
#define ECHO_DER 7
#define TRIG_IZQ 6
#define ECHO_IZQ 5

NewPing sensorIzq(TRIG_IZQ, ECHO_IZQ, MAX_DISTANCE);
NewPing sensorDer(TRIG_DER, ECHO_DER, MAX_DISTANCE);
NewPing sensorFront(TRIG_FRONT, ECHO_FRONT, MAX_DISTANCE);

// --- PIXYCAM 2 ---
Pixy2 pixy;
const int FIRMA_VERDE = 1; // Pasa por la IZQUIERDA
const int FIRMA_ROJA  = 2; // Pasa por la DERECHA

const int ALTO_MIN_CERCA = 60;  
const int ALTO_MAX_CERCA = 220;

// --- CONFIGURACIÓN DE VELOCIDADES ---
const int VEL_RECTA = 120;   // Velocidad rápida para ir recto
const int VEL_ESQUIVE = 120; // Velocidad reducida para maniobras
const int VEL_CURVA = 120;   // Velocidad para tomar la curva de forma rápida
const int VEL_REVERSA = -100;

// --- CONSTANTES DEL PD Y SENSORES ---
float Kp = 10;  
float Kd = 3;
float error_anterior = 0;  

float distIzqFiltrada = 30.0;
float distDerFiltrada = 30.0;
float distFrontFiltrada = 120.0; // Añadido para la curva

// --- FILTRO ANTI-FALSOS POSITIVOS (DEBOUNCE) ---
int lecturasVerdeConsecutivas = 0;
int lecturasRojaConsecutivas = 0;
const int UMBRAL_CONFIRMACION = 3;

// --- MÁQUINA DE ESQUIVE Y CURVAS ---
enum EstadoEsquive {
  RECTA_NORMAL,
  ESQUIVANDO_IZQ, REBASANDO_IZQ, ENDEREZANDO_IZQ,
  ESQUIVANDO_DER, REBASANDO_DER, ENDEREZANDO_DER,
  GIRANDO_CURVA, COOLDOWN_CURVA, RETROCESO_EMERGENCIA, DETENIDO // NUEVOS ESTADOS DE CURVA
};
EstadoEsquive estadoEsquive = RECTA_NORMAL;

unsigned long tiempoInicioRetroceso = 0;
const unsigned long TIEMPO_RETROCESO_MS = 450;

unsigned long tiempoInicioRebase = 0;
unsigned long tiempoInicioEnderezado = 0;

// PARÁMETROS DE TIEMPO Y SEGURIDAD (ESQUIVE)
const unsigned long TIEMPO_REBASE_MS = 600;        
const unsigned long TIEMPO_MAX_ENDEREZANDO_MS = 200;
const float ANGULO_OBJETIVO_ESQUIVE = 10.0;

// --- PARÁMETROS DE CURVA ---
// --- NUEVO: COOLDOWN DE SENSORES (TIEMPO CIEGO) ---
const unsigned long TIEMPO_CIEGO_SENSORES = 500; // Milisegundos ignorando paredes al salir de curva
const float DIST_DETECCION_CURVA = 65.0;
const float ANGULO_OBJETIVO_CURVA = 65.0;
int direccionGiroCurva = 90;
unsigned long tiempoInicioCooldownCurva = 0;
const unsigned long TIEMPO_COOLDOWN_CURVA = 500;
unsigned long ultimoTiempoCurva = 0;
const unsigned long FRONT_COOLDOWN_CURVA = 2500; // Evita que doble dos veces seguidas

unsigned long ultimoTiempoBloque = 0; // Memoria de la cámara
const unsigned long MEMORIA_PIXY_MS = 1000; // 1 segundo de bloqueo de curva

int confirmacionCurva = 0;
const int UMBRAL_CURVA = 2; // Exige ver la pared 2 veces seguidas antes de girar

int contadorCurvas = 0;
const int TOTAL_CURVAS = 12; // 3 vueltas * 4 esquinas = 12 curvas

// --- GIROSCOPIO ---
float anguloZ_acumulado = 0.0;
float offsetZ = 0.0;
unsigned long tiempo_anterior = 0;
bool giroFuePositivo = true;

float leerGiroscopioZ();
float filtrarLectura(float lecturaCruda, float lecturaAnterior);
void enviarComandosEsclavo(int angulo, int velocidad);

void setup() {
  pinMode(PIN_BTN_OUT, OUTPUT);
  digitalWrite(PIN_BTN_OUT, HIGH);
  pinMode(PIN_BTN_IN, INPUT);

  Wire.begin();
  pixy.init();
  pixy.setLamp(1, 0);

  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B);
  Wire.write(0);    
  Wire.endTransmission(true);

  long sumaZ = 0;
  for(int i = 0; i < 50; i++) {
    sumaZ += leerGiroscopioZ();
    delay(3);
  }
  offsetZ = sumaZ / 50.0;

  while (digitalRead(PIN_BTN_IN) == LOW) {
    delay(20);
  }

  ultimoTiempoBloque = millis(); 
  tiempo_anterior = micros();
}

void loop() {
  // 1. LECTURA Y CÁLCULO DEL GIROSCOPIO
  unsigned long tiempoActualMicros = micros();
  float dt = (float)(tiempoActualMicros - tiempo_anterior) / 1000000.0;
  if (dt <= 0) dt = 0.001;
 
  float giroZ = (leerGiroscopioZ() - offsetZ) / 131.0;

  if (estadoEsquive != RECTA_NORMAL) {
    anguloZ_acumulado += (giroZ * dt);
  }

  // 2. LECTURA Y VALIDACIÓN CONTINUA DE PIXYCAM
  int posXVerde = 0;
  int posXRoja = 0;
  bool verdeEnFrame = false;
  bool rojaEnFrame = false;

  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks) {
    for (int i = 0; i < pixy.ccc.numBlocks; i++) {
      int h = pixy.ccc.blocks[i].m_height;
      if (h >= ALTO_MIN_CERCA && h <= ALTO_MAX_CERCA) {
        if ((pixy.ccc.blocks[i].m_signature == 1 || pixy.ccc.blocks[i].m_signature == 3) && !verdeEnFrame) {
          posXVerde = pixy.ccc.blocks[i].m_x;
          verdeEnFrame = true;
        }
        else if (pixy.ccc.blocks[i].m_signature == FIRMA_ROJA && !rojaEnFrame) {
          posXRoja = pixy.ccc.blocks[i].m_x;
          rojaEnFrame = true;
        }
      }
    }
  }

  if (verdeEnFrame) {
    lecturasVerdeConsecutivas++;
    lecturasRojaConsecutivas = 0;
  } else if (rojaEnFrame) {
    lecturasRojaConsecutivas++;
    lecturasVerdeConsecutivas = 0;
  } else {
    lecturasVerdeConsecutivas = 0;
    lecturasRojaConsecutivas = 0;
  }

  bool verdeConfirmado = (lecturasVerdeConsecutivas >= UMBRAL_CONFIRMACION);
  bool rojaConfirmada  = (lecturasRojaConsecutivas >= UMBRAL_CONFIRMACION);
  bool bloqueCerca = (verdeEnFrame || rojaEnFrame); // Indicador general de objeto

  // 3. LÓGICA DE MOVIMIENTO PROTEGIDA
  int anguloDestino = 90;

  // SELECCIÓN AUTOMÁTICA DE VELOCIDAD SEGÚN EL ESTADO
  int velocidadActual = VEL_ESQUIVE;
  if (estadoEsquive == RECTA_NORMAL) velocidadActual = VEL_RECTA;
  else if (estadoEsquive == GIRANDO_CURVA) velocidadActual = VEL_CURVA;
  else if (estadoEsquive == DETENIDO) velocidadActual = 0; // Apaga los motores
  else if (estadoEsquive == RETROCESO_EMERGENCIA) velocidadActual = VEL_REVERSA; // NUEVO

  switch (estadoEsquive) {
    case RECTA_NORMAL:
      
      if (contadorCurvas >= TOTAL_CURVAS) {
        estadoEsquive = DETENIDO;
        break; 
      }

      // --- LECTURA RÁPIDA DE EMERGENCIA ---
      float rawEmergencia = sensorFront.ping_cm();
      if (rawEmergencia > 0 && rawEmergencia <= 12.0) {
         distFrontFiltrada = rawEmergencia; 
      } else if (rawEmergencia == 0.0) {
         distFrontFiltrada = 3.0; // Si da 0, choca.
      }

      // 1. PRIORIDAD MÁXIMA: Detección de peligro inminente (Ultrasonido)
      if (distFrontFiltrada <= 8.0) {
        estadoEsquive = RETROCESO_EMERGENCIA;
        tiempoInicioRetroceso = millis();
        break; // IMPORTANTE: El break evita que ejecute el resto del código
      }

      // 2. PRIORIDAD MEDIA: Esquive de bloques Pixy
      if (verdeConfirmado) {
        estadoEsquive = ESQUIVANDO_IZQ;
        anguloZ_acumulado = 0.0;
      }
      else if (rojaConfirmada) {
        estadoEsquive = ESQUIVANDO_DER;
        anguloZ_acumulado = 0.0;
      }
      else {
        // 2. COOLDOWN DE PAREDES: ¿Acabamos de salir de una curva?
        if (millis() - ultimoTiempoCurva < TIEMPO_CIEGO_SENSORES) {
            // Ignoramos ultrasonidos y PID. Mantenemos el volante recto.
            anguloDestino = 90;
            error_anterior = 0; // Reseteamos el PID para no arrastrar basura
            
            // Forzamos las variables filtradas a valores neutros
            distIzqFiltrada = 30.0;
            distDerFiltrada = 30.0;
            distFrontFiltrada = 120.0;
        } 
        // 3. SENSORES ACTIVOS: Si ya pasó el cooldown, leemos paredes y hacemos PID
        else {
            // Lectura de los 3 sensores
            float rawIzq = sensorIzq.ping_cm();
            distIzqFiltrada = filtrarLectura(rawIzq, distIzqFiltrada);
            delay(15);
           
            float rawDer = sensorDer.ping_cm();
            distDerFiltrada = filtrarLectura(rawDer, distDerFiltrada);
            delay(15);

            float rawFront = sensorFront.ping_cm();
            distFrontFiltrada = filtrarLectura(rawFront, distFrontFiltrada);
            delay(15);

            bool posibleObstaculo = (millis() - ultimoTiempoBloque < MEMORIA_PIXY_MS);
            bool huecoIzquierda = (distIzqFiltrada > 90.0);
            bool huecoDerecha = (distDerFiltrada > 90.0);

            // Detección de nueva curva
            if (distFrontFiltrada <= 70.0 && distFrontFiltrada > 30.0 && (huecoIzquierda || huecoDerecha) &&
                !posibleObstaculo) {
               
                confirmacionCurva++;
                if (confirmacionCurva >= UMBRAL_CURVA) {
                    estadoEsquive = GIRANDO_CURVA; 
                    anguloZ_acumulado = 0.0;
                    confirmacionCurva = 0; 
                   
                    if (huecoIzquierda) direccionGiroCurva = 35; // Hueco Izq -> Gira Izq
                    else direccionGiroCurva = 145;                 // Hueco Der -> Gira Der
                }
            }
            // Control PID de carril
            else {
              confirmacionCurva = 0; 
              
              float distancia_al_centro = (distDerFiltrada - distIzqFiltrada) / 2.0;
              float error = 0;
              float limitePID = 17.0;

              const float ZONA_AZUL = 4.0;
              if (abs(distancia_al_centro) <= ZONA_AZUL) error = 0;
              else {
                if (distancia_al_centro > 0) error = distancia_al_centro - ZONA_AZUL;
                else error = distancia_al_centro + ZONA_AZUL;
              }

              float P = Kp * error;
              float tasa_cambio = (error - error_anterior) / dt;
              tasa_cambio = constrain(tasa_cambio, -150.0, 150.0);
              float D = Kd * tasa_cambio;
             
              float salidaPID = constrain(P + D, -limitePID, limitePID);
             
              anguloDestino = 90 + salidaPID;
              anguloDestino = constrain(anguloDestino, 45, 135);
             
              error_anterior = error;
            }
        }
      }
      break;

    // --- NUEVO: MANIOBRA DE CURVA ---
    case GIRANDO_CURVA:
      anguloDestino = direccionGiroCurva; // Ángulo máximo físico de dirección
     
      // Monitorea el giroscopio para saber cuándo completó los ~76 grados de la curva
      if (abs(anguloZ_acumulado) >= ANGULO_OBJETIVO_CURVA) {
        estadoEsquive = COOLDOWN_CURVA;
        tiempoInicioCooldownCurva = millis();
        error_anterior = 0;
        contadorCurvas++;
      }
      delay(1000);
      break;

    case COOLDOWN_CURVA:
      anguloDestino = 90; // Mantiene el volante recto al salir de la curva
      if (millis() - tiempoInicioCooldownCurva > TIEMPO_COOLDOWN_CURVA) {
        estadoEsquive = RECTA_NORMAL;
        ultimoTiempoCurva = millis(); // Inicia el bloqueo para no detectar la misma pared
      }
      break;

    // --- MANIOBRA VERDE (ESQUIVE POR IZQUIERDA) ---
    case ESQUIVANDO_IZQ:
      anguloDestino = 145;
      if (anguloZ_acumulado >= ANGULO_OBJETIVO_ESQUIVE && (verdeEnFrame && posXVerde >= 200)) {
        estadoEsquive = REBASANDO_IZQ;
        tiempoInicioRebase = millis();
      }
      else if (!verdeEnFrame && anguloZ_acumulado < (ANGULO_OBJETIVO_ESQUIVE * 0.4)) {
        estadoEsquive = RECTA_NORMAL;
      }
      break;

    case REBASANDO_IZQ:
      anguloDestino = 90;
      if (millis() - tiempoInicioRebase >= TIEMPO_REBASE_MS) {
        estadoEsquive = ENDEREZANDO_IZQ;
        tiempoInicioEnderezado = millis();
        giroFuePositivo = (anguloZ_acumulado > 0);
      }
      break;

    case ENDEREZANDO_IZQ:
      anguloDestino = 35;
      if ((giroFuePositivo ? (anguloZ_acumulado <= 0.0) : (anguloZ_acumulado >= 0.0)) ||
          (millis() - tiempoInicioEnderezado >= TIEMPO_MAX_ENDEREZANDO_MS)) {
        estadoEsquive = RECTA_NORMAL;
        error_anterior = 0;
      }
      break;

    // --- MANIOBRA ROJA (ESQUIVE POR DERECHA) ---
    case ESQUIVANDO_DER:
      anguloDestino = 35;
      if (anguloZ_acumulado <= -ANGULO_OBJETIVO_ESQUIVE && (rojaEnFrame && posXRoja <= 40)) {
        estadoEsquive = REBASANDO_DER;
        tiempoInicioRebase = millis();
      }
      else if (!rojaEnFrame && anguloZ_acumulado > (-ANGULO_OBJETIVO_ESQUIVE * 0.4)) {
        estadoEsquive = RECTA_NORMAL;
      }
      break;

    case REBASANDO_DER:
      anguloDestino = 90;
      if (millis() - tiempoInicioRebase >= TIEMPO_REBASE_MS) {
        estadoEsquive = ENDEREZANDO_DER;
        tiempoInicioEnderezado = millis();
        giroFuePositivo = (anguloZ_acumulado > 0);
      }
      break;

    case ENDEREZANDO_DER:
      anguloDestino = 135;
      if ((giroFuePositivo ? (anguloZ_acumulado <= 0.0) : (anguloZ_acumulado >= 0.0)) ||
          (millis() - tiempoInicioEnderezado >= TIEMPO_MAX_ENDEREZANDO_MS)) {
        estadoEsquive = RECTA_NORMAL;
        error_anterior = 0;
      }
      break;

    case DETENIDO:
      anguloDestino = 90; // Endereza las ruedas
      break;

    case RETROCESO_EMERGENCIA:
    anguloDestino = 90; // Mantiene el volante recto mientras retrocede
    
    // Retrocede durante el tiempo definido (TIEMPO_RETROCESO_MS, actualmente 450ms)
    if (millis() - tiempoInicioRetroceso >= TIEMPO_RETROCESO_MS) {
      estadoEsquive = RECTA_NORMAL;
      // Limpiamos los contadores para que no vuelva a retroceder de inmediato con basura de memoria
      lecturasVerdeConsecutivas = 0; 
      lecturasRojaConsecutivas = 0;
      ultimoTiempoBloque = millis(); 
    }
    break;
  }

  // 4. ENVÍO DE DATOS
  enviarComandosEsclavo(anguloDestino, velocidadActual);
  tiempo_anterior = tiempoActualMicros;
}

void enviarComandosEsclavo(int angulo, int velocidad) {
  Wire.beginTransmission(DIRECCION_ESCLAVO);
  Wire.write((byte)angulo);                  
  Wire.write((int8_t)velocidad); 
  Wire.endTransmission();                    
}

float leerGiroscopioZ() {
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x47);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDR, 2, true);
 
  if (Wire.available() >= 2) {
    int16_t Z = Wire.read() << 8 | Wire.read();
    return (float)Z;
  }
  return 0.0;
}

float filtrarLectura(float lecturaCruda, float lecturaAnterior) {
  if (lecturaCruda == 0.0) {
    lecturaCruda = 200.0; // Forzamos la lectura a la distancia máxima real
  } else if (lecturaCruda <= 2.0) {
    return lecturaAnterior; // Ignoramos solo el ruido por contacto físico o cableado
  }
  
  float alpha = 0.4;
  return (alpha * lecturaCruda) + ((1.0 - alpha) * lecturaAnterior);
}