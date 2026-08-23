#include <Arduino.h>
#include <Wire.h>
#include <NewPing.h>

#define DIRECCION_ESCLAVO 0x08
#define MPU6050_ADDR 0x68 // Dirección I2C del giroscopio

// --- PINES DE SENSORES ULTRASÓNICOS ---
#define MAX_DISTANCE 200

#define TRIG_FRONT 11
#define ECHO_FRONT 10
#define TRIG_DER 9
#define ECHO_DER 8 
#define TRIG_IZQ 7
#define ECHO_IZQ 6

NewPing sensorIzq(TRIG_IZQ, ECHO_IZQ, MAX_DISTANCE);
NewPing sensorDer(TRIG_DER, ECHO_DER, MAX_DISTANCE);
NewPing sensorFront(TRIG_FRONT, ECHO_FRONT, MAX_DISTANCE);

// --- MÁQUINA DE ESTADOS ---
enum EstadoCarro { RECTA, CURVA, COOLDOWN };
EstadoCarro estadoActual = RECTA;

// *** PARÁMETROS A CALIBRAR EN PISTA ***
const float DIST_DETECCION_FRONT = 75.0; 
const float ANGULO_OBJETIVO = 72.0; 
const unsigned long TIEMPO_COOLDOWN = 1200; 

unsigned long tiempoInicioCooldown = 0;
int direccionGiroActual = 90;

// --- VARIABLES DEL GIROSCOPIO ---
float anguloZ_acumulado = 0.0;
float offsetZ = 0.0; 

// --- CONSTANTES DEL PD ---
float Kp = 10.33;  
float Kd = 14.0;  
float error_anterior = 0;   
unsigned long tiempo_anterior = 0; 

// --- MEMORIA DE SENSORES PARA FILTRADO ---
float distIzqFiltrada = 30.0;
float distDerFiltrada = 30.0;
float distFrontFiltrada = 120.0;

// Velocidades
const int velCrucero = 220; 
const int velCurva = 200; 

int sentidoPista = 0;

float leerGiroscopioZ();
float filtrarLectura(float lecturaCruda, float lecturaAnterior);

void setup() {
  pinMode(TRIG_IZQ, OUTPUT); pinMode(ECHO_IZQ, INPUT);   
  pinMode(TRIG_DER, OUTPUT); pinMode(ECHO_DER, INPUT);   
  pinMode(TRIG_FRONT, OUTPUT); pinMode(ECHO_FRONT, INPUT);

  Wire.begin(); 
  
  // Despertar y configurar el MPU6050
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);

  // Calibración inicial rápida del Giroscopio
  long sumaZ = 0;
  for(int i = 0; i < 50; i++) {
    sumaZ += leerGiroscopioZ();
    delay(3);
  }
  offsetZ = sumaZ / 50.0;

  tiempo_anterior = micros(); 
}

void enviarComandosEsclavo(int angulo, int velocidad); 

