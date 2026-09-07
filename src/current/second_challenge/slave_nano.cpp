#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>

// --- PINES DEL PUENTE H ---
const int pinA = 5;
const int pinB = 6;

// --- PIN DEL SERVO ---
const int pinServo = 4;
Servo miServo;

#define DIRECCION_ESCLAVO 0x08

void recibirDatosI2C(int cuantosBytes);

void setup() {
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);

  miServo.attach(pinServo);
  miServo.write(90);

  Wire.begin(DIRECCION_ESCLAVO);
  Wire.onReceive(recibirDatosI2C);
}

volatile byte anguloRecibido = 90;
volatile int8_t velRecibida = 0; 
volatile bool actualizarMotores = false;

void loop() {
  if (actualizarMotores) {
    miServo.write(anguloRecibido);

    // LÓGICA DE PUENTE H BIDIRECCIONAL
    if (velRecibida >= 0) {
      // Marcha adelante
      analogWrite(pinA, velRecibida);
      digitalWrite(pinB, LOW);
    } else {
      // Marcha atrás: Invertimos los pines y pasamos el valor a positivo
      digitalWrite(pinA, LOW);
      analogWrite(pinB, -velRecibida); 
    }
    
    actualizarMotores = false;
  }
}

void recibirDatosI2C(int cuantosBytes) {
  if (cuantosBytes >= 2) {
    anguloRecibido = Wire.read();    
    velRecibida = (int8_t)Wire.read(); // Leemos conservando el signo negativo
    actualizarMotores = true; 
  }
}