#include <Autonomous/Action/RotateArmAction.h>
#include <CORERobotLib.h>
#include <Robot.h>
RotateArmAction::RotateArmAction() {

}
void RotateArmAction::actionInit() {

}
COREAutonAction::actionStatus RotateArmAction::action() {
	switch(m_requestedArmAction) {
	case UP:
		CORE2018::GetInstance()->chainBarSubsystem.SetRotationRequestedAngle(180);
		break;
	case MIDDLE:
		CORE2018::GetInstance()->chainBarSubsystem.SetRotationRequestedAngle(90);
		break;
	case DOWN:
		CORE2018::GetInstance()->chainBarSubsystem.SetRotationRequestedAngle(0);
		break;
	}
	return COREAutonAction::actionStatus::END;
}
void RotateArmAction::actionEnd() {

}
