#include <Autonomous/Action/DropCubeAction.h>

DropCubeAction::DropCubeAction() {

}
void DropCubeAction::actionInit() {

}
COREAutonAction::actionStatus DropCubeAction::action() {
	if (Robot.scorerSubsystem.m_isCubeInIntake == true) {
//		Robot.scorerSubsystem.outakeCube();
	}

	return COREAutonAction::actionStatus::END;
}
void DropCubeAction::actionEnd() {

}
