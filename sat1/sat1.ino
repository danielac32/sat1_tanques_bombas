#include <Relay.h>



 
#include <Taskfun.h>
#include <OneWire.h>
#include <DallasTemperature.h>

 

#define ONE_WIRE_BUS 46
OneWire oneWire(ONE_WIRE_BUS);
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
    
    delay(1000);  
  }
}




void loop()
{
                    
}

/*
 

#define trigPin 12
#define echoPin 11

long duration;
int distance;

 
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
   
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration*0.034/2;

  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");
 
}
 * /
 */
