#include <Robot.h>

CORE2018* CORE2018::m_instance;

CORE2018::CORE2018():
        m_chainBarIntakeAngle("Chain Bar Intake Position Angle"),
        m_chainBarSwitchAngle("Chain Bar Switch Position Angle"),
        m_chainBarUpAngle("Chain Bar Up Position Angle"),
        m_chainBarFeederAngle("Chain Bar Feeder Angle"),
        m_liftLowScalePosition("Lift Low Scale Position"),
        m_liftMidScalePosition("Lift Mid Scale Position"),
m_liftHighScalePosition("Lift High Scale Position") {
    m_instance = this;
    SetPeriod(1/60.0);
}

void CORE2018::robotInit() {
    operatorJoystick->registerButton(COREJoystick::JoystickButton::A_BUTTON);
    operatorJoystick->registerButton(COREJoystick::JoystickButton::B_BUTTON);
}

void CORE2018::teleopInit() {

}

void CORE2018::teleop() {
    if(!operatorJoystick->getButton(COREJoystick::JoystickButton::RIGHT_BUTTON)) {
        //*************** Modifier Button Not Pressed ***************
        if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::A_BUTTON)) { //Intake Position
            chainBarSubsystem.SetChainBarRequestedAngle(m_chainBarIntakeAngle.Get());
            chainBarSubsystem.SetRotationRequestedAngle(-180);
            liftSubsystem.SetRequestedPosition(5);
        } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::B_BUTTON)) { //Switch Position
            chainBarSubsystem.SetChainBarRequestedAngle(m_chainBarSwitchAngle.Get());
            chainBarSubsystem.SetRotationRequestedAngle(-90);
        } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::Y_BUTTON)) { //Up Position
            chainBarSubsystem.SetChainBarRequestedAngle(m_chainBarUpAngle.Get());
        } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::X_BUTTON)) { //Feeder Station Position
            chainBarSubsystem.SetChainBarRequestedAngle(m_chainBarFeederAngle.Get());
            chainBarSubsystem.SetRotationRequestedAngle(-90);
        }
    } else {
        //*************** Modifier Button Pressed ***************
        if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::A_BUTTON)) { //Low Scale Position
            liftSubsystem.SetRequestedPosition(45);
        } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::B_BUTTON)) { //Mid Scale Forward Position
            liftSubsystem.SetRequestedPosition(55);
            chainBarSubsystem.SetChainBarRequestedAngle(-90);
            chainBarSubsystem.SetRotationRequestedAngle(-90);
        } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::Y_BUTTON)) { //High Scale Position
            liftSubsystem.SetRequestedPosition(64);
        } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::X_BUTTON)) { //Mid Scale Backward Position
            liftSubsystem.SetRequestedPosition(55);
            chainBarSubsystem.SetChainBarRequestedAngle(90);
            chainBarSubsystem.SetRotationRequestedAngle(90);
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
