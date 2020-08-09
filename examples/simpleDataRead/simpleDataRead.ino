/*
 * This example shows how to read the TDS and EC values
 * from Amperka TDS-sensor.
 */

// Include the library to communicate with TDS-sensor
#include <AmperkaTDS.h>

// Use any analog pin of the controller
constexpr auto pinSensor = A0;

// Create an object for working with Amperka TDS-sensor
AmperkaTDS sensorTDS(pinSensor);

void setup() {
    // Open serial port with 9600 baud rate
    Serial.begin(9600);
    // Wait for serial port to connect, needed for native USB.
    while (!Serial)
        ;
    // Start the sensor for communication
    sensorTDS.begin();
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
