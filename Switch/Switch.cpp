#include "Switch.h"

Switch::Switch(byte* pins, byte count) {
  _pins = pins;
  _count = count;
  
  // Configurar pines como entradas
  for (byte i = 0; i < _count; i++) {
    pinMode(_pins[i], INPUT);
  }
}

int Switch::read(byte switchIndex) {
  if (switchIndex >= _count) return 0;
  
  int valor = analogRead(_pins[switchIndex]);
  
  // 512 es el valor medio (2.5V en ADC de 10 bits)
  if (valor > (512 + _threshold)) {
    return 1;      // ARRIBA
  } else if (valor < (512 - _threshold)) {
    return -1;     // ABAJO
  }
  return 0;        // CENTRO
}

void Switch::readAll(int* results) {
  for (byte i = 0; i < _count; i++) {
    results[i] = read(i);
  }
}