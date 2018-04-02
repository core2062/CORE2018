#include <Autonomous/Action/IntakeAction.h>
#include "Robot.h"
#include "COREUtilities/COREConstant.h"

IntakeAction::IntakeAction(intakeAction intakeRequestedAction) {
	m_intakeRequestedAction = intakeRequestedAction;
}

void IntakeAction::actionInit() {

}

COREAutonAction::actionStatus IntakeAction::action() {
	switch(m_intakeRequestedAction) {
	    case STOP:
		    CORE2018::GetInstance()->intakeSystem.setIntakeSpeed(0);
		    break;
        case WIDE_RANGE_INTAKE:
            CORE2018::GetInstance()->intakeSystem.wideRangeIntake();
            break;
        case SMALL_RANGE_INTAKE:
            CORE2018::GetInstance()->intakeSystem.smallRangeIntake();
            break;
        case OUTTAKE_CUBE:
            CORE2018::GetInstance()->intakeSystem.outtakeCube();
            break;
    }
	return COREAutonAction::actionStatus::END;
}
void IntakeAction::actionEnd() {

}
