#include <Relay.h>

// Crear instancia de la clase MultiRelay
// Si tus relés se activan con LOW, usa: MultiRelay reles(true);
Relay reles;

void setup() {
  Serial.begin(9600);
  
  // Configurar los pines de los relés (puedes cambiarlos según tu conexión)
  reles.setPins(2, 3, 4, 5);
  
  // Inicializar los pines
  reles.begin();
  
  Serial.println("Sistema de 4 relés inicializado");
}

void loop() {
  // Ejemplo de uso de los métodos
  
  // Encender relé 0 (conectado al pin 2)
  reles.turnOn(0);
  Serial.println("Relé 0 encendido");
  delay(1000);
  
  // Apagar relé 0
  reles.turnOff(0);
  Serial.println("Relé 0 apagado");
  delay(1000);
  
  // Encender por número de pin (pin 3 = relé 1)
  reles.turnOnByPin(3);
  Serial.println("Relé en pin 3 encendido");
  delay(1000);
  
  // Apagar por número de pin
  reles.turnOffByPin(3);
  Serial.println("Relé en pin 3 apagado");
  delay(1000);
  
  // Encender todos los relés
  reles.turnOnAll();
  Serial.println("Todos los relés encendidos");
  delay(2000);
  
  // Apagar todos los relés
  reles.turnOffAll();
  Serial.println("Todos los relés apagados");
  delay(2000);
  
  // Alternar estado del relé 2
  reles.toggle(2);
  Serial.print("Estado del relé 2: ");
  Serial.println(reles.getState(2) ? "ENCENDIDO" : "APAGADO");
  delay(1000);
  
  reles.toggle(2);
  Serial.print("Estado del relé 2: ");
  Serial.println(reles.getState(2) ? "ENCENDIDO" : "APAGADO");
  delay(1000);
}