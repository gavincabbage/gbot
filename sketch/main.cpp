#include <AccelStepper.h>
#include <NewPing.h>
#include <Servo.h>

#define SERIAL_SPEED      9600
#define HALFSTEP          8
#define LM_PIN_1          2      // IN1, driver 1
#define LM_PIN_2          3      // IN2, driver 1
#define LM_PIN_3          4      // IN3, driver 1
#define LM_PIN_4          5      // IN4, driver 1
#define RM_PIN_1          6      // IN1, driver 2
#define RM_PIN_2          7      // IN2, driver 2
#define RM_PIN_3          8      // IN3, driver 2
#define RM_PIN_4          9      // IN4, driver 2
#define SERVO_PIN         10
#define TARGET            20000
#define SPEED             500.0
#define MAX_SPEED         1000.0
#define ACCELERATION      100.0
#define SERVO_CENTER      90
#define SERVO_LEFT        135
#define SERVO_RIGHT       45
#define SERVO_INTERVAL    3000

AccelStepper leftMotor(HALFSTEP, LM_PIN_1, LM_PIN_3, LM_PIN_2, LM_PIN_4);
AccelStepper rightMotor(HALFSTEP, RM_PIN_1, RM_PIN_3, RM_PIN_2, RM_PIN_4);
Servo servo;
long previousMillis = 0;

void setupMotors();

void setup()
{
  Serial.begin(SERIAL_SPEED);
  setupMotors();
  servo.attach(SERVO_PIN);
  servo.write(SERVO_CENTER);
}

void loop()
{
  if (leftMotor.distanceToGo() == 0) 
  {
    leftMotor.moveTo(-leftMotor.currentPosition());
  }
  leftMotor.run();

  if (rightMotor.distanceToGo() == 0) 
  {
    rightMotor.moveTo(-rightMotor.currentPosition());
  }
  rightMotor.run();

  // check to see if it's time to move the servo
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > SERVO_INTERVAL) {

    // save the last time
    previousMillis = currentMillis;   

    int pos = servo.read();

    if (pos == SERVO_CENTER)
    {
      servo.write(SERVO_LEFT);
    }
    else if (pos == SERVO_LEFT)
    {
      servo.write(SERVO_RIGHT);
    }
    else if (pos == SERVO_RIGHT)
    {
      servo.write(SERVO_CENTER);
    }
  }
}

void setupMotors() 
{
  leftMotor.setMaxSpeed(MAX_SPEED);
  leftMotor.setAcceleration(ACCELERATION);
  leftMotor.setSpeed(SPEED);
  leftMotor.moveTo(TARGET);
  rightMotor.setMaxSpeed(MAX_SPEED);
  rightMotor.setAcceleration(ACCELERATION);
  rightMotor.setSpeed(SPEED);
  rightMotor.moveTo(-TARGET);
}
