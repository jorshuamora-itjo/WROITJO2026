#include <Servo.h>

// Ohhh Servo mi Servo
Servo miServo;

// Ultrasónicos
const int trigIzq = 9, echoIzq = 10;
const int trigDer = 3, echoDer = 2;
const int trigFront = 7, echoFront = 8;
const int pinA = 5, pinB = 6;

// Maquina de estados
enum EstadoCarro {
  RECTA,
  CURVA
};
EstadoCarro estadoActual = RECTA;

// Control de los tiempos
unsigned long tiempoInicioCurva = 0;
unsigned long tiempoUltimaCurva = 0;
const unsigned long DURACION_GIRO = 2500;   // Tiempo en la curva
const unsigned long COOLDOWN_CURVA = 1500; // Tiempo mínimo en recta
int anguloFijoCurva = 90;                  

// Constantes del PID (Solo se usan en RECTA)
float Kp = 13.0;
float Kd = 15.0;
float Ki = 0.001;

// Variables del PID
float error_anterior = 0, suma_errores = 0;
unsigned long tiempo_anterior = 0;
const float LIMITE = 1000.0;

// Velocidades
const int velMax = 230;
const int velCurva = 200;//velMax * 0.50; 
const int velFreno = 0;

void setup(){
  pinMode(trigIzq, OUTPUT); pinMode(echoIzq, INPUT);
  pinMode(trigDer, OUTPUT); pinMode(echoDer, INPUT);
  pinMode(trigFront, OUTPUT); pinMode(echoFront, INPUT);
 
  miServo.attach(11);
  miServo.write(90);
 
  tiempo_anterior = micros();
  //arrancar();
  avanzar(velMax);
  estadoActual = RECTA;
  delay(1000);
}

void loop(){
  
  avanzar(velMax);

  // Taima (dt)
  unsigned long tiempoActual = micros();
  float dt = (float)(tiempoActual - tiempo_anterior)/1000000;
  if (dt == 0) dt = 1.0;

  // Ultrasónicos 
  float distFront = medirDistancia(trigFront, echoFront);
  float distIzq = medirDistancia(trigIzq, echoIzq);
  float distDer = medirDistancia(trigDer, echoDer);

  //freno
  /*if (distFront < 10){
    alto();
    miServo.write(90);
    delay(750);
    atras(180);
    delay(1500);
    alto();
    delay(750);
  }*/

  // ----------------------------------------------------
  // EVALUAR TRANSICIONES DE ESTADO (Con tiempo y Cooldown)
  // ----------------------------------------------------
  if (estadoActual == RECTA) {
    // Solo puede entrar a curva si ya pasó el tiempo de seguridad desde la última curva
    if ((millis() - tiempoUltimaCurva > COOLDOWN_CURVA) && (distFront <= 90 && distFront >= 30.0)) {
      estadoActual = CURVA;
      tiempoInicioCurva = millis(); // Registramos donde empezó la curva
      
      // Bloqueamos la dirección del giro fijo usando los lados justo antes de doblar
      if (distIzq > distDer && distIzq>=150) {
        anguloFijoCurva = 145; // Curva a la Izquierda
      } else if (distDer > distIzq && distDer>=150){
        anguloFijoCurva = 35;  // Curva a la Derecha
      }
    }
  } 
  else if (estadoActual == CURVA) {
    // Si ya transcurrió el tiempo asignado para el giro fijo, forzamos el regreso a recta
    if (millis() - tiempoInicioCurva > DURACION_GIRO) {
      estadoActual = RECTA;
      tiempoUltimaCurva = millis(); // Registramos cuándo terminó la curva para activar el Cooldown
    }
  }

  float error = 0;

  // ----------------------------------------------------
  // EJECUTAR LÓGICA SEGÚN EL ESTADO ACTUAL
  // ----------------------------------------------------
  switch (estadoActual) {
   
    case RECTA:
      error = distIzq - distDer;
      if (abs(error) < 8.0) error = 0; 
      avanzar(velMax);
      break;

    case CURVA:
      avanzar(velCurva);
      // No calculamos error aquí. Dejamos que el temporizador controle el tiempo.
      break;
  }

  // ----------------------------------------------------
  // CONTROL DEL MOTOR DE DIRECCIÓN (SERVO)
  // ----------------------------------------------------
  int anguloDestino;

  if (estadoActual == CURVA) {
    anguloDestino = anguloFijoCurva;
    
    suma_errores = 0;
    error_anterior = 0;
    delay(60);
  } 
  else {
    // El PID funciona normal
    float P = Kp * error;

    suma_errores = suma_errores + (error * dt);
    if (suma_errores > LIMITE) suma_errores = LIMITE;
    else if (suma_errores < -LIMITE) suma_errores = -LIMITE;
    float I = Ki * suma_errores;

    float tasa_cambio = (error - error_anterior) / dt;
    float D = Kd * tasa_cambio;
   
    float Salida_PID = P + I + D;
    anguloDestino = 90 + Salida_PID;
  }

  // Asegurar límites para el servo
  anguloDestino = constrain(anguloDestino, 35, 145);
  miServo.write(anguloDestino);

  // Memoria para el siguiente ciclo
  error_anterior = error;
  tiempo_anterior = tiempoActual;

} // Fin del loop

// FUNCIONES DE MOTORES Y SENSORES 

void arrancar() {
  for(int vel=0; vel<=velMax; vel++){
    analogWrite(pinA, vel);
    analogWrite(pinB, 0);
    delayMicroseconds(5882);
  }
}

void avanzar(int vel) {
  analogWrite(pinA, vel); 
  digitalWrite(pinB, LOW);
}

void alto() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
}

void atras(int vel) {
  digitalWrite(pinA, LOW);
  analogWrite(pinB, vel);
}

float medirDistancia(int pinTrig, int pinEcho) {
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
 
  long tiempo = pulseIn(pinEcho, HIGH /*30000*/);
  float dist=(tiempo * 0.0343) / 2.0;
  //if (dist == 0.0) dist = 120.0;
 
  dist = constrain(dist, 5.0, 200.0);
  return dist;
}