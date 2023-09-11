#include <Arduino.h>  // Библиотека для работы с Arduino

const int floatSwitchPin = 2; // Пин, к которому подключен поплавковый выключатель (замените на свой пин)
const int relayPin1 = 12;      // Пин для первого реле (открытие и закрытие крана) (замените на свой пин)
const int relayPin2 = 13;      // Пин для второго реле (открытие и закрытие крана) (замените на свой пин)
const int buttonPin = 3;       // Пин, к которому подключена кнопка (замените на свой пин)

const int motor1A = 4;  // Пин для управления мотором 1 (направление A)
const int motor1B = 5;  // Пин для управления мотором 1 (направление B)
const int motor2A = 6;  // Пин для управления мотором 2 (направление A)
const int motor2B = 7;  // Пин для управления мотором 2 (направление B)

bool isRelay1On = false; // Флаг для состояния первого реле (открыто или закрыто)
bool isRelay2On = false; // Флаг для состояния второго реле (открыто или закрыто)
unsigned long startTime = 0; // Время начала программы
unsigned long openTime = 0;  // Время следующего открытия крана
unsigned long closeTime = 0; // Время следующего закрытия крана
bool isOpening = false;      // Флаг для состояния открытия крана

void setup() {
    pinMode(floatSwitchPin, INPUT_PULLUP); // Пин поплавкового выключателя как вход с подтягивающим резистором
    pinMode(relayPin1, OUTPUT); // Настроить пин первого реле как выход (открытие и закрытие крана)
    pinMode(relayPin2, OUTPUT); // Настроить пин второго реле как выход (открытие и закрытие крана)
    pinMode(buttonPin, INPUT_PULLUP); // Настроить пин кнопки как вход с подтягивающим резистором

    // Настроить пины моторов как выходы
    pinMode(motor1A, OUTPUT);
    pinMode(motor1B, OUTPUT);
    pinMode(motor2A, OUTPUT);
    pinMode(motor2B, OUTPUT);

    // Установить начальное время
    startTime = millis();
    openTime = startTime + 240000; // Открыть кран через 240 секунд
}

void loop() {
    // Проверить состояние поплавкового выключателя
    if (digitalRead(floatSwitchPin) == LOW) {
        // Поплавок опущен - есть жидкость

        // Проверить состояние кнопки
        if (digitalRead(buttonPin) == LOW) {
            // Кнопка нажата, переключить состояние первого реле (открытие и закрытие крана)
            isRelay1On = !isRelay1On;
            digitalWrite(relayPin1, isRelay1On ? HIGH : LOW);

            // Подождать, пока кнопка отпущена
            while (digitalRead(buttonPin) == LOW) {
                delay(10);
            }
        }

        // Проверить состояние первого реле (открытие и закрытие крана)
        if (isRelay1On) {
            // Первое реле включено, подождать 240 секунд (4 минуты)
            delay(240000);

            // Выключить первое реле (закрыть кран) и установить флаг
            digitalWrite(relayPin1, LOW);
            isRelay1On = false;
        }

        // Проверить состояние второго реле (открытие и закрытие крана)
        if (isRelay2On) {
            // Второе реле включено, подождать 240 секунд (4 минуты)
            delay(240000);

            // Выключить второе реле (закрыть кран) и установить флаг
            digitalWrite(relayPin2, LOW);
            isRelay2On = false;
        }

        // Проверить время и открыть кран после 240 секунд
        unsigned long currentTime = millis();
        if (currentTime >= openTime && !isOpening) {
            // Открыть кран (включить второе реле)
            digitalWrite(relayPin2, HIGH);
            delay(5000); // Подождать 
            // 5 секунд (держим кран открытым)
            digitalWrite(relayPin2, LOW); // Закрыть кран
            isOpening = true;
            closeTime = currentTime + 140000; // Закрыть кран через 140 секунд
        }

        // Закрыть кран после 140 секунд с момента открытия
        if (currentTime >= closeTime) {
            digitalWrite(relayPin2, HIGH); // Открыть кран
            delay(5000); // Подождать 5 секунд (держим кран открытым)
            digitalWrite(relayPin2, LOW); // Закрыть кран
            isOpening = false;
            openTime = currentTime + 140000; // Открыть кран через 140 секунд
        }
    }
    else {
        // Поплавок поднят - нет жидкости.

        // Выключить реле (открытие и закрытие крана)
        digitalWrite(relayPin1, LOW);
        digitalWrite(relayPin2, LOW);

        // Выключить моторы
        digitalWrite(motor1A, LOW);
        digitalWrite(motor1B, LOW);
        digitalWrite(motor2A, LOW);
        digitalWrite(motor2B, LOW);

        // Остановить программу в бесконечном цикле
        while (true) {
            // Программа остановлена
        }
    }
}