void loop() {
  unsigned long tiempoActualMicros = micros(); 
  float dt = (float)(tiempoActualMicros - tiempo_anterior) / 1000000.0; 
  if (dt <= 0) dt = 0.001; 

  // 1. LECTURA Y FILTRADO EN TIEMPO REAL (Con pausas anti-interferencia)
  if (estadoActual == RECTA) {
    float rawFront = sensorFront.ping_cm();
    distFrontFiltrada = filtrarLectura(rawFront, distFrontFiltrada);
    delay(20);
  }

  if (estadoActual == RECTA || estadoActual == COOLDOWN) {
    float rawIzq = sensorIzq.ping_cm();
    distIzqFiltrada = filtrarLectura(rawIzq, distIzqFiltrada);
    delay(25); 
    
    float rawDer = sensorDer.ping_cm();
    distDerFiltrada = filtrarLectura(rawDer, distDerFiltrada);
    delay(25);
  }

  // 2. MÁQUINA DE ESTADOS
  if (estadoActual == RECTA) {
    if (distFrontFiltrada <= DIST_DETECCION_FRONT) {
      estadoActual = CURVA;
      anguloZ_acumulado = 0.0; 

      // --- LA MAGIA DE LA MEMORIA ---
      // ¿Es la primera curva de la pista? (sentidoPista == 0)
      if (sentidoPista == 0) {
        delay(20);
        float izqDirecto = sensorIzq.ping_cm();
        if (izqDirecto <= 0.0) izqDirecto = 180.0; 

        delay(25);
        float derDirecto = sensorDer.ping_cm();
        if (derDirecto <= 0.0) derDirecto = 180.0; 

        // Decidimos y BLOQUEAMOS la memoria para el resto del reto
        if (izqDirecto > derDirecto) {
          sentidoPista = 65;  // Circuito Antihorario
        } else {
          sentidoPista = 115; // Circuito Horario
        }
      }

      // El auto ahora siempre girará hacia donde dicte la memoria
      direccionGiroActual = sentidoPista;
    }
  }
  else if (estadoActual == CURVA) {
    float giroZ = (leerGiroscopioZ() - offsetZ) / 131.0; 
    anguloZ_acumulado += (giroZ * dt);

    if (abs(anguloZ_acumulado) >= ANGULO_OBJETIVO) {
      estadoActual = COOLDOWN;
      tiempoInicioCooldown = millis();
      error_anterior = 0; 
      
      // Reseteo de memoria para el nuevo carril
      float rawIzq = sensorIzq.ping_cm();
      distIzqFiltrada = (rawIzq <= 0.0) ? 30.0 : rawIzq;
      
      delay(20);
      
      float rawDer = sensorDer.ping_cm();
      distDerFiltrada = (rawDer <= 0.0) ? 30.0 : rawDer;
    }
  }
  else if (estadoActual == COOLDOWN) {
    if (millis() - tiempoInicioCooldown > TIEMPO_COOLDOWN) {
      estadoActual = RECTA;
    }
  }

  // 3. CÁLCULO DE MOVIMIENTO
  int anguloDestino = 92;
  int velocidadActual = velCrucero;

  if (estadoActual == CURVA) {
    anguloDestino = direccionGiroActual;
    velocidadActual = velCurva;
  } 
  else {
    // PID RECTA CON DISTANCIAS FILTRADAS
    float distancia_al_centro = (distDerFiltrada - distIzqFiltrada) / 2.0; 
    const float ZONA_AZUL = 5; 
    float error = 0; 

    if (abs(distancia_al_centro) <= ZONA_AZUL) {
      error = 0; 
    } else {
      if (distancia_al_centro > 0) error = distancia_al_centro - ZONA_AZUL; 
      else error = distancia_al_centro + ZONA_AZUL; 
    }

    float P = Kp * error; 
    float tasa_cambio = (error - error_anterior) / dt; 
    
    tasa_cambio = constrain(tasa_cambio, -150.0, 150.0);
    float D = Kd * tasa_cambio; 
    
    float salidaPID = P + D; 
    salidaPID = constrain(salidaPID, -15.0, 15.0); 
    
    anguloDestino = 92 + salidaPID; 
    anguloDestino = constrain(anguloDestino, 57, 127); 
    
    velocidadActual = velCrucero;
    error_anterior = error; 
  }

  enviarComandosEsclavo(anguloDestino, velocidadActual);
  tiempo_anterior = tiempoActualMicros; 
}

// --- FUNCIÓN DE FILTRADO REVISADA ---
float filtrarLectura(float lecturaCruda, float lecturaAnterior) {
  // Si da 0 o más de 180 cm, asumimos espacio abierto
  float lecturaProcesada = lecturaCruda;
  if (lecturaCruda <= 0.0) {
    lecturaProcesada = 180.0;
  }

  // Si detectamos espacio abierto (> 70 cm), permitimos que el filtro reaccione
  // rápido para no ignorar las aperturas de las esquinas
  if (lecturaProcesada > 70.0) {
    return lecturaProcesada; 
  }

  // Para ajustes finos cerca de muros, aplicamos el suavizado EMA
  float alpha = 0.4;
  return (alpha * lecturaProcesada) + ((1.0 - alpha) * lecturaAnterior);
}

void enviarComandosEsclavo(int angulo, int velocidad) {
  Wire.beginTransmission(DIRECCION_ESCLAVO); 
  Wire.write((byte)angulo);                   
  Wire.write((byte)velocidad);                
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