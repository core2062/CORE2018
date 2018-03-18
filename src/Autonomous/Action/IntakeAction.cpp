#include <Autonomous/Action/IntakeAction.h>
#include "Robot.h"
#include "COREUtilities/COREConstant.h"

IntakeAction::IntakeAction() :
	m_outtakeSpeed("Cube Outtake Speed"),
	m_intakeSpeed("Cube Intake Speed") {
	// TODO Auto-generated constructor stub

}
void IntakeAction::actionInit() {

}
COREAutonAction::actionStatus IntakeAction::action() {
	switch(m_intakeRequestedAction) {
	case INTAKE:
		CORE2018::GetInstance()->intakeSystem.setIntakeSpeed(m_intakeSpeed.Get());
		break;
	case OUTTAKE:
		CORE2018::GetInstance()->intakeSystem.setIntakeSpeed(m_outtakeSpeed.Get());
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
	return COREAutonAction::actionStatus::END;
}
void IntakeAction::actionEnd() {

}
