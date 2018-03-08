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
	void outtakeCube();
	bool m_isCubeInIntake = false;
private:
	bool m_hasEjected = false;
	DoubleSolenoid m_frontLeftSolenoid, m_frontRightSolenoid, m_backRightSolenoid, m_backLeftSolenoid;
	TalonSRX m_leftArmMotor, m_rightArmMotor, m_cubeRotatorMotor;
};
