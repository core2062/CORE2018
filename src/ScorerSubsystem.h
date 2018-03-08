#pragma once

#include "ctre/Phoenix.h"
#include "WPILib.h"
#include <CORERobotLib.h>
#include "COREFramework/COREScheduler.h"


using namespace CORE;

class ScorerSubsystem  : public CORESubsystem {
public:
	ScorerSubsystem();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void rotateSetCube(double);
	void intakeCube();
	void outakeCube();
	bool m_isCubeInIntake;
private:
	DoubleSolenoid m_frontLeftSolenoid, m_frontRightSolenoid, m_backRightSolenoid, m_backLeftSolenoid;
	TalonSRX m_leftArmMotor, m_rightArmMotor, m_cubeRotatorMotor;
};
