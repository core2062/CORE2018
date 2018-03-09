#include <Autonomous/Action/LowerLiftAction.h>

LowerLiftAction::LowerLiftAction() {

}
void LowerLiftAction::actionInit() {

}
COREAutonAction::actionStatus LowerLiftAction::action() {
	if (Robot.liftSubsystem.m_liftPosition == 0) {
		Robot.liftSubsystem.setLift(-0.2);
		return COREAutonAction::actionStatus::CONTINUE;
	} else {
		Robot.liftSubsystem.setLift(0);
		return COREAutonAction::actionStatus::END;
	}
}
void LowerLiftAction::actionEnd() {

}
