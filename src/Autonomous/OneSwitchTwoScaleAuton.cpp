#include <CORERobotLib.h>
#include <Autonomous/OneSwitchTwoScaleAuton.h>

OneSwitchTwoScaleAuton::OneSwitchTwoScaleAuton() :
	COREAuton("One Switch Two Scale Auton", 0.0) {

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
