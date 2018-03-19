#include "DriveWaypointAction.h"
#include "Robot.h"

DriveWaypointAction::DriveWaypointAction(Path path, Position2d startPos, bool reversed, double tolerance,
                                         double maxAccel, double maxAngAccel, bool gradualStop, double lookahead) {
    m_path = path;
    m_reversed = reversed;
    m_tolerance = tolerance;
    m_maxAccel = maxAccel;
    m_maxAngAccel = maxAngAccel;
    m_gradualStop = gradualStop;
    m_lookahead = lookahead;
    m_startPos = startPos;
    CORELog::logInfo("Start Pos theta" + to_string(m_startPos.getRotation().getDegrees()));
}

void DriveWaypointAction::actionInit() {
    CORELog::logInfo("Starting follower");
    CORE2018::GetInstance()->driveSubsystem.resetTracker(m_startPos);
    CORE2018::GetInstance()->driveSubsystem.startPath(m_path, m_startPos, m_reversed, m_maxAccel, m_maxAngAccel,
                                                      m_tolerance, m_gradualStop, m_lookahead);
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
