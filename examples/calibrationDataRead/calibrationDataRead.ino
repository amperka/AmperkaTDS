/*
 * This example shows how to read the TDS and EC calibration values
 * from Amperka TDS-sensor
 * During the calibration, use standart buffer solution of know TDS value
 * For more details read the calibration section in API.md
 */

// Include the library to comunicate with Amperka TDS-sensor
#include <AmperkaTDS.h>

// Use any analog GPIO pin of the controller
constexpr auto pinSensor = A0;

// Create an object to work with Amperka TDS-sensor
AmperkaTDS sensorTDS(pinSensor);

void setup() {
    // Open serial port with 9600 baud rate
    Serial.begin(9600);
    // Wait for serial port to connect, needed for native USB.
    while (!Serial)
      ;
    // Start the sensor for communication
    sensorTDS.begin();
    // Use this function only for calibration sensor,
    // otherwise comment-out.
    calibrateSensor();
}

void loop() {
    // Read the sensor data values: EC and TDS
    sensorTDS.read();
    // Receive the stored electrical conductivity (EC)
    int valueEC = sensorTDS.getEC();
    // Receive the stored total dissolved solids (TDS)
    int valueTDS = sensorTDS.getTDS();
    // Print results
    Serial.print("EC Value = ");
    Serial.print(valueEC);
    Serial.print(" uS/cm");
    Serial.print("\t");
    Serial.print("TDS Value = ");
    Serial.print(valueTDS);
    Serial.println(" ppm");
    // Wait 1000 ms
    delay(1000);
}

// Function for calibration sensor
// For more details read the calibration section in API.md file.
void calibrateSensor() {
    // for example buffer calibration solution is 342 ppm
    float calibrationFactor = sensorTDS.readCalibrationFactor(342);
    sensorTDS.setCalibrationFactor(calibrationFactor);
    Serial.print("CalibrationFactor = ");
    Serial.println(calibrationFactor);
}
