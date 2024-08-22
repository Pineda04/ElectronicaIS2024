#include <Servo.h>

// Variables
int potenciometro = A0;
int botonAbrir = 2;
int botonCerrar = 3;
int pinServo1 = 9;
int pinServo2 = 10;

Servo servo1;
Servo servo2;

void setup() {
  // Aqui inicializo los servos
  servo1.attach(pinServo1);
  servo2.attach(pinServo2);

  // Configuracion de los botones
  pinMode(botonAbrir, INPUT_PULLUP);
  pinMode(botonCerrar, INPUT_PULLUP);
}

void loop() {
  int posicionGrados = 90;
  int posicionGrados2 = 0;
  int estadoPotenciometro = analogRead(potenciometro);
  int estadoBotonAbrir = digitalRead(botonAbrir);
  int estadoBotonCerrar = digitalRead(botonCerrar);

  // Verificacion del boton de abrir
  if (estadoBotonAbrir == LOW) {
    posicionGrados = 0;
  }

  // Verificacion del boton de cerrar
  if (estadoBotonCerrar == LOW) {
    posicionGrados = 180;
  }

  // Potenciometro
  if (estadoBotonAbrir == HIGH && estadoBotonCerrar == HIGH) {
    posicionGrados = map(estadoPotenciometro, 0, 1023, 0, 180);
  }

  servo1.write(posicionGrados);

  posicionGrados2 = 180 - posicionGrados;
  servo2.write(posicionGrados2);

  delay(10);
}
