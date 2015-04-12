#include <AccelStepper.h>
#include <NewPing.h>
#include <Servo.h>

#include "gbot.h"

AccelStepper leftMotor(AccelStepper::HALF4WIRE, LM_PIN_1, LM_PIN_3, LM_PIN_2, LM_PIN_4);
AccelStepper rightMotor(AccelStepper::HALF4WIRE, RM_PIN_1, RM_PIN_3, RM_PIN_2, RM_PIN_4);
Servo servo;
long previousMillis = 0;
int motorMode = MOVE_STOP;
int servoDirection = SERVO_CENTER;

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
  leftMotor.runSpeed();
  rightMotor.runSpeed();

  if (Serial.available())
  {
    int result = Serial.parseInt();
    switch (result)
    {
      case MOVE_FORWARD:
        leftMotor.setSpeed(SPD_LEFT_FORWARD);
        rightMotor.setSpeed(SPD_RIGHT_FORWARD);
        motorMode = MOVE_FORWARD;
        break;
      case MOVE_BACK:
        leftMotor.setSpeed(SPD_LEFT_BACK);
        rightMotor.setSpeed(SPD_RIGHT_BACK);
        motorMode = MOVE_BACK;
        break;
      case MOVE_LEFT:
        leftMotor.setSpeed(SPD_LEFT_LEFT);
        rightMotor.setSpeed(SPD_RIGHT_LEFT);
        motorMode = MOVE_LEFT;
        break;
      case MOVE_RIGHT:
        leftMotor.setSpeed(SPD_LEFT_RIGHT);
        rightMotor.setSpeed(SPD_RIGHT_RIGHT);
        motorMode = MOVE_RIGHT;
        break;
      case MOVE_STOP:
        leftMotor.setSpeed(SPD_STOP);
        rightMotor.setSpeed(SPD_STOP);
        motorMode = MOVE_STOP; 
        break;
      case PAN_CENTER:
        servo_center();
        break;
      case PAN_LEFT:
        servo_left();
        break;
      case PAN_RIGHT:
        servo_right();
        break;
      default:
        break;
    }
  }
}

void servo_left()
{
  servoDirection = servoDirection + SERVO_SETP > SERVO_LEFT_MAX ?
                   SERVO_LEFT_MAX : servoDirection + SERVO_STEP;
  servo.write(servoDirection);
}

void servo_right()
{
  servoDirection = servoDirection - SERVO_SETP > SERVO_RIGHT_MAX ?
                   SERVO_RIGHT_MAX : servoDirection - SERVO_STEP;
  servo.write(servoDirection);
}

servo_center()
{
  servoDirection = SERVO_CENTER;
  servo.write(servoDirection);
}

void setupMotors() 
{
  leftMotor.setMaxSpeed(MAX_SPEED);
  leftMotor.setSpeed(SPD_STOP);
  rightMotor.setMaxSpeed(MAX_SPEED);
  rightMotor.setSpeed(SPD_STOP);
}
