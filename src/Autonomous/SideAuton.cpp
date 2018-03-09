
#include "SideAuton.h"
#include "Autonomous/Action/ScorerAction.h"
#include "Autonomous/Action/IntakeAction.h"
#include "Action/DriveDistanceAction.h"
#include "Autonomous/Action/ScorerAction.h"

SideAuton::SideAuton() :
	COREAuton("One switch one scale auton") {
	m_moveToSwitch = new Node(5, new DriveDistanceAction());
	m_outtakeCubeToSwitch = new Node(5, new ScorerAction(scorerAction::OPEN));
	m_moveToCubeStack = new Node(5, new DriveDistanceAction());
	m_intakeCube = new Node(5, new IntakeAction());
	m_moveToScale = new Node(5, new DriveDistanceAction());
	m_liftUpToScale = new Node(5, new LiftAction(liftAction::SCALE));
	m_outtakeCubeToScale = new Node(5, new ScorerAction(scorerAction::OPEN));
}

void SideAuton::addNodes() {
	m_moveToSwitch->addNext(m_outtakeCubeToSwitch);
	m_outtakeCubeToSwitch->addNext(m_moveToCubeStack);
	m_moveToCubeStack->addNext(m_intakeCube);
	m_intakeCube->addNext(m_moveToScale);
	m_moveToScale->addNext(m_liftUpToScale);
	m_liftUpToScale->addNext(m_outtakeCubeToScale);
}

