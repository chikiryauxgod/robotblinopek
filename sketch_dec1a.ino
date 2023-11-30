#include <Arduino.h>
const int ballValvePin = 2;            // Пин для шарового крана
const int relayStove1Pin = 3;          // Пин для реле первой плиты
const int relayStove2Pin = 4;          // Пин для реле второй плиты
const int relayScrewdriver1Pin = 5;    // Пин для реле первого шуруповерта
const int relayScrewdriver2Pin = 6;   // Пин для реле второго шуруповерта

void setup() {
  pinMode(ballValvePin, OUTPUT);
  pinMode(relayStove1Pin, OUTPUT);
  pinMode(relayStove2Pin, OUTPUT);
  pinMode(relayScrewdriver1Pin, OUTPUT);
  pinMode(relayScrewdriver2Pin, OUTPUT);
}

void operateDevices(int time1, int time2, int time3, int time4, int time5) {
  digitalWrite(relayStove1Pin, HIGH); // Включаем реле для первой плиты
  digitalWrite(relayStove2Pin, HIGH); // Включаем реле для второй плиты
  delay(time1);

  digitalWrite(ballValvePin, HIGH);
  delay(time2);

  digitalWrite(relayScrewdriver1Pin, HIGH); // Включаем реле для первого шуруповерта
  digitalWrite(relayScrewdriver2Pin, HIGH); // Включаем реле для второго шуруповерта
  delay(time3);

  digitalWrite(relayScrewdriver1Pin, LOW); // Выключаем реле для первого шуруповерта
  digitalWrite(relayScrewdriver2Pin, LOW); // Выключаем реле для второго шуруповерта
  delay(time4);

  digitalWrite(relayScrewdriver1Pin, HIGH); // Включаем реле для первого шуруповерта
  digitalWrite(relayScrewdriver2Pin, HIGH); // Включаем реле для второго шуруповерта
  delay(time3);

  digitalWrite(relayScrewdriver1Pin, LOW); // Выключаем реле для первого шуруповерта
  digitalWrite(relayScrewdriver2Pin, LOW); // Выключаем реле для второго шуруповерта
  delay(time4);

  digitalWrite(relayStove1Pin, LOW); // Выключаем реле для первой плиты
  digitalWrite(relayStove2Pin, LOW); // Выключаем реле для второй плиты
  digitalWrite(ballValvePin, LOW);
  delay(time5);
}

void loop() {
  int time1 = 5000; // Пример времени в миллисекундах
  int time2 = 3000;
  int time3 = 2000;
  int time4 = 4000;
  int time5 = 10000;

  operateDevices(time1, time2, time3, time4, time5);
}
