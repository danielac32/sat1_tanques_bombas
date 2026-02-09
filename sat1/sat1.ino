#include <HCSR04.h>
#include <Taskfun.h>
#include <OneWire.h>
#include <DallasTemperature.h>



HCSR04 hc(44, new int[4]{42, 40, 38, 36}, 4); //initialisation class HCSR04 (trig pin , echo pin, number of sensor)



#define ONE_WIRE_BUS 46

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);
int deviceCount = 0;
float tempC;


void setup()
{
    Serial.begin(9600);
    pinMode(13,OUTPUT);
    pinMode(46,INPUT_PULLUP);
    
    sensors.begin();  // Start up the library
    Serial.print("Locating devices...");
    Serial.print("Found ");
    deviceCount = sensors.getDeviceCount();
    Serial.print(deviceCount, DEC);
    Serial.println(" devices.");
    Serial.println("");


    
  
    Serial.println("Sistema listo");
    Serial.println("========================");
    setupTasks();
    runTask(Distancia, 0);
    runTask(Led, 0);
    runTask(Temp, 0);
}



void Temp(int t){
  while(1){
    sensors.requestTemperatures();

    // Display temperature from each sensor
    for (int i = 0; i < deviceCount; i++) {
      Serial.print("Sensor ");
      Serial.print(i + 1);
      Serial.print(" : ");
      tempC = sensors.getTempCByIndex(i);
      Serial.print(tempC);
      Serial.print("°C  |  ");
      Serial.print(DallasTemperature::toFahrenheit(tempC));
      Serial.println("°F");
    }
  
    Serial.println("");
    delay(1000);
  }
}


void Led(int t){
  while(1){
    digitalWrite(13,!digitalRead(13));
    delay(200);
  }
}

void Distancia(int t){
  while(1){
    for (int i = 0; i < 4; i++) {
        float distancia = hc.dist(i);
        // Opción B: Todo en una línea
        Serial.print("S");
        Serial.print(i);
        Serial.print(":");
        Serial.print(distancia, 1);  // 1 decimal
        Serial.println("cm ");
    }
    delay(1000);  
  }
}




void loop()
{
                    
}
