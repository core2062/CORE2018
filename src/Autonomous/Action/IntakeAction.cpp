#include <Autonomous/Action/IntakeAction.h>
#include "Robot.h"

IntakeAction::IntakeAction() {
	// TODO Auto-generated constructor stub

}
void IntakeAction::actionInit() {
	switch(m_intakeRequestedAction) {
	case INTAKE:
		CORE2018::GetInstance()->intakeSystem.setIntakeSpeed(0.2);
		break;
	case OUTTAKE:
		CORE2018::GetInstance()->intakeSystem.setIntakeSpeed(-0.2);
		break;
	case CLOSE:
		CORE2018::GetInstance()->intakeSystem.closeIntake();
		break;
	case OPENINTAKE:
		CORE2018::GetInstance()->intakeSystem.openIntake();
		break;
	case STOP:
		CORE2018::GetInstance()->intakeSystem.setIntakeSpeed(0);
		break;
	}
}
COREAutonAction::actionStatus IntakeAction::action() {
	//TODO: Write this code
	return COREAutonAction::actionStatus::END;
}
void IntakeAction::actionEnd() {

}
