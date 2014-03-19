#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S2,     lightFR,        sensorLightActive)
#pragma config(Sensor, S3,     lightFL,        sensorLightActive)
#pragma config(Sensor, S4,     HTSMUX,         sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     fr,            tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     fl,            tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     bl,            tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     br,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     liftA,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     liftB,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     holder,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     flagspinner,   tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "hitechnic-sensormux.h"
#include "hitechnic-irseeker-v2.h"
#include "lego-ultrasound.h"

#define sonicSensor              msensor_S4_1
#define frontRightIR              msensor_S4_3
#define frontLeftIR              msensor_S4_2
#define backRightIR              msensor_S4_4

const int FRONT_ON_TAPE = 350;
const int BACK_ON_TAPE = 340;
int ontape = 340;

bool tapeify();

task burp(){
	motor[liftA] = 100;
	motor[liftB] = 100;
	wait10Msec(450);
	motor[liftA] = 0;
	motor[liftB] = 0;
}

void initializeRobot(){
	bFloatDuringInactiveMotorPWM = false;
	return;
}

void liftUp(){
	motor[liftA] = 100;
	motor[liftB] = 100;
	wait10Msec(450);
	motor[liftA] = 0;
	motor[liftB] = 0;
}

void takeDump(){
	motor[holder] = -40;
	wait1Msec(350);
	motor[holder] = 0;
	wait1Msec(700);
	motor[holder] = 40;
	wait1Msec(249);
	motor[holder]= 0;
}

task floooop(){
	for(int i = 0; i < 20000; i++){
		PlayTone(i, 5);
	}
}

task fleeeep(){
	for(int i = 20000; i > 20; i--){
		PlayTone(i, 5);
	}
}


void liftUpAndDownAndTakeDumpAndForward(){
	motor[fr] = 25;
	motor[fl] = 25;
	motor[br] = 25;
	motor[bl] = 25;

	wait10Msec(30);

	motor[fr] = 0;
	motor[fl] = 0;
	motor[br] = 0;
	motor[bl] = 0;

	motor[liftA] = 100;
	motor[liftB] = 100;
	wait1Msec(2150);
	motor[liftA] = 0;
	motor[liftB] = 0;

	takeDump();

	motor[fr] = -25;
	motor[fl] = -25;
	motor[br] = -25;
	motor[bl] = -25;

	wait10Msec(3);


	motor[fr] = -0;
	motor[fl] = -0;
	motor[br] = -0;
	motor[bl] = -0;

	motor[fr] = 0;
	motor[fl] = -0;
	motor[br] = 0;
	motor[bl] = 0;
}
task updateDisplay(){
	while(true){
		nxtDisplayTextLine(1, "%d" ,SensorRaw[lightFR]);
		nxtDisplayTextLine(2, "%d" ,HTIRS2readACDir(backRightIR));
		nxtDisplayTextLine(3, "%d" ,HTIRS2readACDir(frontRightIR));
		nxtDisplayTextLine(4, "%d" ,USreadDist(sonicSensor));
	}
}

bool tapeify(){
	//while(false){
	//drive forward until left light loses tape and scan for IR beacon

	bool probablyOffTape = false;


	if(SensorRaw[lightFR]  >= ontape){
		motor[fr] = 10;
		motor[fl] = 15;
		motor[br] = 10;
		motor[bl] = 15;
	}
	else{
		ClearTimer(T1);
		int timeCorrection = 0;
		while(SensorRaw[lightFR]  <= ontape){
			motor[fr] = 20;
			motor[fl] = 0;
			motor[br] = 20;
			motor[bl] = 0;
			if(time1[T1] > 300){
				probablyOffTape = true;
				break;
			}
		}
		timeCorrection = time1[T1];
		ClearTimer(T1);
		while(time1[T1] < timeCorrection){
			motor[fr] = 0;
			motor[fl] = 20;
			motor[br] = 0;
			motor[bl] = 20;
		}

		return probablyOffTape;
	}
}
void irify(){
	PlaySound(soundBeepBeep);
	motor[fr] = 0;
	motor[fl] = 0;
	motor[br] = 0;
	motor[bl] = 0;
	wait1Msec(1000);

	//4 is an assnumber
	//HTIRS2readACDir(frontLeftIR) > 4
	ClearTimer(T1);
	while(time1[T1] < 1700){
		motor[fr] = -25;
		motor[fl] = 25;
		motor[br] = -25;
		motor[bl] = 25;
	}

	int burptits = USreadDist(sonicSensor);

	StartTask(floooop);

	while(USreadDist(sonicSensor)   >22){
		motor[fr] = 15;
		motor[fl] = 20;
		motor[br] = 15;
		motor[bl] = 20;
	}

	StartTask(fleeeep);



	motor[fr] = 0;
	motor[fl] = 0;
	motor[br] = 0;
	motor[bl] = 0;

	liftUpAndDownAndTakeDumpAndForward();


	//if while = -sqrt(true then) <false =int sound beepbeep, while motor(fl)= while then staet task 5falsel fleep probably off tape(x) true
	ClearTimer(T1);
	while(time1[T1] < 1700){
		motor[fr] = 25;
		motor[fl] = -25;
		motor[br] = 25;
		motor[bl] = -25;
	}
}

