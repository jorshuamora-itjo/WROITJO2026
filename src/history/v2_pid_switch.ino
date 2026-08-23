#include <Servo.h>



// Ohhh Servo mi Servo 
Servo miServo;

// Ultrasónicos
const int trigIzq = 9, echoIzq = 10;
const int trigDer = 3, echoDer = 2; 
const int trigFront = 7, echoFront = 8;
const int pinA = 5, pinB = 6; 

// --- MÁQUINA DE ESTADOS ---
// Definimos los posibles estados de nuestro carro
enum EstadoCarro {
  RECTA,
  CURVA
};
// Inicializamos el carro en estado de RECTA
EstadoCarro estadoActual = RECTA;

// Constantes del PID
float Kp = 13.0;
float Kd = 15.0; 
float Ki = 0.001;

// Variables del PID
float error_anterior = 0, suma_errores = 0;
unsigned long tiempo_anterior = 0; 
const float LIMITE = 1000.0; 

// Rapido y Lento
//probar lento y rapido
const int velMax = 255;//jugar con la velocidad
const int velCurva = velMax * 0.80;//jugar con la velocidad 
const int velFreno = 0;

// para la curva
const float distIdealCurva = 50.0; 

void setup(){
  pinMode(trigIzq, OUTPUT); pinMode(echoIzq, INPUT);
  pinMode(trigDer, OUTPUT); pinMode(echoDer, INPUT);
  pinMode(trigFront, OUTPUT); pinMode(echoFront, INPUT);

  pinMode(4, OUTPUT);
  pinMode(13, OUTPUT); 
  
  miServo.attach(11); 
  miServo.write(90);
 
  tiempo_anterior = micros();
  //arrancar();
  avanzar(velMax);
}

void loop(){
  // Taima (dt)
  unsigned long tiempoActual = micros();
  float dt = (float)(tiempoActual - tiempo_anterior)/1000000; 
  if (dt == 0) dt = 1.0;

  // Ultrasónicos joseando 
  float distFront = medirDistancia(trigFront, echoFront);
  float distIzq = medirDistancia(trigIzq, echoIzq);
  float distDer = medirDistancia(trigDer, echoDer);

  // ----------------------------------------------------
  // 1. EVALUAR TRANSICIONES DE ESTADO
  // ----------------------------------------------------
  if (distFront > 75.0 || distFront < 40.0){ // jugar con la distancia 
    estadoActual = RECTA;
    digitalWrite(4,1);
    digitalWrite(13,0);
  } else if (distFront <= 75.0 && distFront >= 40.0){ // jugar con la distancia 
    estadoActual = CURVA;
    digitalWrite(4,0);
    digitalWrite(13,1);
  } else { // jugar con la distancia 
    estadoActual = RECTA;
    digitalWrite(4,1);
    digitalWrite(13,0);
  }

  float error = 0;

  // ----------------------------------------------------
  // 2. EJECUTAR LÓGICA SEGÚN EL ESTADO ACTUAL
  // ----------------------------------------------------
  switch (estadoActual) {
    
    case RECTA:
      error = distIzq - distDer;
      // umbral 
      if (abs(error) < 8.0) error = 0; // jugar con el valor del umbral a base la medida del carrro
      avanzar(velMax);
      break;

    case CURVA:
      avanzar(velCurva); 
      if (distIzq > distDer) {
        error = distDer - distIdealCurva;
        //miServo.write (135);
        if (abs(error) < 4.0) error = 0;
      }
      // Si hay más espacio a la derecha, la curva es a la derecha, así que seguimos la pared IZQUIERDA.
      else { 
        error = distIdealCurva - distIzq;
        //miServo.write (45);
        if (abs(error) < 4.0) error = 0;
      }
      break;
  }

  // Dame la P
  float P = Kp * error; 

  // Dame la I (Se limita para evitar que de vueltas como trompo) 
  suma_errores = suma_errores + (error * dt);
  if (suma_errores > LIMITE) suma_errores = LIMITE; 
  else if (suma_errores < -LIMITE) suma_errores = -LIMITE;
  float I = Ki * suma_errores; 

  // Dame la D
  float tasa_cambio = (error - error_anterior) / dt;
  float D = Kd * tasa_cambio; 
 
  // Que diceeeee: PID :)
  float Salida_PID = P + I + D;

  // Se aplica al servo 
  int anguloDestino = 90 + Salida_PID;
  anguloDestino = constrain(anguloDestino, 45, 135);
  miServo.write(anguloDestino);

  // Memoria
  error_anterior = error;
  tiempo_anterior = tiempoActual;

  // Velocidad Adaptiva con Limite de Curva
  float magnitudGiro = abs(anguloDestino - 90);
} // Fin del loop 

// motor
void arrancar() {
  for(int vel=0; vel<=velMax; vel++){
    analogWrite(pinA, vel);
    analogWrite(pinB, 0);
    delayMicroseconds(5882);
  } 
}

void avanzar(int vel) {
  analogWrite(pinA, vel); // aqui cambie HIGH por vel, si se pone gay le dejo el HIGH
  digitalWrite(pinB, LOW);
} 

void alto() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
}

// sensores ultramaricos se deberian llamar
float medirDistancia(int pinTrig, int pinEcho) {
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2); 
  digitalWrite(pinTrig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  
  long tiempo = pulseIn(pinEcho, HIGH, 30000);//probar sin el 30000
  float dist=(tiempo * 0.0343) / 2.0;
  if (dist == 0.0)dist = 100.0;
 
  dist = constrain(dist, 5.0, 100.0);//ver que pasa si se sube el limite minimo
  return dist;
}
