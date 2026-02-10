#include <Arduino.h>
#include <JSNSR04T.h>

static const int JSNSR04T_RX = PD2;
static const int JSNSR04T_TX = PC12;

HardwareSerial jsnsr04tSerial(JSNSR04T_RX, JSNSR04T_TX);
JSNSR04T jsnsr04t(&jsnsr04tSerial);

void setup() {
  Serial.begin(115200);
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