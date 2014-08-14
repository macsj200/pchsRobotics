#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     fl,            tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     fr,            tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     br,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     bl,            tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Motor config

////////////////////////////////Current pchs teleop code 12/20/2013

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "ButtonsDefs.h"  //Buttons definitions

void initializeRobot()//initialize
{
	return;
}

task raiseLowerLift(){
	while(true){
		//do stuff to do stuff
	}
}


task main()
{
	float speed = 1.00;

	initializeRobot();

	waitForStart();   // wait for start of tele-op phase

	StartTask(raiseLowerLift);

	while (true)
	{
		getJoystickSettings(joystick);

		if(joystick.joy1_Buttons == button_a){
			speed = 1.00;
		}
		else if(joystick.joy1_Buttons == button_b){
			speed = 0.75;
		}
		else if(joystick.joy1_Buttons == button_x){
			speed = 0.50;
		}
		else if(joystick.joy1_Buttons == button_y){
			speed = 0.25;
		}

		if(joystick.joy1_TopHat == pov_north){
			motor[fr] = 100 * speed;
			motor[fl] = 100 * speed;
			motor[br] = -100 * speed;
			motor[bl] = -100 * speed;
		}
		else if(joystick.joy1_TopHat == pov_south){
			motor[fr] = -100 * speed;
			motor[fl] = -100 * speed;
			motor[br] = 100 * speed;
			motor[bl] = 100 * speed;
		}
		else if(joystick.joy1_TopHat == pov_east){
			motor[fr] = 100 * speed;
			motor[fl] = 100 * speed;
			motor[br] = 100 * speed;
			motor[bl] = 100 * speed;
		}
		else if(joystick.joy1_TopHat == pov_west){
			motor[fr] = -100 * speed;
			motor[fl] = -100 * speed;
			motor[br] = -100 * speed;
			motor[bl] = -100 * speed;
		}
		else if(joystick.joy1_Buttons == button_right_trigger){
			motor[fr] = 100 * speed;
			motor[fl] = -100 * speed;
			motor[br] = -100 * speed;
			motor[bl] = 100 * speed;
		}
		else if(joystick.joy1_Buttons == button_left_trigger){
			motor[fr] = -100 * speed;
			motor[fl] = 100 * speed;
			motor[br] = 100 * speed;
			motor[bl] = -100 * speed;
		}
		else{
			motor[fr] = 0;
			motor[fl] = 0;
			motor[br] = 0;
			motor[bl] = 0;
		}

		//spin flag
		if(joystick.joy1_Buttons == button_a){
			//motor[spinner] = 100 * speed;
		}
		else if(joystick.joy1_Buttons == button_b){
			//motor[spinner] = -100 * speed;
		}
		else{
			//motor[spinner] = 0;
		}

		//dump crap
		if(joystick.joy2_TopHat == pov_east){
			//do dc stuff
		}
		if(joystick.joy2_TopHat == pov_west){
			//do dc stuff
		}
	}
}