#include <Autonomous/Action/IntakeCubeAction.h>

IntakeCubeAction::IntakeCubeAction() {
	// TODO Auto-generated constructor stub

}
void IntakeCubeAction::actionInit() {

}
COREAutonAction::actionStatus IntakeCubeAction::action() {
	intakeSubsystem.openIntake();
	intakeSubsystem.setIntake(0.2);
	intakeSubsystem.closeIntake();
	scorerSubsystem.intakeCube();
	return COREAutonAction::actionStatus::END;
}
void IntakeCubeAction::actionEnd() {

}
