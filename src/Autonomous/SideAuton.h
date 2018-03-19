
#pragma once

#include <memory>

#include <CORERobotLib.h>

#include "Actions.h"
#include <WPILib.h>
#include "Autonomous/GameDataParser.h"

using namespace CORE;
enum cubePlacement {
	SWITCH1SCALE1,
	SWITCH1SCALE2
};
class SideAuton : COREAuton {
	SideAuton();
	void addNodes() override;

private:
	Node * m_moveToRightSwitch = nullptr;
	Node * m_moveToLeftSwitch = nullptr;
//	Node * m_moveToSwitch = nullptr;
	Node * m_outtakeCubeToSwitch = nullptr;
	Node * m_moveToCubeStackFromRight = nullptr;
	Node * m_moveToCubeStackFromLeft = nullptr;
	Node * m_intakeCube = nullptr;
	Node * m_moveToRightScale = nullptr;
	Node * m_moveToLeftScale = nullptr;
//	Node * m_moveToScale = nullptr;
	Node * m_liftUpToScale = nullptr;
	Node * m_outtakeCubeToScale = nullptr;
	Node * m_driveToCubesFromLeft = nullptr;
	Node * m_driveToCubesFromRight = nullptr;
//	Node * m_driveToCubes = nullptr;
	Node * m_intakeSecondCube = nullptr;
	Node * m_driveToRightScaleSecondTime = nullptr;
	Node * m_driveToLeftScaleSecondTime = nullptr;
//	Node * m_driveToScaleSecondTime = nullptr;
	Node * m_liftUpToScaleSecondTime = nullptr;
	Node * m_outtakeSecondCube = nullptr;
	GameDataParser gameDataParser;
	SendableChooser<cubePlacement> *m_cubePlacementChooser;
	COREAuton* m_cubePlacement;
	side m_gameOrientation;

};
