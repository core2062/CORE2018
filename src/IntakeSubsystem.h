#pragma once

#include "ctre/Phoenix.h"
#include "CORERobotLib.h"

class IntakeSubsystem {

public:
	IntakeSubsystem();
	void robotInit();
	void autonInit();
	void auton();
	void teleopInit();
	void teleop();
	bool isIntaking();
	void startIntake();
	void stopIntake();
	//COREJoystick *m_intakeJoystick;
	TalonSRX m_leftIntakeMotor;
	TalonSRX m_rightIntakeMotor;
private:
	bool m_isIntaking;


};


