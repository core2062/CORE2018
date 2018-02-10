#pragma once

#include "ctre/Phoenix.h"
#include "CORERobotLib.h"

class LiftSubsystem {
public:
	LiftSubsystem();
	void robotInit();
	void autonInit();
	void auton();
	void teleopInit();
	void teleop();
	bool isLifting();
	bool isLiftDown();
	void startLift();
	void stopLift();
	TalonSRX m_leftLiftMotor;
	TalonSRX m_rightLiftMotor;
	DoubleSolenoid m_
	//COREJoystick *m_liftJoystick;
private:
	bool m_isLifting;
	int m_liftPosition;
	double m_liftTopLimit; //TODO Change to COREConstants
	double m_liftBottomLimit; //TODO Change to COREConstants

};
