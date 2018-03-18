#include "DriveDistanceAction.h"
#include "Robot.h"

DriveDistanceAction::DriveDistanceAction() {

}

void DriveDistanceAction::actionInit() {

}
COREAutonAction::actionStatus DriveDistanceAction::action() {
	//TODO: Write this code
	//CORE2018::GetInstance()->driveSubsystem.
	return COREAutonAction::actionStatus::END;
}
void DriveDistanceAction::actionEnd() {
}
