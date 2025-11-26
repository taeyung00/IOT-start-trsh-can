#pragma once

#include "Bluetooth.h"
#include "StringTok.h"
#include "Voltmeter.h"
#include "LightSensor.h"
#include "Led3.h"
#include "ServoMotor.h"
#include "UltrasonicSensor.h"
#include "AirQualitySensor.h"
#include "LiquidCrystalDisplay.h"
#include <Arduino.h>

class ArduinoHub {
public:
  ArduinoHub() {}

  ~ArduinoHub() {}

  void setup() {
    Serial.begin(9600);
    m_Bluetooth.begin(9600);

    m_LiquidCrystalDisplay.startDisplay();

    m_AirQualitySensor.setPort(A0);
    m_ServoMotor.setPort(A1);
    m_ServoMotor2.setPort(A4);
    m_lightSensor.setPort(A2);
    m_voltmeter.setPort(A3);
    m_UltrasonicSensor.setPort(12, 13);
    m_UltrasonicSensor2.setPort(10, 11);

    m_led3.setPort(4, 5, 6);
    m_led3.setup();

    isautoservo = false;
    isautoled = false;
    isautoair = false;
  }

  void btIn(char c) {
    m_stInput.appendString(c);
  }

  String readBluetoothMessage() {
    return m_Bluetooth.readMessage();
  }

  void loopOnce() {
    m_stInput.appendSerial();

    if (m_stInput.hasLine()) {
      Serial.print("수신 명령어: ");
      Serial.println(m_stInput.toString());
      exeCmd();
      m_stInput.empty();
    }

    if (!isautoservo)
      autoControlLid();

    if (!isautoled)
      autoControlLight();

    exeAirQuality();
    delay(100);
  }

protected:
  StringTok m_stInput;
  Voltmeter m_voltmeter;
  LightSensor m_lightSensor;
  Led3 m_led3;
  ServoMotor m_ServoMotor;
  ServoMotor m_ServoMotor2;
  UltrasonicSensor m_UltrasonicSensor;
  UltrasonicSensor m_UltrasonicSensor2;
  AirQualitySensor m_AirQualitySensor;
  LiquidCrystalDisplay m_LiquidCrystalDisplay;
  Bluetooth m_Bluetooth;

  bool isautoservo = false;
  bool isautoled = false;
  bool isautoair = false;

  void exeCmd() {
    String cmd = getToken();
    if (cmd == "get") exeGet();
    else if (cmd == "set") exeSet();
    else printError(cmd);
  }

  void exeGet() {
    String sub = getToken();
    if (sub == "volt") exeVolt();
    else if (sub == "lightstep") exeLightStep();
    else if (sub == "light") exeLight();
    else if (sub == "dist") exeDistance();
    else if (sub == "air") exeAir();
    else if (sub == "full") exeFull();
    else printError(sub);
  }

  void exeSet() {
    String sub = getToken();
    if (sub == "led") exeLed();
    else if (sub == "servo") exeSerVO();
    else printError(sub);
  }

  void exeAir() {
    String sub = getToken();
    if (sub == "on") AirQuality();
    else if (sub == "off") AirQualityStatus();
    else printError(sub);
  }

  void exeSerVO() {
    String sub = getToken();
    if (sub == "on") open();
    else if (sub == "off") close();
    else if (sub == "auto") autoControlLid();
    else printError(sub);
  }

  void exeLed() {
    String col = getToken();
    if (col == "red") execolor("red");
    else if (col == "green") execolor("green");
    else if (col == "blue") execolor("blue");
    else if (col == "cyan") execolor("cyan");
    else if (col == "yellow") execolor("yellow");
    else if (col == "magenta") execolor("magenta");
    else if (col == "white") execolor("white");
    else if (col == "auto") autoControlLight();
    else if (col == "off") execolor("off");
    else printError(col);
  }

  void execolor(String color) {
    isautoled = true;

    if (color == "red") m_led3.turnLed(true, false, false);
    else if (color == "green") m_led3.turnLed(false, true, false);
    else if (color == "blue") m_led3.turnLed(false, false, true);
    else if (color == "cyan") m_led3.turnLed(false, true, true);
    else if (color == "yellow") m_led3.turnLed(true, true, false);
    else if (color == "magenta") m_led3.turnLed(true, false, true);
    else if (color == "white") m_led3.turnLed(true, true, true);
    else if (color == "off") m_led3.turnLed(false, false, false);
    else printError(color);
  }

  void exeFull() {
    long dist = m_UltrasonicSensor2.measureDistance();
    int percent = m_UltrasonicSensor2.FillLevel(dist);
    String s_percent = String(percent);
    Serial.println(s_percent);
    m_Bluetooth.println(s_percent);
  }

  void autoControlLight() {
    isautoled = false;
    m_led3.autoControlLight();
  }

  void autoControlLid() {
    isautoservo = false;
    long dist = m_UltrasonicSensor.measureDistance();
    if (dist > 0 && dist <= 30) {
      m_ServoMotor.open();
      delay(5000);
    } else if (dist > 15) {
      m_ServoMotor.close();
    }
  }

  void open() {
    m_ServoMotor.open();
    isautoservo = true;
  }

  void close() {
    m_ServoMotor.close();
    isautoservo = true;
  }

  void exeVolt() {
    double volt = m_voltmeter.getVolt();
    String result = String(volt, 4);
    Serial.println(result);
    m_Bluetooth.println(result);
  }

  void exeDistance() {
    long dist = m_UltrasonicSensor.measureDistance();
    String result = String(dist) + " cm";
    Serial.println(result);
    m_Bluetooth.println(result);
  }

  void exeLightStep() {
    int LightStep = m_lightSensor.getLightStep();
    String result = String(LightStep);
    Serial.println(result);
    m_Bluetooth.println(result);
  }

  void exeLight() {
    LightType light = m_lightSensor.getLightType();
    Serial.println(m_lightSensor.typeToStr(light));
  }

  void exeAirQuality() {
    float voltage = m_AirQualitySensor.readSensorVoltage();
    float ratio = m_AirQualitySensor.calculateSensorRatio(voltage);
    String status = m_AirQualitySensor.getAirQualityStatus(ratio);

    long dist = m_UltrasonicSensor2.measureDistance();
    int percent = m_UltrasonicSensor2.FillLevel(dist);
    String s_percent = String(percent);

    m_LiquidCrystalDisplay.clearDisplay();
    m_LiquidCrystalDisplay.printAt(0, 0, "   Load: " + s_percent + "%");
    m_LiquidCrystalDisplay.printAt(0, 1, " AQ Ratio: " + status);
  }

  void AirQuality() {
    isautoair = true;
    float voltage = m_AirQualitySensor.readSensorVoltage();
    float ratio = m_AirQualitySensor.calculateSensorRatio(voltage);
    m_Bluetooth.println(String(ratio, 2));
    Serial.println("AQ Ratio: " + String(ratio, 2));
  }

  void AirQualityStatus() {
    float voltage = m_AirQualitySensor.readSensorVoltage();
    float ratio = m_AirQualitySensor.calculateSensorRatio(voltage);
    String status = m_AirQualitySensor.getAirQualityStatus(ratio);
    m_Bluetooth.println(status);
    Serial.println("AQ status: " + status);
  }

  String getToken() {
    return m_stInput.cutToken().toString();
  }

  void printError(const String& tok) {
    if (tok.length() == 0) return;
    Serial.println("wrong command: " + tok);
    m_stInput.empty();
  }
};
