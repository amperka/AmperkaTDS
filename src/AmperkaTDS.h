#ifndef __AMPERKA_TDS_H__
#define __AMPERKA_TDS_H__

#include <Arduino.h>

#if defined(__AVR__)
#define BOARD_OPERATING_VOLTAGE 5.0
#else
#define BOARD_OPERATING_VOLTAGE 3.3
#endif

constexpr float converionTDStoEC = 2.0;

class AmperkaTDS {
public:
    AmperkaTDS(uint8_t pinS);
    void begin();
    void read();
    uint16_t getEC() const;
    uint16_t getTDS() const;
    void setCalibrationFactor(float calibrationFactor);
    float readCalibrationFactor(uint16_t calibrationValueTDS);
    void setCompensationTemperature(float temperature);
    void setAnalogReadResolution(uint8_t bits = 10);

private:
    uint8_t _pinS;
    uint8_t _bits;
    uint16_t _valueEC;
    uint16_t _valueTDS;
    float _calibrationFactor;
    float _temperature;
};

#endif // __AMPERKA_TDS_H__