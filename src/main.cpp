#define BLYNK_PRINT Serial

#include <Arduino.h>
#include <Servo.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "xLM1h0P7AUhf4fRpzAON8SA_oUA-fGr4";
char ssid[] = "CHRISTIAN_BARAJAS";
char pass[] = "BotLAB2018";

const int potPin = 32;
int potValue = 0;
const int control = 2;
int pos = 0;
int velocidad = 3;

Servo servoDerecha;
Servo servoIzquierda;

void moverServo(); // Prototipo de la función
BLYNK_WRITE(V1);
BLYNK_WRITE(V2);
BLYNK_WRITE(V3);

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  servoDerecha.attach(21);
  servoIzquierda.attach(22);
  if (control == 0) {
    servoDerecha.write(0);
    servoIzquierda.write(0);
  } else if (control == 1) {
      moverServo();
  } else if (control == 2) {
    for (int i = 0; i < 5; i++) {
      moverServo();
    }
  }
}

void loop() {
  Blynk.run();
  //potValue = analogRead(potPin);
  velocidad = map(analogRead(potPin), 0, 4095, 3, 30);
}

void moverServo() {
  for (int i = 0; i < 180; i++) {
    servoDerecha.write(i);
    delay(velocidad); // mínima = 3 máxima = 30
  }
  for (int i = 180; i >= 0; i--) {
    servoDerecha.write(i);
    delay(velocidad); // mínima = 3 máxima = 30
  }
  
  // pos = 0;
  // servoDerecha.write(pos);
  // servoIzquierda.write(pos);
  // delay(velocidad);
  // pos = 1;
  // servoDerecha.write(pos);
  // servoIzquierda.write(pos);
  // delay(velocidad);
  // pos = 2;
  // servoDerecha.write(pos);
  // servoIzquierda.write(pos);
  // delay(velocidad);
  // delay(1000);
  // pos = 180;
  // servoDerecha.write(pos);
  // servoIzquierda.write(pos);
  // delay(1000);
  // pos = 0;
  // servoDerecha.write(pos);
  // servoIzquierda.write(pos);
}

BLYNK_WRITE(V1) {
  int valorSlider1 = param.asInt();
  Serial.println("Slider1: " + String(valorSlider1));
  if (valorSlider1 > 90) {
    moverServo();
  } else {
    servoDerecha.write(valorSlider1);
  }
}

BLYNK_WRITE(V2) {
  int valorSlider2 = param.asInt();
  Serial.println("Slider2: " + String(valorSlider2));
  servoIzquierda.write(valorSlider2);
}

BLYNK_WRITE(V3) {
  velocidad = param.asInt();
  Serial.println("Velocidad: " + String(velocidad));
}

