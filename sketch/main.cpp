#include <AccelStepper.h>
#include <NewPing.h>
#include <Servo.h>

#include "gbot.h"

AccelStepper leftMotor(AccelStepper::HALF4WIRE, LM_PIN_1, LM_PIN_3, LM_PIN_2, LM_PIN_4);
AccelStepper rightMotor(AccelStepper::HALF4WIRE, RM_PIN_1, RM_PIN_3, RM_PIN_2, RM_PIN_4);
Servo servo;
long previousMillis = 0;
int motorMode = MOVE_STOP;

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
  // switch(motorMode)
  // {
  //   case MOVE_FORWARD:
  //     leftMotor.move(LEFT_TARGET);
  //     rightMotor.move(RIGHT_TARGET);
  //     leftMotor.run();
  //     rightMotor.run();
  //     break;
  //   case MOVE_BACK:
  //     leftMotor.move(-LEFT_TARGET);
  //     rightMotor.move(-RIGHT_TARGET);
  //     leftMotor.run();
  //     rightMotor.run();
  //     break;
  //   case MOVE_LEFT:
  //     leftMotor.move(-LEFT_TARGET);
  //     rightMotor.move(RIGHT_TARGET);
  //     leftMotor.run();
  //     rightMotor.run();
  //     break;
  //   case MOVE_RIGHT:
  //     leftMotor.move(LEFT_TARGET);
  //     rightMotor.move(-RIGHT_TARGET);
  //     leftMotor.run();
  //     rightMotor.run();
  //     break;
  //   case MOVE_STOP:
  //     break;
  // }

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
        motorMode = MOVE_FORWARD; break;
      case MOVE_BACK:
        leftMotor.setSpeed(SPD_LEFT_BACK);
        rightMotor.setSpeed(SPD_RIGHT_BACK);
        motorMode = MOVE_BACK; break;
      case MOVE_LEFT:
        leftMotor.setSpeed(SPD_LEFT_LEFT);
        rightMotor.setSpeed(SPD_RIGHT_LEFT);
        motorMode = MOVE_LEFT; break;
      case MOVE_RIGHT:
        leftMotor.setSpeed(SPD_LEFT_RIGHT);
        rightMotor.setSpeed(SPD_RIGHT_RIGHT);
        motorMode = MOVE_RIGHT; break;
      case MOVE_STOP:
        leftMotor.setSpeed(SPD_STOP);
        rightMotor.setSpeed(SPD_STOP);
        motorMode = MOVE_STOP; 
        break;
      case PAN_CENTER:
        servo.write(SERVO_CENTER);
        break;
      case PAN_LEFT:
        servo.write(SERVO_LEFT);
        break;
      case PAN_RIGHT:
        servo.write(SERVO_RIGHT);
        break;
      default:
        break;
    }
  }

     // while(stepperB.currentPosition() != 50000){
     //     stepperB.run(); }
     //  stepperB.setCurrentPosition(0);

  // if (leftMotor.distanceToGo() == 0) 
  // {
  //   leftMotor.moveTo(-leftMotor.currentPosition());
  // }
  // leftMotor.run();

  // if (rightMotor.distanceToGo() == 0) 
  // {
  //   rightMotor.moveTo(-rightMotor.currentPosition());
  // }
  // rightMotor.run();

  // // check to see if it's time to move the servo
  // unsigned long currentMillis = millis();
  // if(currentMillis - previousMillis > SERVO_INTERVAL) {

  //   // save the last time
  //   previousMillis = currentMillis;   

  //   int pos = servo.read();

  //   if (pos == SERVO_CENTER)
  //   {
  //     servo.write(SERVO_LEFT);
  //   }
  //   else if (pos == SERVO_LEFT)
  //   {
  //     servo.write(SERVO_RIGHT);
  //   }
  //   else if (pos == SERVO_RIGHT)
  //   {
  //     servo.write(SERVO_CENTER);
  //   }
  // }
}

void setupMotors() 
{
  leftMotor.setMaxSpeed(MAX_SPEED);
  leftMotor.setSpeed(SPD_STOP);
  rightMotor.setMaxSpeed(MAX_SPEED);
  rightMotor.setSpeed(SPD_STOP);
}