task main()
{
	bool probablyOffTape = false;
	initializeRobot();


	motor[motorA] = -50;

	wait1Msec(700);

	StartTask(updateDisplay);

	motor[fr] = 0;
	motor[fl] = 0;
	motor[br] = 0;
	motor[bl] = 0;


	/*while(true){
	if(HTIRS2readACDir(frontRightIR) == 9 && HTIRS2readACDir(backRightIR) == 5){
	irify();
	break;
	}
	else{
	probablyOffTape = tapeify();
	}
	}*/

	//Drive forward until backRightIR reads 5 (time this)
	ClearTimer(T1);
	while(HTIRS2readACDir(backRightIR) != 5){
		motor[fr] = 20;
		motor[fl] = 21;
		motor[br] = 20;
		motor[bl] = 21;
	}
	int bitchtits = time1[T1];
	//End timer

	motor[fr] = -0;
	motor[fl] = 0;
	motor[br] = -0;
	motor[bl] = 0;

	wait1Msec(500);

	//Turn time to go perpendicular to crates
	int turntits = 1100;

	//Turn for turntits ms
	ClearTimer(T1);
	while(time1[T1] < turntits){
		motor[fr] = -30;
		motor[fl] = 30;
		motor[br] = -30;
		motor[bl] = 30;
	}



	int tits = USreadDist(sonicSensor);

	StartTask(floooop);

	//Drive forward to the blocks for turds ms
	int turds = 600;

	ClearTimer(T1);
	while(time1[T1] < turds){
		motor[fr] = 15;
		motor[fl] = 22;
		motor[br] = 15;
		motor[bl] = 22;
	}

	StartTask(fleeeep);



	motor[fr] = 0;
	motor[fl] = 0;
	motor[br] = 0;
	motor[bl] = 0;

	//What it looks like
	liftUpAndDownAndTakeDumpAndForward();

	//Back up as much as you drove forward
	ClearTimer(T1);
	while(time1[T1] < turds){
		motor[fr] = -15;
		motor[fl] = -22;
		motor[br] = -15;
		motor[bl] = -22;
	}

	motor[fr] = -0;
	motor[fl] = -0;
	motor[br] = -0;
	motor[bl] = -0;

	motor[liftA] = -100;
	motor[liftB] = -100;
	wait1Msec(1800);
	motor[liftA] = 0;
	motor[liftB] = 0;

	//Turn 200 ms less than turntits to go parallel to crates
	ClearTimer(T1);
	while(time1[T1] < turntits - 200){
		motor[fr] = 30;
		motor[fl] = -30;
		motor[br] = 30;
		motor[bl] = -30;
	}

	//back up 200 ms less than we went forward to get ir
	ClearTimer(T1);
	while(time1[T1] < bitchtits - 200){
		motor[fr] = -20;
		motor[fl] = -22;
		motor[br] = -20;
		motor[bl] = -22;
	}

	// im writing ofr yaaaa bbay

	/*while(HTIRS2readACDir(backRightIR) != 5 && HTIRS2readACDir(frontRightIR) != 3){
	if(SensorRaw[lightFR] > ontape && SensorRaw[lightFL] < ontape){
	motor[fr] = 10;
	motor[fl] = 15;
	motor[br] = 10;
	motor[bl] = 15;
	}
	else if(SensorRaw[lightFR] < ontape && SensorRaw[lightFL] > ontape){
	motor[fl] = 10;
	motor[fr] = 15;
	motor[bl] = 10;
	motor[br] = 15;


	}
	else{
	motor[fr] = 10;
	motor[fl] = 15;
	motor[br] = 10;
	motor[bl] = 15;

	}
	//	PlaySound(soundBeepBeep);
	}*/

	motor[fr] = 0;
	motor[fl] = 0;
	motor[br] = 0;
	motor[bl] = 0;

	//Turn for certain ms to grab blocks
	ClearTimer(T1);
	while(time1[T1] < 1200){
		motor[fr] = -30;
		motor[fl] = 33;
		motor[br] = -30;
		motor[bl] = 33;
	}

	//lower block holder
	ClearTimer(T1);
	while(time1[T1] < 300){
		motor[holder] = -15;
	}

	motor[holder] = -0;

	//Drive forward for certain ms to grab blocks
	ClearTimer(T1);
	while(time1[T1] < 3100){
		motor[fr] = 30;
		motor[fl] = 33;
		motor[br] = 30;
		motor[bl] = 33;
	}

	motor[fr] = 0;
	motor[fl] = 0;
	motor[br] = 0;
	motor[bl] = 0;
	wait1Msec(70);

	//raise holder while backing up
	ClearTimer(T1);
	while(time1[T1] < 340){
		motor[holder] = 30;
		motor[fr] = -30;
		motor[fl] = -33;
		motor[br] = -30;
		motor[bl] = -33;
	}

	//keep raising holder
	ClearTimer(T1);
	while(time1[T1] < 40){
		motor[holder] = 30;
	}

	motor[holder] = -0;

	motor[fr] = -0;
	motor[fl] = 0;
	motor[br] = 0;
	motor[bl] = 0;

	//Turn to get onto ramp n shit
	ClearTimer(T1);
	while(time1[T1] < 720){
		motor[fr] = -30;
		motor[fl] = 33;
		motor[br] = -30;
		motor[bl] = 33;
	}

	//Back on to ramp ;)
	ClearTimer(T1);
	while(time1[T1] < 2800){
		motor[fr] = -30;
		motor[fl] = -33;
		motor[br] = -30;
		motor[bl] = -33;
	}

	motor[fr] = 0;
	motor[fl] = 0;
	motor[br] = 0;
	motor[bl] = 0;


	while(true){}

}
