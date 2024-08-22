#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int trigFondo = 8;
int echoFondo = 9;
int trigLado = 10;
int echoLado = 11;
int ledNaranja = 17;
int ledVerde = 16;
int ledRojo = 15;
int buzzer = 14;
float duracionFondo;
float duracionLado;
int distanciaFondo;
int distanciaLado;

void setup() {
  pinMode(trigFondo, OUTPUT);
  pinMode(trigLado, OUTPUT);
  pinMode(echoFondo, INPUT);
  pinMode(echoLado, INPUT);
  pinMode(ledNaranja, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  // Medir distancia al fondo
  digitalWrite(trigFondo, LOW);
  delayMicroseconds(2);
  digitalWrite(trigFondo, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigFondo, LOW);
  duracionFondo = pulseIn(echoFondo, HIGH);
  distanciaFondo = duracionFondo / 58.2;

  // Medir distancia al lado
  digitalWrite(trigLado, LOW);
  delayMicroseconds(2);
  digitalWrite(trigLado, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigLado, LOW);
  duracionLado = pulseIn(echoLado, HIGH);
  distanciaLado = duracionLado / 58.2;

  // Imprimir distancias en el monitor serial
  Serial.print("Distancia al fondo: ");
  Serial.println(distanciaFondo);
  Serial.print("Distancia al lado: ");
  Serial.println(distanciaLado);

  if (distanciaFondo == 12 && distanciaLado == 9) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Felicidades! :D");
    lcd.setCursor(0, 1);
    lcd.print("Lo hiciste bien");

    for (int i = 0; i < 3; i++) {
      digitalWrite(ledRojo, HIGH);
      digitalWrite(ledNaranja, HIGH);
      digitalWrite(ledVerde, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(ledRojo, LOW);
      digitalWrite(ledNaranja, LOW);
      digitalWrite(ledVerde, LOW);
      digitalWrite(buzzer, LOW);
      delay(1000);
    }
    lcd.clear();
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Fondo: ");
    lcd.print(distanciaFondo);
    lcd.print(" cm");
    lcd.setCursor(0, 1);
    lcd.print("Lado:  ");
    lcd.print(distanciaLado);
    lcd.print(" cm");

    digitalWrite(ledNaranja, LOW);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledRojo, LOW);
    digitalWrite(buzzer, LOW);

    if (distanciaFondo <= 8) {
      digitalWrite(ledRojo, HIGH);
      digitalWrite(buzzer, HIGH);
    } else if (distanciaFondo <= 12) {
      digitalWrite(ledRojo, HIGH);
    } else if (distanciaFondo <= 14 && distanciaFondo > 12) {
      digitalWrite(ledVerde, HIGH);
    } else if (distanciaFondo <= 30 && distanciaFondo > 14) {
      digitalWrite(ledNaranja, HIGH);
    }
  }

  delay(200);
}
