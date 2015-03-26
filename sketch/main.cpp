// stepper_ping

// Control a stepper motor based on a distance sensor.

#include <AccelStepper.h>
#include <NewPing.h>

#define HALFSTEP      8
#define MAX_DISTANCE  200
#define M1P1          2      // IN1 on the ULN2003 driver 1
#define M1P2          3      // IN2 on the ULN2003 driver 1
#define M1P3          4      // IN3 on the ULN2003 driver 1
#define M1P4          5      // IN4 on the ULN2003 driver 1
#define TRIG          8
#define ECHO          9

AccelStepper stepper(HALFSTEP, M1P1, M1P3, M1P2, M1P4);
NewPing sonar(TRIG, ECHO, MAX_DISTANCE);

void setup()
{
  Serial.begin(9600);
  stepper.setMaxSpeed(1000.0);
  stepper.setAcceleration(100.0);
  stepper.setSpeed(200.0);
  stepper.moveTo(20000);
}

void loop()
{
  // unsigned int pingTime = sonar.ping();
  // unsigned int pingDistance = (pingTime / US_ROUNDTRIP_CM);
  // Serial.print("pingDistance = ");
  // Serial.print(pingDistance);
  // Serial.print("\n");
  // delay(50);
  
  if (stepper.distanceToGo() == 0) 
  {
    stepper.moveTo(-stepper.currentPosition());
  }
  stepper.run();
}


