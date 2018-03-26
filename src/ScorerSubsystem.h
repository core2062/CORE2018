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
	void closeScorer();
	void openScorer();
	bool cubeInScorer();

private:
	DoubleSolenoid m_scorerSolenoid;
	DigitalInput m_photoEye;
	bool m_scorerClosed;
};
