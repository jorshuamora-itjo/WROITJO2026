#include <Servo.h>

//Ohhh Servo mi Servo
Servo miServo;

//Ultrasónicos
const int trigIzq = 9, echoIzq = 10;
const int trigDer = 3, echoDer = 2;
const int trigFront = 7, echoFront = 8;

//Se viven quemando
const int in1 = 6;  
const int in2 = 5;

//Constantes del PID
float Kp = 7.0;
float Kd = 10.0;
float Ki = 0.001;

//Variables del PID
float error_anterior = 0;
unsigned long tiempo_anterior = 0;
float suma_errores = 0;
const float LIMITE = 1000.0;

//Rapido y Lento
const int velMax = 255;  
const int velMin = 170;  // Subido a 195 como pediste para la curva agresiva

//Pa que de 3 vueltas
int girosRealizados = 0;
const int giros_max = 12;
bool misionTerminada = false;

//Estados del carrito
const int Inicio = 0;
const int PID = 1;
const int Girando = 2;

int estadoActual = Inicio;

// 'U'=Nosabe, 'I'=Izq, 'D'=Der
char direccionBloqueada = 'U';    
   
const float distanciaLim = 130.0;
const float distanciaHueco = 90.0;

// Memoria para la función tomarEsquinaGradual
int anguloActualInterno = 90;        

// Arreglos globales pal filtro contra el ruido
float historialIzq[4] = {150.0, 150.0, 150.0, 150.0};
float historialDer[4] = {150.0, 150.0, 150.0, 150.0};
float historialFront[4] = {150.0, 150.0, 150.0, 150.0};

void setup() {
  Serial.begin(115200);

  pinMode(trigIzq, OUTPUT); pinMode(echoIzq, INPUT);
  pinMode(trigDer, OUTPUT); pinMode(echoDer, INPUT);
  pinMode(trigFront, OUTPUT); pinMode(echoFront, INPUT);
   pinMode(in1, OUTPUT); pinMode(in2, OUTPUT);

  miServo.attach(11);
  miServo.write(90);

  Serial.println("Si doy tres vueltas guillermo compra una torta");
 
  // Ya entendí el for
  
  Serial.println("Acelerando misil...");
  for (int v = 0; v <= velMax; v += 5) {
    avanzar(v);
    delay(35);
  }
 
  tiempo_anterior = millis();
}

void loop() {
 
  //El ganador ps
  if (misionTerminada == true) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    miServo.write(90);
    while (true) {}
  }

  //Ultrasónicos joseando (ahora con filtro de proteccion)
  float distFront = filtroMediana4(medirDistancia(trigFront, echoFront), historialFront);
  float distIzq = filtroMediana4(medirDistancia(trigIzq, echoIzq), historialIzq);
  float distDer = filtroMediana4(medirDistancia(trigDer, echoDer), historialDer);
  
  //Migración Interna (Cambio de estado)
  switch (estadoActual) {

    case Inicio:
      //Avanza hasta que se encuentre algo
      avanzar(velMax);
      float distFront;
      float distIzq;
      float distDer;
      miServo.write(90);

      if (distFront <= distanciaLim) {
        //Elige pa donde va
        Serial.println("VOY PALAO - Tomando decision permanente");
        if (distIzq > distDer) {
          direccionBloqueada = 'I';
          Serial.println("-> Direccion bloqueada: IZQUIERDA");
        }
        else {
          direccionBloqueada = 'D';
          Serial.println("-> Direccion bloqueada: DERECHA");
        }
        estadoActual = Girando;
      }
      break;

    case PID:
      //Usamos PID porque yo no me maté toda una madrugada pa un coño
      ejecutarControlPID(distIzq, distDer);

      // --- NUEVA LÓGICA DE DETECCIÓN DE HUECOS ---
      // Si la dirección bloqueada es Izquierda y de repente hay un espacio grande a la izquierda
      if (direccionBloqueada == 'I' && distIzq >= distanciaHueco) {
        Serial.println("¡Hueco a la izquierda detectado! Entrando a curva...");
        estadoActual = Girando;
      }
      // Si la dirección bloqueada es Derecha y de repente hay un espacio grande a la derecha
      else if (direccionBloqueada == 'D' && distDer >= distanciaHueco) {
        Serial.println("¡Hueco a la derecha detectado! Entrando a curva...");
        estadoActual = Girando;
      }
      
      // Seguridad opcional: por si acaso el carro entra cruzado y no lee bien el hueco
      else if (distFront <= 40.0) { 
        estadoActual = Girando;
      }
      break;

    case Girando:
      //Giramos (NI MODO QUE VAYA PA ATRAS, SI DICE LA VARIABLE GIRANDO NO VA A SER PORQUE VA A VOLAR)
      ejecutarGiroMecanico();
      break;
  }
  Serial.print("frontal: ");
  Serial.println(distFront);
  Serial.print("izquierda: ");
  Serial.println(distIzq);
  Serial.print("derecha: ");
  Serial.println(distDer);
}

