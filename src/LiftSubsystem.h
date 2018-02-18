#pragma once

#include "ctre/Phoenix.h"
#include <CORERobotLib.h>
#include "Robot.h"
#include "COREHardware/COREJoystick.h"

class LiftSubsystem {
public:
	LiftSubsystem(COREJoystick * operatorJoystick);
	void robotInit();
	void teleopInit();
	void teleop();
	void isLifting();
	void setLift(double);
	TalonSRX *m_leftLiftMotor;
	TalonSRX *m_rightLiftMotor;
private:
	COREJoystick * m_operatorJoystick;
	int m_liftPosition;
	int m_leftYJoystickPosition;
	COREConstant<double> m_liftTopLimit;
	COREConstant<double> m_liftBottomLimit;
};
