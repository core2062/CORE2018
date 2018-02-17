#pragma once

#include "ctre/Phoenix.h"
#include "CORERobotLib.h"
#include "Robot.h"

class LiftSubsystem {
public:
	LiftSubsystem();
	void robotInit();
	void autonInit();
	void auton();
	void teleopInit();
	void teleop();
	void isLifting();
	void setLift(double);
	TalonSRX *m_leftLiftMotor;
	TalonSRX *m_rightLiftMotor;
private:
	int m_liftPosition;
	int m_leftYJoystickPosition;
	COREConstant<double> m_liftTopLimit;
	COREConstant<double> m_liftBottomLimit;
};
