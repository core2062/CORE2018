#include <Autonomous/Action/LiftUpToSwitchAction.h>

LiftUpToSwitch::LiftUpToSwitch() {
	m_switchHeight = 3.0;
}
void LiftUpToSwitch::actionInit(){
}
COREAutonAction::actionStatus LiftUpToSwitch::action(){
	if (m_switchHeight >= Robot.liftSubsystem.m_liftPosition) {
		Robot.liftSubsystem.setLift(0.2);
		return COREAutonAction::actionStatus::CONTINUE;
	} else {
		Robot.liftSubsystem.setLift(0);
		return COREAutonAction::actionStatus::END;
	}
}
void LiftUpToSwitch::actionEnd(){

}

