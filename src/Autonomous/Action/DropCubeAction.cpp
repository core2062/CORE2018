#include <Autonomous/Action/DropCubeAction.h>

DropCubeAction::DropCubeAction() {

}
void DropCubeAction::actionInit() {

}
COREAutonAction::actionStatus DropCubeAction::action() {
	if (Robot.scorerSubsystem.m_scorerClosed == true) {
		Robot.scorerSubsystem.openScorer();
	}

	return COREAutonAction::actionStatus::END;
}
void DropCubeAction::actionEnd() {

}
