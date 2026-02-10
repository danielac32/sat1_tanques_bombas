#ifndef Switch_h
#define Switch_h

#include <Arduino.h>

class Switch {
  public:
    // Inicializar con array de pines y su cantidad
    Switch(byte* pins, byte count);
    
    // Leer un switch específico: -1=ABAJO, 0=CENTRO, 1=ARRIBA
    int read(byte switchIndex);
    
    // Leer todos los switches
    void readAll(int* results);
    
  private:
    byte* _pins;
    byte _count;
    const int _threshold = 200;  // Umbral fijo
};

#endif