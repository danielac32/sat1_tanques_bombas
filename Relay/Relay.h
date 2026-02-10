#ifndef Relay_h
#define Relay_h

#include <Arduino.h>

class Relay {
  private:
    uint8_t pins[4];        // Array para almacenar los pines de los relés
    bool states[4];         // Array para almacenar el estado de cada relé
    bool activeLow;         // Si los relés se activan con LOW (true) o HIGH (false)
    
  public:
    // Constructor por defecto - activeLow = false (activación con HIGH)
    Relay();
    
    // Constructor con configuración de activación
    Relay(bool activeLowMode);
    
    // Configurar los pines de los relés
    void setPins(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);
    
    // Inicializar los pines como salidas
    void begin();
    
    // Métodos para control individual por número de relé (0-3)
    void turnOn(uint8_t relayNum);      // Encender relé específico
    void turnOff(uint8_t relayNum);     // Apagar relé específico
    void toggle(uint8_t relayNum);      // Alternar estado del relé
    
    // Métodos para control individual por número de pin
    void turnOnByPin(uint8_t pin);      // Encender relé por número de pin
    void turnOffByPin(uint8_t pin);     // Apagar relé por número de pin
    
    // Métodos para control múltiple
    void turnOnAll();                   // Encender todos los relés
    void turnOffAll();                  // Apagar todos los relés
    
    // Obtener estado de un relé
    bool getState(uint8_t relayNum);
    
    // Obtener estado de todos los relés como máscara de bits
    uint8_t getAllStates();
    
    // Configurar modo activo (LOW o HIGH)
    void setActiveLow(bool mode);
};

#endif