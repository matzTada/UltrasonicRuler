/*
 * Ultrasonic Ruler 
 * 
 * Check GitHub (https://github.com/matzTada/UltrasonicRuler) for further information.
 * 
 * 2017/3/19 modified by Tada Matz
*/

#include<LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int Trig = 8;
int Echo = 9;
int Duration;
float Distance;

#define BUZZER_PIN 7

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  lcd.begin(16, 2);

  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  float tempDistance = getDistance();
  lcd.setCursor(0, 0);
  lcd.print(tempDistance);
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);

  if (tempDistance > 0) {
    tone(BUZZER_PIN, (int)map(tempDistance, 0, 150, 200, 800));
  }
}

float getDistance() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(1);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(11);
  digitalWrite(Trig, LOW);
  Duration = pulseIn(Echo, HIGH);
  if (Duration > 0) {
    Distance = Duration / 2;
    Distance = Distance * 340 * 100 / 1000000; // ultrasonic speed is 340m/s = 34000cm/s = 0.034cm/us
    Serial.print(Duration);
    Serial.print(" us ");
    Serial.print(Distance);
    Serial.println(" cm");
    return Distance;
  }
  return -1;
}

