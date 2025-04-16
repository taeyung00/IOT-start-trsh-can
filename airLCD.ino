#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int sensorPin = A0;
float R0 = 10.0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  // 센서 초기 보정
  float sensorSum = 0;
  for (int i = 0; i < 100; i++) {
    sensorSum += analogRead(sensorPin);
    delay(50);
  }
  float avgVal = sensorSum / 100.0;
  float voltage = avgVal * (5.0 / 1023.0);
  float sensorResistance = ((5.0 - voltage) / voltage) * 10.0;
  R0 = sensorResistance / 3.6;

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Trashcan");
  delay(2000);
  lcd.clear();
}

void loop() {
  int value = analogRead(sensorPin);
  float voltage = value * (5.0 / 1023.0);
  float sensorResistance = ((5.0 - voltage) / voltage) * 10.0;
  float ratio = sensorResistance / R0;

  String statusText;
  if (ratio > 4.0) {
    statusText = "Very Clean";
  } else if (ratio > 2.5) {
    statusText = "Good";
  } else if (ratio > 1.5) {
    statusText = "Caution";
  } else {
    statusText = "Ventilate!";
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AQ Ratio:");
  lcd.print(ratio, 2);

  lcd.setCursor(0, 1);
  lcd.print(statusText);

  delay(2000);
}
