// TECHATRONIC.COM
// DHT11 LIBRARY
// https://github.com/adafruit/DHT-sensor-library
#include "DHT.h"
DHT dht2(2, DHT11);
void setup() {
  delay(1500);
  Serial.begin(9600);
}
void loop() {
  int h = dht2.readHumidity();
  int t = dht2.readTemperature();
  Serial.print("Temperature in C:   ");
  Serial.println(t);
  Serial.print("Humidity in C:   ");
  Serial.println(h);
  delay(1000);
}
