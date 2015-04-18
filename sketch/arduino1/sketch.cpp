// arduino1/sketch.cpp
// stepper motor subsystem

#include <Wire.h>
#include <AccelStepper.h>

#include "../gbot.h"



/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}





// AccelStepper leftMotor(AccelStepper::HALF4WIRE, LM_PIN_1, LM_PIN_3, LM_PIN_2, LM_PIN_4);
// AccelStepper rightMotor(AccelStepper::HALF4WIRE, RM_PIN_1, RM_PIN_3, RM_PIN_2, RM_PIN_4);
// int motorMode = MOVE_STOP;
// int status = STATUS_OK;

// void move_forward();
// void move_back();
// void move_left();
// void move_right();
// void move_stop();
// void move(int, int, int);
// void receiveData(int);
// void sendData();
// void setup_motors();

// void setup()
// {
//     setup_motors();
//     Wire.begin(ARDUINO1_ADDR);
//     Wire.onReceive(receiveData);
//     Wire.onRequest(sendData);
// }

// void loop()
// {
//     leftMotor.runSpeed();
//     rightMotor.runSpeed();
// }

// void receiveData(int byteCount)
// {
//     while (Wire.available())
//     {
//         switch (Wire.read())
//         {
//         case MOVE_FORWARD:
//             move_forward();
//             break;
//         case MOVE_BACK:
//             move_back();
//             break;
//         case MOVE_LEFT:
//             move_left();
//             break;
//         case MOVE_RIGHT:
//             move_right();
//             break;
//         case MOVE_STOP:
//             move_stop();
//             break;
//         }
//     }
// }

// void move_forward()
// {
//     move(SPD_LEFT_FORWARD, SPD_RIGHT_FORWARD, MOVE_FORWARD);
// }

// void move_back()
// {
//     move(SPD_LEFT_BACK, SPD_RIGHT_BACK, MOVE_BACK);
// }

// void move_left()
// {
//     move(SPD_LEFT_LEFT, SPD_RIGHT_LEFT, MOVE_LEFT);
// }

// void move_right()
// {
//     move(SPD_LEFT_RIGHT, SPD_RIGHT_RIGHT, MOVE_RIGHT);
// }

// void move_stop()
// {
//     move(SPD_STOP, SPD_STOP, MOVE_STOP);
// }

// void move(int left_direction, int right_direction, int mode)
// {
//     leftMotor.setSpeed(left_direction);
//     rightMotor.setSpeed(right_direction);
//     motorMode = mode;
// }

// void sendData()
// {
//     Wire.write(status);
// }

// void setup_motors()
// {
//     leftMotor.setMaxSpeed(MAX_SPEED);
//     leftMotor.setSpeed(SPD_STOP);
//     rightMotor.setMaxSpeed(MAX_SPEED);
//     rightMotor.setSpeed(SPD_STOP);
// }
