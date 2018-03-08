#pragma once

#include <CORERobotlib.h>
#include <WPILib.h>

#include "ctre/Phoenix.h"
#include "COREFramework/COREScheduler.h"

using namespace CORE;

class ChainBarSubsystem : public CORESubsystem {
public:
	ChainBarSubsystem();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void setChainBar(double speed);
	void setRotation(double speed);
private:
	TalonSRX m_chainBarMotor, m_rotationMotor;
};
