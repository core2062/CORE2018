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
	Node * m_dropCube = nullptr;
	Node * m_intakeCube = nullptr;
	Node * m_dropCubeSecondTime = nullptr;
	Node * m_moveToScale = nullptr;
	Node * m_raiseToScale = nullptr;
	Node * m_driveForward = nullptr;
};
