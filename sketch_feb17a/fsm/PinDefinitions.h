/**
* This file contains a list of pin definitions we will be using in this project.
* 
*
* example #define pin1 1
*/

// motor control
#define MOTOR_LEFT_SPEED 4
#define MOTOR_RIGHT_SPEED 9

#define MOTOR_LEFT_DIR_A 5
#define MOTOR_RIGHT_DIR_A 7
#define MOTOR_LEFT_DIR_B 6
#define MOTOR_RIGHT_DIR_B 8

// brush
#define MOTOR_BRUSH_SPEED 10
// prop
#define PROP_ESC_SPEED 11

// limit switch input
#define LIMIT_SWITCH_1 52
#define LIMIT_SWITCH_2 50
#define LIMIT_SWITCH_3 48

// sonar
#define SONAR_TRIG1 46
#define SONAR_TRIG2 44
#define SONAR_TRIG3 42

#define SONAR_ECHO1 0 //Analogue Pins
#define SONAR_ECHO2 1 //Analogue Pins
#define SONAR_ECHO3 2 //Analogue Pins

// encoders
#define ENCODER_RIGHT_A 2 //Inturrupt
#define ENCODER_LEFT_A 18 //Inturrupt
#define ENCODER_RIGHT_B 3 //Inturrupt
#define ENCODER_LEFT_B 19 //Inturrupt

//9DOF Sensor
#define DOF9_SERIAL_SCL 21 //i2c scl pin
#define DOF9_SERIAL_SDA 20 //i2c sda pin

//Accel Sensor
#define ACCEL_LEFT_GUIDE 5 //Analogue Pins
#define ACCEL_LEFT_GUIDE 6 //Analogue Pins

// IR
#define IR_SIGNAL 3 //Analogue Pins

// Flex Lego Sensor
#define FLEX_SENSOR 4 //Analogue Pins

#define KILL_SWITCH 20 //Inturrupt
