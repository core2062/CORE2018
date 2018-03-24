
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
    Node * m_intakeCube = nullptr;
};

}
