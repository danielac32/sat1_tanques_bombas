#include <Switch.h>

// Pines donde están conectados los switches
byte pinesSwitches[] = {A0, A1, A2, A3};
byte numSwitches = 4;

// Crear objeto
Switch switches(pinesSwitches, numSwitches);

// Array para guardar resultados
int estados[4];

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Leer todos los switches
  switches.readAll(estados);
  
  // Mostrar resultados
  for (byte i = 0; i < numSwitches; i++) {
    Serial.print("S");
    Serial.print(i);
    Serial.print(": ");
    
    switch (estados[i]) {
      case -1: Serial.println("Abajo"); break;
      case 0:  Serial.println("Centro"); break;
      case 1:  Serial.println("Arriba"); break;
    }
  }
  
  Serial.println("---");
  delay(300);
}