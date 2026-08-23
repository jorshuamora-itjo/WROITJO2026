#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>

// --- PINES DEL PUENTE H ---
//const int pinPWM = 5;
const int pinA = 5;
const int pinB = 6;

// --- PIN DEL SERVO ---
const int pinServo = 2;
Servo miServo;

// Dirección I2C asignada a este Esclavo
#define DIRECCION_ESCLAVO 0x08


void recibirDatosI2C(int cuantosBytes);
void arrancarSuave();

void setup() {
  // 1. Configuración de pines de control de motor
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);

  // 2. Inicialización del Servo
  miServo.attach(pinServo);
  miServo.write(92); // Centrado inicial

  // 3. Inicialización de la red I2C como Esclavo
  Wire.begin(DIRECCION_ESCLAVO);
  
  // Registrar la función que se ejecutará automáticamente cuando el Amo envíe datos
  Wire.onReceive(recibirDatosI2C);

  // Arrancar motor suavemente al encender
  arrancarSuave();
}

// Variables seguras para interrupciones
volatile byte anguloRecibido = 90;
volatile byte velRecibida = 255;
volatile bool actualizarMotores = false;

void loop() {
  // El loop ahora se encarga de mover la electrónica de forma segura
  if (actualizarMotores) {
    miServo.write(anguloRecibido);
    analogWrite(pinA, velRecibida);
    digitalWrite(pinB, LOW);
    actualizarMotores = false; // Reinicia el aviso
  }
}

// --- FUNCIÓN DE RECEPCIÓN I2C ---
void recibirDatosI2C(int cuantosBytes) {
  if (cuantosBytes >= 2) {
    anguloRecibido = Wire.read();    
    velRecibida = Wire.read(); 
    actualizarMotores = true; // Le avisa al loop() que hay trabajo nuevo
  }
}

// Función de arranque progresivo para evitar picos de corriente
void arrancarSuave() {
  digitalWrite(pinB, LOW);
  for (int vel = 0; vel <= velRecibida; vel ++) {
    analogWrite(pinA, vel);
    delayMicroseconds(3921);
  }
}