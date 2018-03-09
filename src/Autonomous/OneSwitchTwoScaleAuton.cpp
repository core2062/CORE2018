#include <CORERobotLib.h>
#include <Autonomous/OneSwitchTwoScaleAuton.h>
#include "OneSwitchOneScaleAuton.h"
#include "Action/DropCubeAction.h"
#include "Action/IntakeCubeAction.h"
#include "Action/DriveDistanceAction.h"
#include "Action/DropCubeAction.h"

OneSwitchTwoScaleAuton::OneSwitchTwoScaleAuton() :
	COREAuton("One Switch Two Scale Auton", 0.0) {
	m_moveToSwitch = new Node(5, new DriveDistanceAction());
	m_outtakeCubeToSwitch = new Node(5, new DropCubeAction());
	m_moveToCubeStack = new Node(5, new DriveDistanceAction());
	m_intakeCube = new Node(5, new IntakeCubeAction());
	m_moveToScale = new Node(5, new DriveDistanceAction());
	m_liftUpToScale = new Node(5, new LiftUpToScaleAction());
	m_outtakeCubeToScale = new Node(5, new DropCubeAction());
	m_intakeSecondCube = new Node(5, new IntakeCubeAction());
	m_driveToScaleSecondTime = new Node(5, new DriveDistanceAction());

}

void OneSwitchTwoScaleAuton::addNodes() {
	m_moveToSwitch->addNext(m_outtakeCubeToSwitch);
	m_outtakeCubeToSwitch->addNext(m_moveToCubeStack);
	m_moveToCubeStack->addNext(m_intakeCube);
	m_intakeCube->addNext(m_moveToScale);
	m_moveToScale->addNext(m_liftUpToScale);
	m_liftUpToScale->addNext(m_outtakeCubeToScale);
	m_outtakeCubeToScale->addNext(m_driveToCubes);
	m_driveToCubes->addNext(m_intakeSecondCube);
	m_intakeSecondCube->addNext(m_driveToScaleSecondTime);
	m_driveToScaleSecondTime->addNext(m_outtakeSecondCube);
}
