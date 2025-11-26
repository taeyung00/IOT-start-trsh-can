#pragma once
#include <SoftwareSerial.h>
#include <Arduino.h>

class Bluetooth {
public:
  Bluetooth() : btSerial(2, 3) {} 

  void begin(long baud = 9600) {
    btSerial.begin(baud);
  }

  String readMessage() {
    if (btSerial.available()) {
      String msg = btSerial.readStringUntil('\n');
      msg.trim();
      return msg;
    }
    return "";
  }

  void println(const String& data) {
    btSerial.println(data);
  }

  void print(const String& data) {
    btSerial.print(data);
  }

private:
  SoftwareSerial btSerial;
};
