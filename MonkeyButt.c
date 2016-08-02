#pragma config(Sensor, in1,    Yaw,            sensorGyro)
#pragma config(Motor,  port1,           ClawArm1,      tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           RightFront,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           RightBack,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           Lift1,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           Lift2,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           Lift3,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           Lift4,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           LeftBack,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           LeftFront,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          ClawArm2,      tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "Vex_Competition_Includes.c";

void gyroBias(long totalBias =0)
{
	SensorType[Yaw] = sensorNone;
	for(int i=0; i<2000; i++)
	{
		totalBias += SensorValue[Yaw];
	}
	SensorType[Yaw] = sensorGyro;
	SensorBias[Yaw] = totalBias/2000;
}

void pre_auton()
{
	gyroBias();
}

void motorspeed(string *motorgroup, int speed)//motorgoup is the word, speed is a value
{
	switch(strIndex(*motorgroup, 0))
	{
		case 'r'://call with motorspeed("right", speed);
		motor[RightBack] = speed;//Insert mootors for the right drive here
		motor[RightFront] = speed;
		break;

		case 'l'://call with motorspeed("left", speed)
		motor[LeftBack] = speed;//insert motors for the left drive here
		motor[LeftFront] = speed;
		break;

		case 'h'://call with motorspeed("height", speed)
		motor[Lift1] = speed;//insert lift motors here
		motor[Lift2] = speed;
		motor[Lift3] = speed;
		motor[Lift4] = speed;
		break;

		default:
		break;
	}
}

task autonomous()
{
}

task usercontrol()
{
	while(true)
	{
		motorspeed("right" , vexRT[Ch2]);
		motorspeed("left", vexRT[Ch3]);
	}
}