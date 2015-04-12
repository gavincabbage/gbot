// arduino1/sketch.cpp
// stepper motor subsystem

#include <Wire.h>
#include <AccelStepper.h>

#include "../gbot.h"

#define SLAVE_ADDRESS 0x04

AccelStepper leftMotor(AccelStepper::HALF4WIRE, LM_PIN_1, LM_PIN_3, LM_PIN_2, LM_PIN_4);
AccelStepper rightMotor(AccelStepper::HALF4WIRE, RM_PIN_1, RM_PIN_3, RM_PIN_2, RM_PIN_4);
int motorMode = MOVE_STOP;
int status = STATUS_OK;

void setup_motors();
void receiveData(int byteCount);
void sendData();

void setup()
{
    setup_motors();
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);
}

void loop()
{
    leftMotor.runSpeed();
    rightMotor.runSpeed();
}

void receiveData(int byteCount)
{
   while (Wire.available())
   {
     int result = Wire.read();
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
       default:
         break;
     }
   }
}

void sendData()
{
    Wire.write(status);
}

void setup_motors()
{
  leftMotor.setMaxSpeed(MAX_SPEED);
  leftMotor.setSpeed(SPD_STOP);
  rightMotor.setMaxSpeed(MAX_SPEED);
  rightMotor.setSpeed(SPD_STOP);
}
