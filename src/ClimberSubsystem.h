#pragma once

#include "ctre/Phoenix.h"
#include "CORERobotLib.h"
class ClimberSubsystem {

public:
	ClimberSubsystem();
	void robotInit();
	void teleopInit();
	void teleop();
	bool isClimbing();
	void startClimbing();
	void stopClimbing();
	//COREJoystick *m_climberJoystick;
private:
	bool m_isClimbing;
	TalonSRX m_climbMotor;
};

