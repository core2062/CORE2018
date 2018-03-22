
#pragma once

#include <memory>
#include <CORERobotLib.h>
#include "Actions.h"

using namespace CORE;

class DriveForwardAuton : public COREAuton {
public:
	DriveForwardAuton();
	void addNodes() override;

private:
	Node * m_moveForward = nullptr;
};
