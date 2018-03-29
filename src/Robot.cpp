#include <Robot.h>

CORE2018* CORE2018::m_instance;

CORE2018::CORE2018() {
    m_instance = this;
    SetPeriod(1/60.0);
}

void CORE2018::robotInit() {
    operatorJoystick->registerButton(COREJoystick::JoystickButton::A_BUTTON);
    operatorJoystick->registerButton(COREJoystick::JoystickButton::B_BUTTON);
    operatorJoystick->registerButton(COREJoystick::JoystickButton::X_BUTTON);
    operatorJoystick->registerButton(COREJoystick::JoystickButton::Y_BUTTON);
    operatorJoystick->registerButton(COREJoystick::JoystickButton::RIGHT_BUTTON);
}

void CORE2018::teleopInit() {

}

void CORE2018::teleop() {
    if(!operatorJoystick->getButton(COREJoystick::JoystickButton::RIGHT_BUTTON)) {
        //*************** Modifier Button Not Pressed ***************
        if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::A_BUTTON)) { //Intake Position
            superStructure.setWantedState(WantedState::WANT_TO_PICKUP_CUBE);
        } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::B_BUTTON)) { //Switch Position
            superStructure.setWantedState(WantedState::WANT_TO_SCORE_ON_SWITCH);
        } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::Y_BUTTON)) { //Up Position
            superStructure.setWantedState(WantedState::WANT_TO_BE_STRAIGHT_UP);
        } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::X_BUTTON)) { //Feeder Station Position
            superStructure.setWantedState(WantedState::WANT_TO_GET_FROM_FEEDER);
        }
    } else {
        //*************** Modifier Button Pressed ***************
        if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::A_BUTTON)) { //Mid Scale Position - Forward
            superStructure.setWantedState(WantedState::WANT_TO_SCORE_ON_SCALE);
            superStructure.setWantedScaleScoreHeight(WantedScaleScoreHeight::MID_SCALE);
        } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::B_BUTTON)) { //High Scale Position - Forward
            superStructure.setWantedState(WantedState::WANT_TO_SCORE_ON_SCALE);
            superStructure.setWantedScaleScoreHeight(WantedScaleScoreHeight::HIGH_SCALE);
        } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::Y_BUTTON)) { //High Scale Position - Behind
            superStructure.setWantedState(WantedState::WANT_TO_SCORE_ON_SCALE_BEHIND);
            superStructure.setWantedScaleScoreHeight(WantedScaleScoreHeight::HIGH_SCALE);
        } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::X_BUTTON)) { //Mid Scale Position - Behind
            superStructure.setWantedState(WantedState::WANT_TO_SCORE_ON_SCALE_BEHIND);
            superStructure.setWantedScaleScoreHeight(WantedScaleScoreHeight::MID_SCALE);
        }
    }
}

void CORE2018::testInit() {
	CORELog::logInfo("test init");
}

void CORE2018::test() {
	CORELog::logInfo("test");
}
CORE2018* CORE2018::GetInstance() {
	if(!m_instance) {
		CORELog::logError("Get instance returning null pointer!");
	}
	return m_instance;
}


START_ROBOT_CLASS(CORE2018)
