#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     fr,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     br,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     upDownR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     bl,            tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     fl,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     cLift,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     upDownL,       tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Motor config

////////////////////////////////Current pchs teleop code 10/29/2013

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "ButtonsDefs.h"  //Buttons definitions

const float MAX_JOYSTICK = 128.0;//used to scale joystick vectors out of 1
float motorScale = 100; //variable to scale the max motor power that is tolerated
int servoPos = 90;// default servo position = 90 /255
void initializeRobot()//initialize
{
  return;
}

float scaleJoystick(int n){
	return (n / MAX_JOYSTICK)	* motorScale; //scale the joysticks out of 100 rather than 128

}


task main()
{
  initializeRobot();

  waitForStart();   // wait for start of tele-op phase

  while (true)
  {
  	getJoystickSettings(joystick);
////////CUBE LIFT///////////
  	if(joystick.joy1_TopHat == pov_north){
  		motor[upDownL] = -100;
  		motor[upDownR] = -100;
  	}
  	else if(joystick.joy1_TopHat == pov_south){
  		motor[upDownR] = 100;
  		motor[upDownL] = 100;
  	}
  	else{
 		motor[cLift] = 0;
 			motor[upDownR] = 0;
  		motor[upDownL] = 0;
  		////////////////////
  	}
//rotate left
  	if(joystick.joy1_Buttons == button_left_button){
  		motor[fr] = 100;
  		motor[fl] = -100;
  		motor[br] = 100;
  		motor[bl] = -100;
  	}

// rotate left

  	if(joystick.joy1_Buttons == button_right_button){
  		motor[fr] = 100;
  		motor[fl] = 100;
  		motor[br] = 100;
  		motor[bl] = 100;
  	}
//put in a way to limit max motor power -- either 25% or 100%
	if(joystick.joy1_Buttons == button_left_trigger ){
  		motorScale = 25;

  	}
  	if(joystick.joy1_Buttons == button_right_trigger ){
  		motorScale = 100;

  	}

  	//end  max motor power scaling

  	//Start useless ultrasonic rotator function
  	if(joystick.joy1_TopHat == pov_east){
  servoPos = servoPos + 1;
  }
  if(joystick.joy1_TopHat == pov_west){
  servoPos = servoPos - 1;

  }
  //servo[SensSwivel] = servoPos;
  //end useless ultrasonic rotator functions
  //	motor[updownL] = joystick.joy1_y2;
  //	motor[updownR] = joystick.joy1_y2;

  	int y_vals = scaleJoystick(joystick.joy1_y1);
  	int x_vals = scaleJoystick(joystick.joy1_x1);

  	///////////////Start derp math
  	motor[fl] = x_vals + y_vals;
  	motor[br] = x_vals + y_vals;

  	motor[fr] = y_vals - x_vals;
  	motor[bl] = y_vals - x_vals;
  	/////////////////End derp math
  }
}
