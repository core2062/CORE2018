#include <Robot.h>
#include "ctre/Phoenix.h"
#include "CORELogging/COREDataLog.h"
#include <CORERobotLib.h>

CORE2018* CORE2018::m_instance;

CORE2018::CORE2018():
        m_chainBarIntakeAngle("Chain Bar Intake Position Angle"),
        m_chainBarSwitchAngle("Chain Bar Switch Position Angle") {
    m_instance = this;
}

void CORE2018::robotInit() {
    operatorJoystick->registerButton(COREJoystick::JoystickButton::A_BUTTON);
    operatorJoystick->registerButton(COREJoystick::JoystickButton::B_BUTTON);
}

void CORE2018::teleopInit() {

}

void CORE2018::teleop() {
    if(operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::A_BUTTON)) { //Intake Position
        chainBarSubsystem.SetChainBarRequestedAngle(m_chainBarIntakeAngle.Get());
        chainBarSubsystem.SetRotationRequestedAngle(-180);
    } else if(operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::B_BUTTON)) { //Switch Position
        chainBarSubsystem.SetChainBarRequestedAngle(m_chainBarSwitchAngle.Get());
        chainBarSubsystem.SetRotationRequestedAngle(-90);
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
