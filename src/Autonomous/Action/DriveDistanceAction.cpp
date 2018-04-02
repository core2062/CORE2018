#include "DriveDistanceAction.h"
#include "Robot.h"
DriveDistanceAction::DriveDistanceAction() {

}

void DriveDistanceAction::actionInit() {
	timer.Reset();
	timer.Start();
}

COREAutonAction::actionStatus DriveDistanceAction::action() {
	if (timer.Get() <= 3) {
		CORE2018::GetInstance()->driveSubsystem.m_swerveDrive->inverseKinematics(0, 0.5, 0);
		return COREAutonAction::actionStatus::CONTINUE;
	} else {
		return COREAutonAction::actionStatus::END;
	}
}

void DriveDistanceAction::actionEnd() {
	CORE2018::GetInstance()->driveSubsystem.m_swerveDrive->inverseKinematics(0, 0, 0);
}
