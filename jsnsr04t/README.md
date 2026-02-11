# JSN SR-04T

This provides a simple driver for JSN SR-04T board, which reads distance using ultrasonic transducter.

## Usage



Classical Arduino usage. In your sketch :

### Include the headers

```c++
#include <AsyncDelay.h>
#include <jsnsr04t.h>
```

The `AsyncDelay` is [a nice library implementing non-blocking delays](https://www.arduino.cc/reference/en/libraries/asyncdelay/). It is used internally by this library, therefore it is dependency. If you installed `jsnsr04t`, then you have it ready to use.

_Note: `delay` methods are pausing the main thread, meaning nothing else can happened on your system during the pause, including interrupts for other hardware. Although it is a clear way to understand basic stuff, it is better to use non-blocking way._

### Object declaration

Before your sketch start, instanciates the object : 

```c++
#define ECHO_PIN 2
#define TRIGGER_PIN 4

JsnSr04T ultrasonicSensor(ECHO_PIN, TRIGGER_PIN, LOG_LEVEL_VERBOSE);

```
_Note 1 : this is using defined constants for pin layout readability, you can skip this step if you feel more confortable with direct numbers._

_Note 2 : the log level parameter is not mandatory, default is `LOG_LEVEL_VERBOSE` which is the maximum. Under the hood, this library leverages ArduinoLog, so you can find all log levels, and all usage data [here](https://github.com/thijse/Arduino-Log/#usage)_

### Setup

Use the `begin` method :

```c++
void setup()
{
  ultrasonicSensor.begin();
}
```

This will create the needed setup regarding the pin layout, using the pin numbers you provided above.

### Read distance

In the `loop` method, use the `readDistance` method. It will return the distance found between obstacle and sensor in cm.
```c++
void loop()
{
  int distanceInCm = ultrasonicSensor.readDistance();
}
```

_Note : please enclose the `readDistance` call within timing function, such as it is done on given example. Constantly querying distance will give a lot or erratic results. From datasheet : >The recommend cycle period should be no less than 50ms_
## Example


Example folder contains one basic test. You will find an simple implementation with distance written to serial port.