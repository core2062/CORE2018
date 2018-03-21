#pragma once

#include "CORERobotLib.h"
#include "WaypointFollower/WaypointFollower.h"

using namespace CORE;

class DriveWaypointAction : public COREAutonAction {
public:
    //DriveWaypointAction(Path path, Position2d startPos);
    explicit DriveWaypointAction(Path path);
    void actionInit() override;
    actionStatus action() override;
    void actionEnd() override;
private:
    Path m_path;
    bool m_reversed;
    double m_tolerance;
    double m_maxAccel;
    double m_maxAngAccel;
    bool m_gradualStop;
    double m_lookahead;
    bool m_resetPosition;
    Position2d m_startPos;
};
