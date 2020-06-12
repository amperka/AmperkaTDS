# AmperkaTDS API

## `class AmperkaTDS`

Create an object of type `AmperkaTDS` to communicate with a particular [TDS-sensor](https://amperka.ru/product/troyka-tds-sensor).

### `AmperkaTDS(uint8_t pinS)`

Constructs a new `AmperkaTDS` object. The argument `pinS` the analog output signal. It is marked `S` on the TDS board. Use any analog GPIO pin of the controller.

### `void begin()`

Initializes the given interface, prepares the board for communication.
Call this method before interfacing with `AmperkaTDS`. For example, in your `setup()`.

### `void read()`

Reads and stores the sensor data values: EC and TDS.

### `uint16_t getEC()`

Returns the stored electrical conductivity (EC) when the call method `read`. EC measurement is in microsiemens per centimeter and ranges from `0` to `2500` in `uS/cm`.

### `uint16_t getTDS()`

Returns the stored total dissolved solids (TDS) when the call method `read`. TDS measurement is in parts per million and ranges from `0` to `1250` in `ppm`.

### `float getCalibrationFactor()`

Returns the ratio between the known TDS value and the TDS measurement value. In the ideal case, the ratio is `1`. Use the returned value in the function `setCalibrationFactor`. During the calibration, use a liquid buffer solution of known TDS value.

_The measured value may differ from the actual value due to the individual differences between the different TDS sensors and differences in the control boards. Therefore, calibration is required before measurement, to obtain a more accurate TDS value._

### `void setCalibrationFactor(float calibrationFactor)`

Corrects the difference between the known TDS value and the TDS measurement value. The argument `calibrationFactor` is the ratio between the known TDS value and the TDS measurement value, which gets `getCalibrationFactor()` function.

### `void setEnvironmentTemperature(float temperature)`

Sets temperature from other climatic sensors to compensate for TDS data error. The argument `temperature` is an ambient temperature from other sensors. Ranges from `−25` to `50` °C.

By default, the internal algorithm uses 25 °C temperature to compensate for environmental changes. Read temperature from other climatic sensors, e.g., [Troyka Meteo Sensor](https://amperka.ru/product/troyka-meteo-sensor) or [Sealed Temperature Sensor DS18B20](https://amperka.ru/product/sealed-temperature-sensor-ds18b20).

### `void setAnalogReadResolution(uint8_t bits = 10)`

Sets resolution to output values, that are used to calculate voltage on the sensor in function `read`. The argument `bits` is the current resolution analog to digital conversion (ADC) Arduino board. Ranges from `1` to `32` bits. If omitted, resolution output values are `10`. This function doesn't change the Arduino board resolution.

Resolution ADC is changed with standard Arduino function `analogReadResolution(uint8_t bits)`, but only for some Arduino boards. If you call the function `analogReadResolution (bits uint8_t)`, then call `setAnalogReadResolution (bits uint8_t)` with the same argument `bits`.
