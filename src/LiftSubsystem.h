#pragma once

#include "ctre/Phoenix.h"
#include <CORERobotLib.h>
#include "COREHardware/COREJoystick.h"

class LiftSubsystem {
public:
	LiftSubsystem(COREJoystick * operatorJoystick);
	LiftSubsystem();
	void robotInit();
	void teleopInit();
	void teleop();
	void isLifting();
	void setLift(double);
	void liftPosistion(double);
	TalonSRX m_leftLiftMotor;
	TalonSRX m_rightLiftMotor;
	double m_liftPosition;
	COREConstant<double> m_liftBottomLimit;
private:
	COREJoystick * m_operatorJoystick;
	COREConstant<double> m_liftTopLimit;
};
