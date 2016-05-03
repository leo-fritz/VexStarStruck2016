#pragma config(sensor, dgtl1, FlyWheel, sensorQuadEncoder)

int TargetSpeed[4] = {0, 269, 297, 365};//Desired Encoder Value
int Error = 0;//The difference between desired value and sensor data
float Kp[4] = {0, 0.79, 0.56, 0.8};//Error conversion values, tuning constants
float KpError = 0;//Use this to see how much Error is controlling the PID
long Integral[4] = {0, 0, 0, 0};//Total sum of all errors
float Ki[4] = {0, 0.13, 0.07, 0.004};//Integral conversion values, tuning constants
float KiIntegral = 0;//Use this to see how much Integral is controlling the PID
int DeltaE = 0;//Change in Error, Last minus now
float Kd[4] = {0, 0.69, 0.63, 0.84};//DeltaE conversion values, tuning constants
float KdDeltaE = 0;//Use this to see how much DeltaE is controlling the PID
int PrevError = 0;//Last error value
int stillspeed[4] = {0, 25, 30, 45};//base value of the PID, it adds or subtracts from this
int PIDPower = 0;
int AccError[4]  = {-1, 30, 25, 10};//Decides between PID and BangBang
int BangBang = 0;
int PIDBang = 0;
int Flyspeed = 0;//Final state
TVexJoysticks buttons[4] = {Btn8D, Btn7U, Btn7R, Btn7D};//Selection buttons 0 - 3 for ranges
int n = 0;//Choice variable

task PIDControl()
{
	while(true)
	{
		SensorValue[FlyWheel] = 0;//Measure difference
		releaseCPU();//Oinkless: Do other stuff
		wait1Msec(PI*20);//TimeSample to end all time samples
		hogCPU();//Oink: Do nothing else
		Error = TargetSpeed[n] - SensorValue[FlyWheel];//How much I'm wrong
		datalogAddValue(0, Error);//DATADATADATADATADATADATADATADATADATADATADATADATA
		KpError = Kp[n]*Error;//Debuggery & Tuning
		Integral[n] += (Error + PrevError)/2;//How wrong I've been
		datalogAddValue(1, Integral[n]);//DATADATADATADATADATADATADATADATADATADATADATADATA
		KiIntegral = Ki[n]*Integral[n];//Debuggery & Tuning
		DeltaE = PrevError - Error;//How much less wrong I am
		datalogAddValue(2, DeltaE);//DATADATADATADATADATADATADATADATADATADATADATADATA
		KdDeltaE = Kd[n]*DeltaE;//Debuggery & Tuning
		PrevError = Error;//What it says on the tin
		PIDPower = KpError + KdDeltaE + KiIntegral + stillspeed[n];//PID Equation
		BangBang = Error > 0 ? 127 : 0;//On or Off, Pure Binary
		PIDBang = abs(Error)>AccError[n] ? BangBang : PIDPower;//Axiom of choice
	  Flyspeed = PIDBang<0?0:PIDBang*(n==0?0:1);//Limit the flywheel to whole numbers and keep 0 range from doing anything
	}
}

task main()
{
	startTask(PIDControl);
	while(true)
	{
		for(int i = 0; i<=3; i++)
		{
			n = vexRT[buttons[i]] == 1 ? i : n;//Select speed
		}
	}
}
