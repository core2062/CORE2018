#pragma once

#include <memory>

#include <CORERobotLib.h>

#include "Actions.h"
#include <WPILib.h>
#include "Autonomous/GameDataParser.h"

using namespace CORE;

class SideAuton : COREAuton {
public:
	SideAuton();
	void addNodes() override;

private:
	Node * m_moveToSwitch = nullptr;
//	Node * m_liftUpToSwitch = nullptr;
	Node * m_outtakeCubeToSwitch = nullptr;
	Node * m_moveToCubeStack = nullptr;
	Node * m_intakeCube = nullptr;
	Node * m_moveToScale = nullptr;
//	Node * m_liftUpToScale = nullptr;
	Node * m_outtakeCubeToScale = nullptr;
	Node * m_driveToCubes = nullptr;
	Node * m_intakeSecondCube = nullptr;
	Node * m_driveToScaleSecondTime = nullptr;
//	Node * m_liftUpToScaleSecondTime = nullptr;
	Node * m_outtakeSecondCube = nullptr;
};
