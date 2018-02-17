#pragma once

#include "ctre/Phoenix.h"
#include "CORERobotLib.h"
#include "Robot.h"
class ClimberSubsystem {

public:
	ClimberSubsystem();
	void robotInit();
	void teleopInit();
	void teleop();
	bool isClimbing();
	void startClimbing();
	void stopClimbing();
private:
	bool m_isClimbing;
	TalonSRX m_climbMotor;
};

