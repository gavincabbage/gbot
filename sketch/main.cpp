#include <AccelStepper.h>
#include <NewPing.h>
#include <Servo.h>

#include "gbot.h"

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
  if (Serial.available())
  {
    switch (Serial.parseInt())
    {
      case MOVE_FORWARD:
        Serial.println("MOVE_FORWARD"); break;
      case MOVE_BACK:
        Serial.println("MOVE_BACK"); break;
      case MOVE_LEFT:
        Serial.println("MOVE_LEFT"); break;
      case MOVE_RIGHT:
        Serial.println("MOVE_RIGHT"); break;
      case PAN_CENTER:
        Serial.println("PAN_CENTER"); break;
      case PAN_LEFT:
        Serial.println("PAN_LEFT"); break;
      case PAN_RIGHT:
        Serial.println("LEFT"); break;
      default:
        Serial.println("DEFAULT"); break;
    }
  }


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
