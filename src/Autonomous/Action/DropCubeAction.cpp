#include <Autonomous/Action/DropCubeAction.h>

DropCube::DropCube() {

}
void DropCube::actionInit() {

}
COREAutonAction::actionStatus DropCube::action() {
	if (Robot.scorerSubsystem.m_isCubeInIntake == true) {
		Robot.scorerSubsystem.outakeCube();
	}

	return COREAutonAction::actionStatus::END;
}
void DropCube::actionEnd() {

}
