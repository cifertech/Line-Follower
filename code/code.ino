#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels(1, 3, NEO_GRB + NEO_KHZ800);

const int sensorPins[5] = {A0, A1, A2, A3, A4}; 

const int leftMotorPin1 = 4;
const int leftMotorPin2 = 5;
const int rightMotorPin1 = 6;
const int rightMotorPin2 = 7;

const int switchPin = A5;

const int buzzer = 2;

bool robotRunning = false;
bool lastSwitchState = HIGH;

void setup() {
  
  pixels.begin();
  
  for (int i = 0; i < 5; i++) {
    pinMode(sensorPins[i], INPUT);
  }

  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(switchPin, INPUT_PULLUP); 

  pinMode(buzzer, OUTPUT);
}

void loop() {
  
  noTone(buzzer);
  int sensorValues[5];

  for (int i = 0; i < 5; i++) {
    sensorValues[i] = digitalRead(sensorPins[i]);
  }

  bool currentSwitchState = digitalRead(switchPin);

  if (currentSwitchState == LOW && lastSwitchState == HIGH) {
    robotRunning = !robotRunning;

    if (robotRunning) {
      Serial.println("Robot started.");
      moveForward();
      pixels.setPixelColor(0, pixels.Color(0, 25, 0));
      pixels.show();
      
    } else {
      stopMotors();
      Serial.println("Robot stopped.");
      pixels.setPixelColor(0, pixels.Color(25, 0, 0));
      pixels.show();
    }
  }

  lastSwitchState = currentSwitchState;

  if (robotRunning) {

    if (sensorValues[0] == HIGH && sensorValues[1] == HIGH && sensorValues[2] == LOW && sensorValues[3] == HIGH && sensorValues[4] == HIGH) {
      moveForward();
      buzer();
    } else if (sensorValues[0] == LOW && sensorValues[1] == HIGH && sensorValues[2] == HIGH && sensorValues[3] == HIGH && sensorValues[4] == HIGH) {
      turnLeftSlightly();
      buzer();
    } else if (sensorValues[0] == HIGH && sensorValues[1] == HIGH && sensorValues[2] == HIGH && sensorValues[3] == HIGH && sensorValues[4] == LOW) {
      turnRightSlightly();
      buzer();
    } else if (sensorValues[0] == HIGH && sensorValues[1] == LOW && sensorValues[2] == HIGH && sensorValues[3] == HIGH && sensorValues[4] == HIGH) {
      turnLeftSlightly();
      buzer();
    } else if (sensorValues[0] == HIGH && sensorValues[1] == HIGH && sensorValues[2] == HIGH && sensorValues[3] == LOW && sensorValues[4] == HIGH) {
      turnRightSlightly();
      buzer();
    }
  } else {
    stopMotors();
  }
}

void moveForward() {
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
}

void turnRightSlightly() {
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, LOW);
}

void turnLeftSlightly() {
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
}

void stopMotors() {
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, LOW);
}

void buzer(){
  tone(buzzer, 1000); 
  delay(100);        
  noTone(buzzer);
  delay(100);
}
