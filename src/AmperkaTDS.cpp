#include <AmperkaTDS.h>

AmperkaTDS::AmperkaTDS(uint8_t pinS, uint8_t pinS)
    : _pinS(pinS) {}

void AmperkaTDS::begin() {
    pinMode(_pinS, INPUT);
    setAnalogReadResolution();
    _calibrationFactor = 1.0;
    _temperature = 25.0;
}

void AmperkaTDS::read() {
    int valueADC = analogRead(_pinS);
    float valueVoltage = valueADC * BOARD_OPERATING_VOLTAGE / pow(2, _bits);
    // Convert voltage to TDS value
    _valueTDS = (66.71 * pow(valueVoltage, 3) - 127.93 * pow(valueVoltage, 2)
                 + 428.7 * valueVoltage)
                * _calibrationFactor;
    // Temperature compensation
    _valueTDS = _valueTDS / (1.0 + 0.02 * (_temperature - 25.0));
    // Convert TDS to EC
    _valueEC = _valueTDS * converionTDStoEC;
}

uint16_t AmperkaTDS::getEC() const { return _valueEC; }

uint16_t AmperkaTDS::getTDS() const { return _valueTDS; }

void AmperkaTDS::setCalibrationFactor(float calibrationFactor) {
    _calibrationFactor = calibrationFactor;
}

float AmperkaTDS::readCalibrationFactor(uint16_t calibrationValueTDS) {
    read();
    float calibrationFactor = static_cast<float>(calibrationValueTDS)
                              / static_cast<float>(_valueTDS);
    return calibrationFactor;
}

void AmperkaTDS::setCompensationTemperature(float temperature) {
    _temperature = temperature;
}

void AmperkaTDS::setAnalogReadResolution(uint8_t bits) { _bits = bits; }
