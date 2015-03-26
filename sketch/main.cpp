// stepper_ping

// Control a stepper motor based on a distance sensor.

#include <AccelStepper.h>
#include <NewPing.h>
#include <Servo.h>

#define HALFSTEP      8
#define MAX_DISTANCE  200
#define M1P1          2      // IN1 on the ULN2003 driver 1
#define M1P2          3      // IN2 on the ULN2003 driver 1
#define M1P3          4      // IN3 on the ULN2003 driver 1
#define M1P4          5      // IN4 on the ULN2003 driver 1
#define M2P1          6      // IN1 on the ULN2003 driver 2
#define M2P2          7      // IN2 on the ULN2003 driver 2
#define M2P3          8      // IN3 on the ULN2003 driver 2
#define M2P4          9      // IN4 on the ULN2003 driver 2
//#define TRIG          8
//#define ECHO          9
#define SERVO         10

AccelStepper stepper1(HALFSTEP, M1P1, M1P3, M1P2, M1P4);
AccelStepper stepper2(HALFSTEP, M2P1, M2P3, M2P2, M2P4);
//NewPing sonar(TRIG, ECHO, MAX_DISTANCE);
Servo servo;

void setup()
{
  Serial.begin(9600);
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
  stepper1.setSpeed(200.0);
  stepper1.moveTo(20000);
  stepper2.setMaxSpeed(1000.0);
  stepper2.setAcceleration(100.0);
  stepper2.setSpeed(200.0);
  stepper2.moveTo(20000);
  //servo.attach(10);

}

void loop()
{
  // unsigned int pingTime = sonar.ping();
  // unsigned int pingDistance = (pingTime / US_ROUNDTRIP_CM);
  // Serial.print("pingDistance = ");
  // Serial.print(pingDistance);
  // Serial.print("\n");
  // delay(50);
  
  if (stepper1.distanceToGo() == 0) 
  {
    stepper1.moveTo(-stepper1.currentPosition());
  }
  stepper1.run();

  if (stepper2.distanceToGo() == 0) 
  {
    stepper2.moveTo(-stepper2.currentPosition());
  }
  stepper2.run();





/*  int pos;
  for(pos = 15; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees
  {                                  // in steps of 1 degree
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
    if (pos == 90) {
      delay(500);
    }
  }
  for(pos = 180; pos>=15; pos-=1)     // goes from 180 degrees to 0 degrees
  {
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
    if (pos == 90) {
      delay(500);
    }
  }*/

}
