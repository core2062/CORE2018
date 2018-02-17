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
	void startClimbing();
	void stopClimbing();
private:
	TalonSRX m_climbMotor;
};
