# JSN-SR04T v2.0

Arduino library for the JSN-SR04T v2.0 20-600 cm Ultrasonic Waterproof Range Finder.

***

Example:
```cpp
#include <Arduino.h>
#include <JSNSR04T.h>

HardwareSerial jsnsr04tSerial(PD2, PC12);
JSNSR04T jsnsr04t(&jsnsr04tSerial);

void setup() {
  Serial.begin(921600);
  while (!jsnsr04t.begin()) {
    Serial.print(F("JSN-SR04T not found!\n"));
    delay(1000);
  }
  Serial.print(F("JSN-SR04T found!\n"));
}

void loop() {
  Serial.print(F("JSN-SR04T:\t"));
  Serial.print(F("Distance (mm):\t"));
  Serial.print(jsnsr04t.getDistanceMM());
  Serial.print(F("\t"));
  Serial.print(F("Distance (cm):\t"));
  Serial.print(jsnsr04t.getDistanceCM());
  Serial.print(F("\t"));
  Serial.print(F("Distance (m):\t"));
  Serial.print(jsnsr04t.getDistanceM());
  Serial.print(F("\n"));
  delay(1000);
}
```