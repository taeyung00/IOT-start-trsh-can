#pragma once

#include <Arduino.h>

//초음파 센서
class UltrasonicSensor {
public:
  UltrasonicSensor(void) {}
  ~UltrasonicSensor() {}

  void setPort(int trigPin, int echoPin) {
    m_trigPin = trigPin;
    m_echoPin = echoPin;
    pinMode(m_trigPin, OUTPUT);
    pinMode(m_echoPin, INPUT);
  }

  long measureDistance(void) const {
    digitalWrite(m_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(m_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_trigPin, LOW);

    long duration = pulseIn(m_echoPin, HIGH);
    long distance = duration * 0.034 / 2;  // 초음파 거리 계산 (cm)

    return distance;
  }

  float FillLevel(float distance) const {
    if (distance <= FULL_DIST) return 100.0;
    else if (distance >= MAX_DIST) return 0.0;
    else return ((MAX_DIST - distance) / (MAX_DIST - FULL_DIST)) * 100.0;
  }


protected:

  int m_trigPin;
  int m_echoPin;
  const float MAX_DIST = 23.0;
  const float FULL_DIST = 10.0;
};



