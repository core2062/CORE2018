#include "DriveWaypointAction.h"

#include <utility>
#include "Robot.h"

DriveWaypointAction::DriveWaypointAction(Path path) {
    m_path = std::move(path);
    m_reversed = false;
    m_tolerance = 0.25;
    m_maxAccel = 24;
    m_maxAngAccel = 0.25;
    m_gradualStop = true;
    m_lookahead = 24.0;
    m_resetPosition = false;
}

void DriveWaypointAction::actionInit() {
    if(m_resetPosition) {
        CORELog::logInfo("Start position theta" + to_string(m_startPos.getRotation().getDegrees()));
        CORE2018::GetInstance()->driveSubsystem.resetTracker(m_startPos);
    }
    CORE2018::GetInstance()->driveSubsystem.startPath(m_path, m_startPos, m_reversed, m_maxAccel, m_maxAngAccel,
                                                      m_tolerance, m_gradualStop, m_lookahead);
}

DriveWaypointAction::actionStatus DriveWaypointAction::action() {
    if(!CORE2018::GetInstance()->driveSubsystem.pathDone()){
        return actionStatus::CONTINUE;
    }
    return actionStatus::END;
}

void DriveWaypointAction::actionEnd() {
    CORE2018::GetInstance()->driveSubsystem.zeroMotors();
}
