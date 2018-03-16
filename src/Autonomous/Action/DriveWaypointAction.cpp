#include "DriveWaypointAction.h"
#include "Robot.h"

DriveWaypointAction::DriveWaypointAction(Path path, bool reversed, double tolerance, double maxAccel, bool gradualStop,
                                         double lookahead) {
    m_path = path;
    m_reversed = reversed;
    m_tolerance = tolerance;
    m_maxAccel = maxAccel;
    m_gradualStop = gradualStop;
    m_lookahead = lookahead;
}

void DriveWaypointAction::actionInit() {
    CORELog::logInfo("Starting follower");
    CORE2018::GetInstance()->driveSubsystem.startPath(m_path, m_reversed, m_maxAccel, m_tolerance, m_gradualStop, m_lookahead);
    CORELog::logInfo("Ending start follower");
}

DriveWaypointAction::actionStatus DriveWaypointAction::action() {
    if(!CORE2018::GetInstance()->driveSubsystem.pathDone()){
        return actionStatus::CONTINUE;
    }
    std::cout << "Waypoint Action Done" << std::endl;
    return actionStatus::END;
}

void DriveWaypointAction::actionEnd() {
    CORE2018::GetInstance()->driveSubsystem.zeroMotors();
}
