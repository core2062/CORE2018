#include <Autonomous/Action/DropCube.h>

DropCube::DropCube() {

}
void DropCube::actionInit() {

}
COREAutonAction::actionStatus DropCube::action() {
	scorerSubsystem.outakeCube();
	return COREAutonAction::actionStatus::END;
}
void DropCube::actionEnd() {

}
