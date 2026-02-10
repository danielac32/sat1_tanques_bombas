#ifndef JSNSR04T_H
#define JSNSR04T_H

#include <Arduino.h>

// #define DEBUG

typedef enum {
  JSNSR04T_ONESHOT,
  JSNSR04T_MULTIPLE_SAMPLES
} Jsnsr04tSamplingMode_Enum;

class JSNSR04T {
private:
  static const uint32_t JSNSR04T_BAUD_RATE = (uint32_t)9600;
  static const uint32_t JSNSR04T_INIT_TIMEOUT = (uint32_t)100;
  static const uint32_t JSNSR04T_READ_TIMEOUT = (uint32_t)60;
  static const uint32_t JSNSR04T_UPDATE_TIME = (uint32_t)60;
  static const uint16_t JSNSR04T_MIN_RANGE = (uint16_t)200;
  static const uint16_t JSNSR04T_MAX_RANGE = (uint16_t)6000;
  static const uint8_t JSNSR04T_CMD_REQUEST_DATA = (uint8_t)0x55;

  HardwareSerial *_serial = NULL;
  Jsnsr04tSamplingMode_Enum _samplingMode = JSNSR04T_ONESHOT;
  uint8_t _sampleSize = 0;
  uint32_t _lastReadTime = 0;
  uint16_t _distance = 0;

  uint8_t computeCheckSum(uint8_t *buffer, uint8_t len);
  bool confirmCheckSum(uint8_t *buffer, uint8_t len);
  void sendCommand(uint8_t cmd);
  uint8_t receiveData(uint8_t *buffer, uint8_t len);
  bool updateReadings();

public:
  uint16_t latestDistance = 0;
  uint16_t minRange = JSNSR04T_MIN_RANGE;
  uint16_t maxRange = JSNSR04T_MAX_RANGE;

  JSNSR04T();
  JSNSR04T(HardwareSerial *serial);
  bool begin(Jsnsr04tSamplingMode_Enum samplingMode = JSNSR04T_ONESHOT,
             uint8_t sampleSize = (uint8_t)1);
  bool begin(HardwareSerial *serial,
             Jsnsr04tSamplingMode_Enum samplingMode = JSNSR04T_ONESHOT,
             uint8_t sampleSize = (uint8_t)1);
  void setSamplingMode(Jsnsr04tSamplingMode_Enum samplingMode);
  void setSampleSize(uint8_t sampleSize);
  uint16_t getDistanceMM();
  float getDistanceCM();
  float getDistanceM();
  ~JSNSR04T();
};

#endif // !JSNSR04T_H