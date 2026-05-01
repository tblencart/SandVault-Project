#include <OneWire.h>
#include <DallasTemperature.h>

// I am using GPIO 5 for the OneWire bus (Data pin)
#define ONE_WIRE_BUS 5

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void setup() {
  // I am using 115200 baud for fast and reliable serial communication
  Serial.begin(115200);
  
  // Start up the library for the DS18B20 sensors
  sensors.begin();
}

void loop() {
  // Send the command to get temperatures from all sensors on the bus
  sensors.requestTemperatures(); 
  
  // Reading temperatures from the two sensors
  // Index 0 is typically the first sensor found, Index 1 the second
  float tempSand = sensors.getTempCByIndex(0); 
  float tempWater = sensors.getTempCByIndex(1);

  // Formatting for the Arduino Serial Plotter
  // This allows me to visualize the thermal transfer in real-time
  Serial.print("Sand_Core_Temp:");
  Serial.print(tempSand);
  Serial.print(",");
  Serial.print("Water_Loop_Temp:");
  Serial.println(tempWater);

  // I set a 1-second delay to maintain a stable telemetry stream
  delay(1000);
}
