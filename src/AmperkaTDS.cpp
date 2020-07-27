#include <AmperkaTDS.h>

AmperkaTDS::AmperkaTDS(uint8_t pinS) : _pinS(pinS) {}

void AmperkaTDS::begin() {
    pinMode(this->_pinS, INPUT);
    setAnalogReadResolution();
    this->_calibrationFactor = 1.0;
    this->_temperature = 25.0;
}

void AmperkaTDS::read() {
    int valueADC = analogRead(this->_pinS);
    float valueVoltage = valueADC * BOARD_OPERATING_VOLTAGE / pow(2, this->_bits);
    // convert voltage to TDS value
    this->_valueTDS = (66.71 * pow(valueVoltage, 3) -
                        127.93 * pow(valueVoltage, 2) + 428.7 * valueVoltage) *
                        this->_calibrationFactor;
    // temperature compensation
    this->_valueTDS =
        this->_valueTDS / (1.0 + 0.02 * (this->_temperature - 25.0));
    // convert TDS to EC
    this->_valueEC = this->_valueTDS * converionTDStoEC;
}

uint16_t AmperkaTDS::getEC() const { return this->_valueEC; }

uint16_t AmperkaTDS::getTDS() const { return this->_valueTDS; }

void AmperkaTDS::setCalibrationFactor(float calibrationFactor) {
    this->_calibrationFactor = calibrationFactor;
}

float AmperkaTDS::readCalibrationFactor(uint16_t calibrationValueTDS) {
    this->read();
    float calibrationFactor = static_cast<float>(calibrationValueTDS) /
                                static_cast<float>(this->_valueTDS);
    return calibrationFactor;
}

void AmperkaTDS::setCompensationTemperature(float temperature) {
    this->_temperature = temperature;
}

void AmperkaTDS::setAnalogReadResolution(uint8_t bits) { this->_bits = bits; }
