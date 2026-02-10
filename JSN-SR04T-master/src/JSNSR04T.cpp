#include "./JSNSR04T.h"

JSNSR04T::JSNSR04T() {}

JSNSR04T::JSNSR04T(HardwareSerial *serial) { _serial = serial; }

JSNSR04T::~JSNSR04T() {}

bool JSNSR04T::begin(Jsnsr04tSamplingMode_Enum samplingMode,
                     uint8_t sampleSize) {
  if (_serial == NULL) {
#ifdef DEBUG
    Serial.print(F("Serial port not set!\n"));
#endif // DEBUG
    return (false);
  }
  _serial->begin(JSNSR04T_BAUD_RATE);
  uint32_t startTime = millis();
  while (getDistanceMM() == 0) {
    if ((millis() - startTime) > JSNSR04T_INIT_TIMEOUT) {
#ifdef DEBUG
      Serial.print(F("JSN-SR04T not found!"));
#endif // DEBUG
      return (false);
    }
  }
  _samplingMode = samplingMode;
  _sampleSize = (sampleSize > 0) ? sampleSize : 1;
  return (true);
}

bool JSNSR04T::begin(HardwareSerial *serial,
                     Jsnsr04tSamplingMode_Enum samplingMode,
                     uint8_t sampleSize) {
  _serial = serial;
  if (_serial == NULL) {
#ifdef DEBUG
    Serial.print(F("Serial port not set!\n"));
#endif // DEBUG
    return (false);
  }
  _serial->begin(JSNSR04T_BAUD_RATE);
  uint32_t startTime = millis();
  while (getDistanceMM() == 0) {
    if ((millis() - startTime) > JSNSR04T_INIT_TIMEOUT) {
#ifdef DEBUG
      Serial.print(F("JSN-SR04T not found!"));
#endif // DEBUG
      return (false);
    }
  }
  _samplingMode = samplingMode;
  _sampleSize = (sampleSize > 0) ? sampleSize : 1;
  return (true);
}

void JSNSR04T::setSamplingMode(Jsnsr04tSamplingMode_Enum samplingMode) {
  _samplingMode = samplingMode;
}

void JSNSR04T::setSampleSize(uint8_t sampleSize) { _sampleSize = sampleSize; }

uint8_t JSNSR04T::computeCheckSum(uint8_t *buffer, uint8_t len) {
  uint8_t checkSum = 0;
  for (int i = 0; i < len - 1; i++) {
    checkSum += (uint8_t)buffer[i];
  }
  return (checkSum);
}

bool JSNSR04T::confirmCheckSum(uint8_t *buffer, uint8_t len) {
  uint8_t calcCheckSum = computeCheckSum(buffer, len);
  uint8_t dataCheckSum = (uint8_t)buffer[len - 1];
#ifdef DEBUG
  Serial.print(F("Calculated check sum:\t"));
  Serial.print(calcCheckSum, HEX);
  Serial.print(F("\t"));
  Serial.print(F("Received check sum:\t"));
  Serial.print(dataCheckSum, HEX);
  Serial.print(F("\n"));
#endif // DEBUG
  if (calcCheckSum != dataCheckSum) {
    return (false);
  }
  return (true);
}

void JSNSR04T::sendCommand(uint8_t cmd) {
  _serial->write(cmd);
#ifdef DEBUG
  Serial.print(F("UART send:\t"));
  Serial.print(cmd, HEX);
  Serial.print(F("\n"));
#endif // DEBUG
}

uint8_t JSNSR04T::receiveData(uint8_t *buffer, uint8_t len) {
  uint32_t startTime = millis();
  uint8_t index = 0;
#ifdef DEBUG
  Serial.print(F("UART read:\t"));
#endif // DEBUG
  while (index < len) {
    if ((millis() - startTime) > JSNSR04T_READ_TIMEOUT) {
#ifdef DEBUG
      Serial.print(F("timeout!"));
#endif // DEBUG
      break;
    }
    if (_serial->available()) {
      uint8_t data = (uint8_t)_serial->read();
#ifdef DEBUG
      Serial.print(data, HEX);
      Serial.print(F(" "));
#endif // DEBUG
      buffer[index++] = data;
      startTime = millis();
    }
  }
#ifdef DEBUG
  Serial.print(F("\n"));
#endif // DEBUG
  if (buffer[0] != (uint8_t)0xFF) {
#ifdef DEBUG
    Serial.print(F("Header byte error!\n"));
#endif // DEBUG
    return (0);
  }
  if (!confirmCheckSum(buffer, len)) {
#ifdef DEBUG
    Serial.print(F("Check sum error!\n"));
#endif // DEBUG
    return (0);
  }
  return (index);
}

bool JSNSR04T::updateReadings() {
  static uint8_t response[4] = {0};
  if ((millis() - _lastReadTime) < JSNSR04T_UPDATE_TIME) {
#ifdef DEBUG
    Serial.print(F("Last update valid!\n"));
#endif // DEBUG
    return (true);
  }
  sendCommand(JSNSR04T_CMD_REQUEST_DATA);
  if (receiveData(response, 4) != 4) {
#ifdef DEBUG
    Serial.print(F("Not enough bytes received!\n"));
#endif // DEBUG
    return (false);
  }
  _distance = (uint16_t)((response[1] << 8) | response[2]);
  if (_distance < JSNSR04T_MIN_RANGE) {
    _distance = JSNSR04T_MIN_RANGE;
  } else if (_distance > JSNSR04T_MAX_RANGE) {
    _distance = JSNSR04T_MAX_RANGE;
  }
  latestDistance = _distance;
  _lastReadTime = millis();
  return (true);
}

uint16_t JSNSR04T::getDistanceMM() {
  if (_samplingMode == JSNSR04T_ONESHOT) {
    if (!updateReadings()) {
      return (0);
    }
    return (_distance);
  }
  uint32_t distance = (uint32_t)0;
  uint8_t sampleIndex = (uint8_t)0;
  uint8_t validSamples = (uint8_t)1;
  while (sampleIndex < _sampleSize) {
    if (updateReadings()) {
      distance += _distance;
      validSamples++;
    }
    sampleIndex++;
    delay(JSNSR04T_UPDATE_TIME);
  }
  return ((uint16_t)(distance /= (validSamples - 1)));
}

float JSNSR04T::getDistanceCM() { return ((float)getDistanceMM() / 10.0f); }

float JSNSR04T::getDistanceM() { return ((float)getDistanceMM() / 1000.0f); }