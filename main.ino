#include <EEPROM.h>
#include <AccelStepper.h>

#define stepPin 8
#define dirPin 9
#define eepromAddress 0
#define startLocation 0
#define endLocation 7000

AccelStepper stepper(1, stepPin, dirPin);
long lastLocation;

void setup() {
  // Serial.begin(9600);
  // while (!Serial) {
  //   ; // wait for serial port to connect. Needed for native USB port only
  // }

  EEPROM.get(eepromAddress, lastLocation);
  Serial.print("Reading lastLocation: ");
  Serial.println(lastLocation);

  if (lastLocation != startLocation && lastLocation != endLocation) {
    Serial.print("Found position: ");
    Serial.println(stepper.currentPosition());
  }

  if (lastLocation == startLocation || lastLocation < (endLocation / 2)) {
    Serial.println("Is start");
    stepper.move(endLocation);
  } else if (lastLocation == endLocation || lastLocation > (endLocation / 2)) {
    Serial.println("Is end");
    stepper.move(-endLocation);
  }

  stepper.setMaxSpeed(250.0);
  stepper.setAcceleration(100.0);
}

void loop() {
   if (!stepper.run()) {
    Serial.print("Final location: ");
    Serial.println(stepper.currentPosition());
    EEPROM.put(eepromAddress, stepper.currentPosition());

    for (;;)
      ;
  }
}
