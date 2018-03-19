#pragma once

#include "CORERobotLib.h"
#include "WaypointFollower/WaypointFollower.h"

using namespace CORE;

class DriveWaypointAction : public COREAutonAction {
public:
    DriveWaypointAction(Path path, Position2d startPos, bool reverssed = false, double tolerance = .25,
                        double maxAccel = 100, double maxAngAccel = 0.25, bool gradualStop = true, double lookahead = 16.0);
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
    Position2d m_startPos;
};
