#include <Autonomous/Action/RotateArmAction.h>

RotateArmAction::RotateArmAction() {

}
void RotateArmAction::actionInit() {

}
COREAutonAction::actionStatus RotateArmAction::action() {
	scorerSubsystem.rotateSetCube(0.2);
	scorerSubsystem.rotateSetCube(0);
	return COREAutonAction::actionStatus::END;
}
void RotateArmAction::actionEnd() {

}
