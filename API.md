# AmperkaTDS API

## `class AmperkaTDS`

Create an object of type `AmperkaTDS` to communicate with a particular [TDS-sensor](https://amperka.ru/product/troyka-tds-sensor).

### `AmperkaTDS(uint8_t pinS)`

Constructs a new `AmperkaTDS` object. The argument `pinS` the analog output signal. It is marked `S` on the TDS board. Use any analog GPIO pin of the controller.

### `void begin()`

Initializes the given interface, prepares the board for communication.
Call this method before interfacing with `AmperkaTDS`. For example, in your `setup()`.

### `void read()`

Reads and stores the sensor data values EC and TDS.

### `uint16_t getEC()`

Returns the stored electrical conductivity (EC) when the call method `read`. Measurement EC in microsiemens per centimeter — ranges from `0` to `2500` in `uS/cm`.

### `uint16_t getTDS()`

Returns the stored total dissolved solids (TDS) when the call method `read`. Measurement TDS in parts per million — ranges from `0` to `1250` in `ppm`.

### `float getCalibrationFactor()`

Returns the ratio between the known TDS value and the TDS measurement value. In the ideal case, the ratio is `1`. Returned value use in the function `setCalibrationFactor`. During the calibration, use a liquid buffer solution of known TDS value.

_The measured value may differ from the actual value due to individual differences between different TDS sensors and differences in the control board. Therefore, to obtain a more accurate TDS value, calibration is required before measurement._

### `void setCalibrationFactor(float calibrationFactor)`

Corrects the difference between the known TDS value and the TDS measurement value. The argument `calibrationFactor` the ratio between the known TDS value and the TDS measurement value, which gets `getCalibrationFactor()` function.

### `void setEnvironmentTemperature(float temperature)`

Sets temperature from other climatic sensors to compensate TDS data. The argument `temperature` ambient temperature from other sensors. Range from `−25` to `50` °C.

By default, the internal algorithm uses 25 °C temperature to compensate for environmental changes. Read temperature from other climatic sensors, e.g., [Troyka Meteo Sensor](https://amperka.ru/product/troyka-meteo-sensor) or [Sealed Temperature Sensor DS18B20](https://amperka.ru/product/sealed-temperature-sensor-ds18b20).

### `void setAnalogReadResolution(uint8_t bits = 10)`

Sets resolution to output values, which used in calculate voltage on the sensor in function `read`. The argument `bits` is the current resolution analog to digital conversion (ADC) Arduino board. Ranges from `1` to `32` bits. If omitted, resolution output values are `10`. This function doesn't change the resolution Arduino board.

Resolution ADC is set and changed standard Arduino function `analogReadResolution(uint8_t bits)`, but only some arduino boards. If you call the function `analogReadResolution (bits uint8_t)`, then call `setAnalogReadResolution (bits uint8_t)` with the same argument `bits`.
