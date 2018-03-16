#pragma once

#include "CORERobotLib.h"

using namespace CORE;

class TestPathAuton : public COREAuton {
public:
    TestPathAuton();
	void addNodes() override;

private:
	Node * m_testNode;
};
