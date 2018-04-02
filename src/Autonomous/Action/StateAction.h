#pragma once

#include "CORERobotLib.h"

#include "SuperStructure.h"

using namespace CORE;

class StateAction : public COREAutonAction {
public:
    StateAction(WantedState wantedState);
    void actionInit() override;
    actionStatus action() override;
    void actionEnd() override;

private:
    WantedState m_requestedState;
};