#include <CORERobotLib.h>
#include "CenterAuton.h"
#include "Actions.h"


CenterAuton::CenterAuton() :
	COREAuton("Three cubes in exchange auton", 0.0) {
	m_outtakeCubeToExchange = new Node(5, new ScorerAction(scorerAction::OPEN));
	m_moveToCubeStack = new Node(5, new DriveDistanceAction());
	m_intakeCube = new Node(5, new IntakeAction());
	m_moveToExchange = new Node(5, new DriveDistanceAction());
	m_outtakeCubeSecondTime = new Node(5, new ScorerAction(scorerAction::OPEN));
	m_moveToCubeStackSecondTime = new Node(5, new DriveDistanceAction());
	m_intakeSecondCube = new Node(5, new IntakeAction());
	m_moveToExchangeSecondTime = new Node(5, new DriveDistanceAction());
	m_outtakeCubeThirdTime  = new Node(5, new ScorerAction(scorerAction::OPEN));

}

void CenterAuton::addNodes() {
	m_outtakeCubeToExchange->addNext(m_moveToCubeStack);
	m_moveToCubeStack->addNext(m_intakeCube);
	m_intakeCube->addNext(m_moveToExchange);
	m_moveToExchange->addNext(m_outtakeCubeSecondTime);
	m_outtakeCubeSecondTime->addNext(m_moveToCubeStackSecondTime);
	m_moveToCubeStackSecondTime->addNext(m_intakeSecondCube);
	m_intakeSecondCube->addNext(m_moveToExchangeSecondTime);
	m_moveToExchangeSecondTime->addNext(m_outtakeCubeThirdTime);

}
