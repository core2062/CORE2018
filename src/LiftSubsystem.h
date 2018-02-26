#pragma once

#include "ctre/Phoenix.h"
#include <CORERobotLib.h>
#include "COREHardware/COREJoystick.h"
#include "COREUtilities/COREConstant.h"

using namespace CORE;

class LiftSubsystem : public CORESubsystem {
public:
	LiftSubsystem();
	void robotInit();
	void teleopInit();
	void teleop();
	void isLifting();
	void setLift(double);
	void liftPosistion(double);
	TalonSRX m_leftLiftMotor;
	TalonSRX m_rightLiftMotor;
private:
	COREJoystick * m_operatorJoystick;
	int m_liftPosition;
	COREConstant<double> m_liftTopLimit;
	COREConstant<double> m_liftBottomLimit;
};
