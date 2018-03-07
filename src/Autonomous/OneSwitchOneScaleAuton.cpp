
#include "OneSwitchOneScaleAuton.h"

OneSwitchOneScaleAuton::OneSwitchOneScaleAuton() :
	COREAuton("One switch one scale auton") {
}

void OneSwitchOneScaleAuton::addNodes() {
	m_moveToSwitch->addNext(m_outtakeCubeToSwitch);
	m_outtakeCubeToSwitch->addNext(m_moveToCubeStack);
	m_moveToCubeStack->addNext(m_intakeCube);
	m_intakeCube->addNext(m_moveToScale);
	m_moveToScale->addNext(m_liftUpToScale);
	m_liftUpToScale->addNext(m_outtakeCubeToScale);
}

