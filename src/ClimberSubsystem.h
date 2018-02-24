#pragma once

#include "ctre/Phoenix.h"
#include "CORERobotLib.h"
#include "COREHardware/COREJoystick.h"

class ClimberSubsystem {
public:
	ClimberSubsystem(COREJoystick * operatorJoystick);
	void robotInit();
	void teleopInit();
	void teleop();
	void startClimbing();
	void stopClimbing();
private:
	COREJoystick * m_operatorJoystick;
	TalonSRX m_climbMotor;
};
