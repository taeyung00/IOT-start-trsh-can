#pragma once

#include <Servo.h>
#include <Arduino.h>
#include "UltrasonicSensor.h"  // 센서 기능 사용
//서보 모터
class ServoMotor : public UltrasonicSensor
{
public:
    ServoMotor(void) {}
    ~ServoMotor() {}

    void setPort(int servoPin) {
        m_servoPin = servoPin;
        m_servo.attach(m_servoPin);
        close(); // 기본: 닫힘
    }

    void open() {
        m_servo.write(90); // 열기 (90도)
        
    }

    void m_start() {
        m_servo.write(90); // 열기 (90도)
    }

    void close() {
        m_servo.write(0);  // 닫기 (0도)
       
    }

    void moveTo(int angle) {
        m_servo.write(angle); // 원하는 각도로 이동
    }

    
protected:
   
    int m_servoPin;
    Servo m_servo;
    UltrasonicSensor m_UltrasonicSensor;
    bool m_isOpen =false;
};
