#pragma once

#include "CORERobotLib.h"

using namespace CORE;

class TestAuton : public COREAuton {
public:
    TestAuton();
	void addNodes() override;

private:
	Node * m_testNode;
};
