#include <Autonomous/Action/RotateArmAction.h>
#include <CORERobotLib.h>
#include <Robot.h>
RotateArmAction::RotateArmAction() {

}
void RotateArmAction::actionInit() {
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

}
COREAutonAction::actionStatus RotateArmAction::action() {
	//TODO: Write this code
	return COREAutonAction::actionStatus::END;
}
void RotateArmAction::actionEnd() {

}
