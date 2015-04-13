#include <Arduino.h>

#define LM_PIN_1          3      // IN1, driver 1
#define LM_PIN_2          4      // IN2, driver 1
#define LM_PIN_3          5      // IN3, driver 1
#define LM_PIN_4          6      // IN4, driver 1
#define RM_PIN_1          7      // IN1, driver 2
#define RM_PIN_2          8      // IN2, driver 2
#define RM_PIN_3          9      // IN3, driver 2
#define RM_PIN_4          10     // IN4, driver 2
#define SERVO_PIN         11

#define ARDUINO1_ADDR     0x04
#define ARDUINO2_ADDR     0x05

#define SERVO_CENTER      90
#define SERVO_LEFT_MAX    160
#define SERVO_RIGHT_MAX   20
#define SERVO_STEP        10
#define SERVO_INTERVAL    5000

#define MAX_SPEED         1000.0
#define SPD_LEFT_FORWARD  -750.0
#define SPD_LEFT_BACK     750.0
#define SPD_LEFT_LEFT	  400.0
#define SPD_LEFT_RIGHT    -400.0
#define SPD_RIGHT_FORWARD 750.0
#define SPD_RIGHT_BACK    -750.0
#define SPD_RIGHT_LEFT	  400.0
#define SPD_RIGHT_RIGHT   -400.0
#define SPD_STOP		  0.0

#define MOVE_FORWARD      10
#define MOVE_BACK         11
#define MOVE_LEFT         12
#define MOVE_RIGHT        13
#define MOVE_STOP		  14

#define PAN_CENTER        20
#define PAN_LEFT          21
#define PAN_RIGHT         22

#define STATUS_OK         42
