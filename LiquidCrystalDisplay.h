#pragma once
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//LCD
class LiquidCrystalDisplay {
public:
  LiquidCrystalDisplay(void)
    : m_lcd(0x27, 16, 2)  // 멤버 초기화
  {
  }

  ~LiquidCrystalDisplay() {
  }

  void startDisplay() {
    Wire.begin();       // 추가: Wire 라이브러리 시작
    m_lcd.begin(16, 2);
    m_lcd.backlight();   // 백라이트 켜기 추가
    m_lcd.setCursor(0, 0); //시작 줄
  }

  void printDisplay(const String& str) {
    m_lcd.print(str);
  }

  void clearDisplay() {
    
    delay(1000);
    m_lcd.clear();
  }

  void testPrintAt(void) {
    m_lcd.setCursor(0, 0);
    m_lcd.print("this is test code");
    m_lcd.setCursor(0, 1);
    m_lcd.print("GOOD");
  }

  void printAt(int col, int row, const String& str) {
    m_lcd.setCursor(col, row);
    m_lcd.print(str);
  }

private:
  LiquidCrystal_I2C m_lcd;
};
