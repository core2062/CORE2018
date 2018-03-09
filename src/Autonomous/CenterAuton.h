
#pragma once

#include <CORERobotLib.h>

namespace CORE {

class CenterAuton : COREAuton {
public:
	CenterAuton();
	void addNodes() override;

private:
	Node * m_moveToSwitch = nullptr;
	Node * m_outtakeCubeToSwitch = nullptr;
	Node * m_moveToCubeStack = nullptr;
	Node * m_intakeCube = nullptr;
	Node * m_moveToScale= nullptr;
	Node * m_liftUpToScale = nullptr;
	Node * m_outtakeCubeToScale = nullptr;
	Node * m_driveToCubes = nullptr;
	Node * m_intakeSecondCube = nullptr;
	Node * m_driveToScaleSecondTime = nullptr;
	Node * m_outtakeSecondCube = nullptr;
};

}
