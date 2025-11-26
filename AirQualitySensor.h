#pragma once
#include <Arduino.h>
#include "Voltmeter.h"

// 공기질
class AirQualitySensor : public Voltmeter {
public:
  AirQualitySensor(void) {}
  ~AirQualitySensor() {}

  // 센서 핀 설정 및 보정 값 추출
  void setPort(int airQualityPin) {
    m_airQualityPin = airQualityPin;
    calibrateSensor();
  }

  // 초기 보정 : 핀 전압을 100회 측정 후 보정 값(m_ro) 추출  
  float calibrateSensor() {
    float sensorSum = 0;

    for (int i = 0; i < 100; i++) {
      sensorSum += analogRead(m_airQualityPin);
      delay(50);
    }

    float avgVal = sensorSum / 100.0;
    float R0_voltage = avgVal * (5.0 / 1023.0);
    float sensorResistance = ((5.0 - R0_voltage) / R0_voltage) * 10.0;
    m_R0 = sensorResistance;

    return m_R0;
  }

  // 센서 전압 읽기 
  float readSensorVoltage() {
    int value = analogRead(m_airQualityPin);
    float voltage = value * (5.0 / 1023.0);
    return voltage;
  }

  // 전압 비율 계산 : 공식(Rs/R0) 비율이 낮을수록 오염 심함
  float calculateSensorRatio(float voltage) {
    float sensorResistance = ((5.0 - voltage) / voltage) * 10.0;
    float ratio = sensorResistance / m_R0; // (Rs/R0)
    return ratio;
  }

  // 상태 표시
  String getAirQualityStatus(float ratio) {
    if (ratio > 2.0) {
      return "Clean";
    } else if (ratio >= 1.0) {
      return "Good";
    } else if (ratio > 0.5) {
      return "Warn";
    } else {
      return "Vent";
    }
  }

private:
  int m_airQualityPin;
  float m_R0 = 10.0;
};
