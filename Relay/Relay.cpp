#include "Relay.h"

// Constructor por defecto - activación con HIGH
Relay::Relay() {
  activeLow = false;
  for (int i = 0; i < 4; i++) {
    states[i] = false;  // Todos apagados inicialmente
  }
}

// Constructor con configuración de activación
Relay::Relay(bool activeLowMode) {
  activeLow = activeLowMode;
  for (int i = 0; i < 4; i++) {
    states[i] = false;  // Todos apagados inicialmente
  }
}

// Configurar los pines de los relés
void Relay::setPins(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4) {
  pins[0] = pin1;
  pins[1] = pin2;
  pins[2] = pin3;
  pins[3] = pin4;
}

// Inicializar los pines como salidas
void Relay::begin() {
  for (int i = 0; i < 4; i++) {
    pinMode(pins[i], OUTPUT);
    // Establecer estado inicial (apagado)
    digitalWrite(pins[i], activeLow ? HIGH : LOW);
  }
}

// Encender un relé específico (0-3)
void Relay::turnOn(uint8_t relayNum) {
  if (relayNum < 4) {
    digitalWrite(pins[relayNum], activeLow ? LOW : HIGH);
    states[relayNum] = true;
  }
}

// Apagar un relé específico (0-3)
void Relay::turnOff(uint8_t relayNum) {
  if (relayNum < 4) {
    digitalWrite(pins[relayNum], activeLow ? HIGH : LOW);
    states[relayNum] = false;
  }
}

// Alternar estado de un relé
void Relay::toggle(uint8_t relayNum) {
  if (relayNum < 4) {
    if (states[relayNum]) {
      turnOff(relayNum);
    } else {
      turnOn(relayNum);
    }
  }
}

// Encender relé por número de pin
void Relay::turnOnByPin(uint8_t pin) {
  for (int i = 0; i < 4; i++) {
    if (pins[i] == pin) {
      turnOn(i);
      break;
    }
  }
}

// Apagar relé por número de pin
void Relay::turnOffByPin(uint8_t pin) {
  for (int i = 0; i < 4; i++) {
    if (pins[i] == pin) {
      turnOff(i);
      break;
    }
  }
}

// Encender todos los relés
void Relay::turnOnAll() {
  for (int i = 0; i < 4; i++) {
    turnOn(i);
  }
}

// Apagar todos los relés
void Relay::turnOffAll() {
  for (int i = 0; i < 4; i++) {
    turnOff(i);
  }
}

// Obtener estado de un relé
bool Relay::getState(uint8_t relayNum) {
  if (relayNum < 4) {
    return states[relayNum];
  }
  return false;
}

// Obtener estado de todos los relés como máscara de bits
uint8_t Relay::getAllStates() {
  uint8_t mask = 0;
  for (int i = 0; i < 4; i++) {
    if (states[i]) {
      mask |= (1 << i);
    }
  }
  return mask;
}

// Configurar modo activo
void Relay::setActiveLow(bool mode) {
  activeLow = mode;
  // Aplicar el nuevo modo a todos los relés según su estado actual
  for (int i = 0; i < 4; i++) {
    digitalWrite(pins[i], states[i] ? (activeLow ? LOW : HIGH) : (activeLow ? HIGH : LOW));
  }
}