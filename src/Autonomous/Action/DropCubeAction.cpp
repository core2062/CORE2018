#include <Autonomous/Action/DropCubeAction.h>

DropCube::DropCube() {

}
void DropCube::actionInit() {

}
COREAutonAction::actionStatus DropCube::action() {
	if (Robot.scorerSubsystem.m_scorerClosed == true) {
		Robot.scorerSubsystem.openScorer();
	}

	return COREAutonAction::actionStatus::END;
}
void DropCube::actionEnd() {

}
