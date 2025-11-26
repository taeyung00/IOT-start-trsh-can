#pragma once

#include "Voltmeter.h"

#define LIGHT_BRIGHT_LIMIT 400
#define LIGHT_AMBIENT_LIMIT 730

enum class LightType {
    DARK = 0, AMBIENT, BRIGHT
};
// 조도 센서
class LightSensor : public Voltmeter {
public:
    LightSensor(void) {
        setPort(A2); // 센서 포트 설정
    }
    ~LightSensor() {}

    int getLightStep(void) const {
    return 1023 - getVoltStep();  // 밝을수록 값이 커짐 (비례됨)
		}


    LightType getLightType(void) const {
        int nLight = getLightStep();
        if (nLight < LIGHT_BRIGHT_LIMIT) return LightType::BRIGHT;
        else if (nLight < LIGHT_AMBIENT_LIMIT) return LightType::AMBIENT;
        else return LightType::DARK;
    }

    String typeToStr(LightType nType) {
        switch (nType) {
            case LightType::DARK: return "dark";
            case LightType::AMBIENT: return "ambient";
            default: return "bright";
        }
    }
};
