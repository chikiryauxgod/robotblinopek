const int waterPin = 9;
const int waterLed = 3;
const int relayPin = 8;
const int relayLed = 13;
void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode (13, OUTPUT);
  digitalWrite(13, HIGH);
  pinMode(9, INPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  int time1 = 5000;
  int time 2 = 3;
  
  int waterSensor = digitalRead(waterPin); 
  if (waterSensor){
    digitalWrite(waterLed, HIGH);
    digitalWrite(relayPin, HIGH);
    delay (time1);
    digitalWrite(relayPin, LOW);
    delay (time1);
  } 
  else {
    digitalWrite (relayLed, LOW);    
    digitalWrite (relayPin, LOW);
    digitalWrite(waterLed, LOW);
    Serial.println("Отсутствие воды! Выключение.");
    
    while (true) {
      
    }
  }

  delay(time2); 
}
