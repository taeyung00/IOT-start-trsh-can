#include "Arduino.h"
#pragma once

#define DEF_RLED_PORT	(2)
#define DEF_GLED_PORT	(3)
#define DEF_BLED_PORT	(4)
//LED
class Led3 : public LightSensor
{
public:
	Led3(void)
	{
		setPort(DEF_RLED_PORT, DEF_GLED_PORT, DEF_BLED_PORT);
	}
	~Led3()	{}

 // 1. 자동 조도 제어: 조도 단계별 RGB LED 색상
 void autoControlLight() {
    LightType lt = getLightType();
    switch (lt) {
      case LightType::BRIGHT:  turnLed(false, false, false);  break;  // off
      case LightType::AMBIENT: turnLed(true, true, false); break;  // YELLOW
      case LightType::DARK:    turnLed(false, false, true); break;  // BLUE
    }
  }

	void setPort(int nPortR, int nPortG, int nPortB)
	{
		m_nPortR = nPortR;
		m_nPortG = nPortG;
		m_nPortB = nPortB;
	}

	void setup(void)
	{
		pinMode(m_nPortR, OUTPUT);
		pinMode(m_nPortG, OUTPUT);
		pinMode(m_nPortB, OUTPUT);
	}

	void turnLed(bool bR, bool bG, bool bB)
	{
		digitalWrite(m_nPortR, (bR) ? HIGH : LOW); // bR�� true�̸�, HIGH; bR�� false�̸� LOW
		digitalWrite(m_nPortG, (bG) ? HIGH : LOW);
		digitalWrite(m_nPortB, (bB) ? HIGH : LOW);
		delay(500);
	}

protected:
	int m_nPortR;
	int m_nPortG;
	int m_nPortB;
};