//PID como función pa mantener el orden muchachos
void ejecutarControlPID(float distIzq, float distDer) {

  //Taima (dt)
  unsigned long tiempoActual = millis();
  float dt = (float)(tiempoActual - tiempo_anterior);
  if (dt == 0) dt = 1.0;

  //Error
  float error = distIzq - distDer;

  //Me fume uno viendome 5 videos de esto :(
 
  //Dame la P
  float P = Kp * error;
 
  //Dame la I (Se limita para evitar que de vueltas como trompo)
  suma_errores = suma_errores + (error * dt);
  if (suma_errores > LIMITE) suma_errores = LIMITE;
  else if (suma_errores < -LIMITE) suma_errores = -LIMITE;
  float I = Ki * suma_errores;

  //Dame la D
  float tasa_cambio = (error - error_anterior) / dt;
  float D = Kd * tasa_cambio;
 
  //Que diceeeee: PID :)
  float Salida_PID = P + I + D;
 
  //Se aplica al servo
  int anguloDestino = 90 + Salida_PID;
  anguloDestino = constrain(anguloDestino, 45, 135);
  miServo.write(anguloDestino);
  anguloActualInterno = anguloDestino; // Sincronizamos la memoria del volante

  //Memoria
  error_anterior = error;
  tiempo_anterior = tiempoActual;

  //Velocidad Adaptiva con Limite de Curva
  float magnitudGiro = abs(anguloDestino - 90);
  int velocidadAdaptativa = map(magnitudGiro, 0, 45, velMax, velMin);
  velocidadAdaptativa = constrain(velocidadAdaptativa, velMin, velMax);
  avanzar(velocidadAdaptativa);
  float distFront;
  delay(30);
}

//Funcion pa girar
void ejecutarGiroMecanico() {

  Serial.println("Ejecutando curva de carreras...");

  //Frena primero
  for (int v = velMax; v >= velMin; v -= 5) {
    avanzar(v);
    delay(25);
  }

  //Gira hacia el lado bloqueao
  int anguloGiro = (direccionBloqueada == 'I') ? 135 : 45;
  tomarEsquinaGradual(anguloGiro);
  delay(2500);

  //Regresa a 90
  tomarEsquinaGradual(90);

  //Acelera
  for (int v = velMin; v <= velMax; v += 5) {
    avanzar(v);
    delay(25);
  }

  //Conteo de vueltas
  girosRealizados++;
  Serial.print("Una menos. Giros totales: ");
  Serial.print(girosRealizados);
  Serial.print(" / ");
  Serial.println(giros_max);

  if (girosRealizados >= giros_max) {
    Serial.println("Di tres vueltas valeeee");
    misionTerminada = true;
  } 
  else {
    suma_errores = 0;
    error_anterior = 0;
    tiempo_anterior = millis();
    estadoActual = PID;
  }


  //Reinicio de PID
  suma_errores = 0;
  error_anterior = 0;
  tiempo_anterior = millis(); // Reseteamos el reloj
 
  estadoActual = PID; // Devolvemos el cerebro a la matemática
}

//Servo girando gradualmente
void tomarEsquinaGradual(int anguloDestino) {
  avanzar(velMin);

  if (anguloDestino < anguloActualInterno) {
    for (int pos = anguloActualInterno; pos >= anguloDestino; pos -= 10) {
      miServo.write(pos);
      delay(20);
    }
  }
  else {
    for (int pos = anguloActualInterno; pos <= anguloDestino; pos += 10) {
      miServo.write(pos);
      delay(20);
    }
  }
  anguloActualInterno = anguloDestino;
}

//Funciones normales pues
void avanzar(int velocidad) {
  analogWrite(in1, velocidad);
  digitalWrite(in2, LOW);
}

/*void frenar() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  miServo.write(90);
}*/

float medirDistancia(int pinTrig, int pinEcho) {
  digitalWrite(pinTrig, LOW); delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH); delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  long tiempo = pulseIn(pinEcho, HIGH, 12000);
  if (tiempo == 0) return 150.0;
  return (tiempo * 0.0343) / 2.0;
}

// Filtro de mediana pa proteger contra el ruido
float filtroMediana4(float nuevoValor, float historial[]) {
  for (int i = 0; i < 3; i++) {
    historial[i] = historial[i + 1];
  }
  historial[3] = nuevoValor;
  float copia[4];
  for (int i = 0; i < 4; i++) {
    copia[i] = historial[i];
  }
  // Ordenamiento
  for (int i = 0; i < 3; i++) {
    for (int j = i + 1; j < 4; j++) {
      if (copia[i] > copia[j]) {
        float temp = copia[i];
        copia[i] = copia[j];
        copia[j] = temp;
      }
    }
  }
  // Retorna el promedio de los dos centrales
  return (copia[1] + copia[2]) / 2.0;
}
