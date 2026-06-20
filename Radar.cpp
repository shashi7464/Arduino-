#include <Servo.h>

Servo radarServo;

const int trigPin = 2;
const int echoPin = 3;
const int servoPin = 4;
const int buzzerPin = 5;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  radarServo.attach(servoPin);

  Serial.begin(9600);
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  return duration * 0.034 / 2;
}

void loop() {

  for (int angle = 0; angle <= 180; angle++) {
    radarServo.write(angle);
    delay(15);

    distance = getDistance();

    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print("  Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance > 0 && distance < 30) {
      tone(buzzerPin, 1000);   
    } else {
      noTone(buzzerPin);
    }
  }


  for (int angle = 180; angle >= 0; angle--) {
    radarServo.write(angle);
    delay(15);

    distance = getDistance();

    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print("  Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance > 0 && distance < 30) {
      tone(buzzerPin, 1000);
    } else {
      noTone(buzzerPin);
    }
  }
}