
#pragma once

#include <CORERobotLib.h>

namespace CORE {

class CenterAuton : COREAuton {
public:
	CenterAuton();
	void addNodes() override;

private:
	Node * m_outtakeCubeToExchange = nullptr;
	Node * m_moveToCubeStack = nullptr;
	Node * m_intakeCube = nullptr;
	Node * m_moveToExchange = nullptr;
	Node * m_outtakeCubeSecondTime = nullptr;
	Node * m_moveToCubeStackSecondTime = nullptr;
	Node * m_intakeSecondCube = nullptr;
	Node * m_moveToExchangeSecondTime = nullptr;
	Node * m_outtakeCubeThirdTime = nullptr;
};

}
