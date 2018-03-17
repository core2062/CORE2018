#pragma once

#include "CORERobotLib.h"
#include "WaypointFollower/WaypointFollower.h"


using namespace CORE;

class DriveWaypointAction : public COREAutonAction {
public:
    DriveWaypointAction(Path path, Translation2d startPos, bool reversed = false, double tolerance = .25,
                        double maxAccel = 25.0, bool gradualStop = true, double lookahead = 24.0);
    void actionInit() override;
    actionStatus action() override;
    void actionEnd() override;
private:
    Path m_path;
    bool m_reversed = false;
    double m_tolerance = .25;
    double m_maxAccel = 25.0;
    bool m_gradualStop = true;
    double m_lookahead;
    Translation2d m_startPos;
};
