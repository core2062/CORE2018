#include <CORERobotLib.h>
#include "CenterAuton.h"
#include "Actions.h"


CenterAuton::CenterAuton() :
	COREAuton("One Switch Two Scale Auton", 0.0) {
	m_moveToSwitch = new Node(5, new DriveDistanceAction());
	m_outtakeCubeToSwitch = new Node(5, new ScorerAction(scorerAction::OPEN));
	m_moveToCubeStack = new Node(5, new DriveDistanceAction());
	m_intakeCube = new Node(5, new IntakeAction());
	m_moveToScale = new Node(5, new DriveDistanceAction());
	m_liftUpToScale = new Node(5, new LiftAction(liftAction::SCALE));
	m_outtakeCubeToScale = new Node(5, new ScorerAction(scorerAction::OPEN));
	m_intakeSecondCube = new Node(5, new IntakeAction());
	m_driveToScaleSecondTime = new Node(5, new DriveDistanceAction());

}

void CenterAuton::addNodes() {
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
