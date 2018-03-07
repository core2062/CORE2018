
#pragma once

#include <memory>

#include <CORERobotLib.h>

#include "Actions.h"

using namespace CORE;

class OneSwitchOneScaleAuton : public COREAuton {
	OneSwitchOneScaleAuton();
	void addNodes() override;

private:
	Node * m_moveToSwitch = nullptr;
	Node * m_outtakeCubeToSwitch = nullptr;
	Node * m_moveToCubeStack = nullptr;
	Node * m_intakeCube = nullptr;
	Node * m_moveToScale= nullptr;
	Node * m_liftUpToScale = nullptr;
	Node * m_outtakeCubeToScale = nullptr;
};
