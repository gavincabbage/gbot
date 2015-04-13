// arduino2/sketch.cpp
// servo subsystem

#include "../gbot.h"

Servo servo;
int servoDirection = SERVO_CENTER;
int status = STATUS_OK;

void receiveData(int byteCount);
void sendData();
void servo_left();
void servo_right();
void servo_center();

void setup()
{
   servo.attach(SERVO_PIN);
   servo.write(SERVO_CENTER);
   Wire.begin(ARDUINO2_ADDR);
   Wire.onReceive(receiveData);
   Wire.onRequest(sendData);
}

void loop()
{
    delay(100)
}

void receiveData(int byteCount)
{
   while (Wire.available())
   {
     int result = Wire.read();
     switch (result)
     {
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

void sendData()
{
    Wire.write(status);
}

void servo_left()
{
   servoDirection = servoDirection + SERVO_STEP > SERVO_LEFT_MAX ?
                    SERVO_LEFT_MAX : servoDirection + SERVO_STEP;
   servo.write(servoDirection);
}

void servo_right()
{
   servoDirection = servoDirection - SERVO_STEP > SERVO_RIGHT_MAX ?
                    SERVO_RIGHT_MAX : servoDirection - SERVO_STEP;
   servo.write(servoDirection);
}

void servo_center()
{
   servoDirection = SERVO_CENTER;
   servo.write(servoDirection);
}
