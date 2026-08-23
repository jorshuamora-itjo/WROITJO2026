//Librería
#include <Servo.h>

//Ohhh Servo mi Servo
Servo miServo;

//Ultrasónicos
const int trigIzq = 5, echoIzq = 4;
const int trigDer = 3, echoDer = 2;
const int trigFront = 7, echoFront = 6;

//Se viven quemando
//const int ena = 8;
const int in1 = 10;  
const int in2 = 9;

//Constantes del PID
float Kp = 1.5;
float Kd = 100.0;
float Ki = 0.001;

//Variables del PID
float error_anterior = 0;
unsigned long tiempo_anterior = 0;
float suma_errores = 0;
const float LIMITE = 1000.0;

//Rapido y Lento
const int velMax = 200;  
const int velMin = 140;  

//Pa que de 3 vueltas
int girosRealizados = 0;
const int giros_max = 12;
bool misionTerminada = false;
bool enCurva = false;

void setup() {
  Serial.begin(115200);

  pinMode(trigIzq, OUTPUT); pinMode(echoIzq, INPUT);
  pinMode(trigDer, OUTPUT); pinMode(echoDer, INPUT);
  pinMode(trigFront, OUTPUT); pinMode(echoFront, INPUT);
  //pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT); pinMode(in2, OUTPUT);

  miServo.attach(11);
  miServo.write(90);

  Serial.println("Si doy tres vueltas guillermo compra una torta");
 
  avanzar(255);
  delay(200);
 
  tiempo_anterior = millis();
}

void loop() {
 
  //El ganador ps
  if (misionTerminada) {
    frenar();
    return;
  }

  //Taima (dt)
  unsigned long tiempoActual = millis();
  float dt = (float)(tiempoActual - tiempo_anterior);
  if (dt == 0) dt = 1.0;

  //Ultrasónicos joseando
  float distFront = medirDistancia(trigFront, echoFront);
  float distIzq = medirDistancia(trigIzq, echoIzq);
  float distDer = medirDistancia(trigDer, echoDer);

  //Error
  float error = distIzq - distDer;

  //Conteo de las vueltas dadas
  int velMaxPermitida = velMax;

  if (distFront <= 30.0) {
    frenar ();
    return;
  }

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

  //Memoria
  error_anterior = error;
  tiempo_anterior = tiempoActual;

  //Velocidad Adaptiva con Limite de Curva
  float magnitudGiro = abs(anguloDestino - 90);
  //Cantamos la zona con la velocidad permitida actual
  int velocidadAdaptativa = map(magnitudGiro, 0, 45, velMaxPermitida, velMin);
  velocidadAdaptativa = constrain(velocidadAdaptativa, velMin, velMaxPermitida);
  avanzar(velocidadAdaptativa);

  delay(30);
}

//Funciones
void avanzar(int velocidad) {
  //analogWrite(ena, velocidad);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void frenar() {
  //digitalWrite(ena, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  miServo.write(90);
}

float medirDistancia(int pinTrig, int pinEcho) {
  digitalWrite(pinTrig, LOW); delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH); delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  long tiempo = pulseIn(pinEcho, HIGH, 12000);
  if (tiempo == 0) return 150.0;
  return (tiempo * 0.0343) / 2.0;
}
