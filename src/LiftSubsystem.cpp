#include <LiftSubsystem.h>


LiftSubsystem::LiftSubsystem() :
	m_leftLiftMotor(0),
	m_rightLiftMotor(0) {
		m_liftPosition = 0;
		m_liftBottomLimit = 0;
		m_liftTopLimit = 0;
		m_isLifting = false;
		m_isLiftAtTop = false;
		m_isLiftDown = true;
}
void LiftSubsystem::robotInit() {
	m_leftLiftMotor->Set(ControlMode::PercentOutput, 0);
	m_rightLiftMotor->Set(ControlMode::PercentOutput, 0);
	//m_liftJoystick.GetAxis(frc::Joystick::AxisType::kYAxis);
	//m_button2.GetAxisChannel(frc::Joystick::AxisType::kYAxis);
	Robot->m_operatorJoystick.registerAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);

}
void LiftSubsystem::autonInit() {

}
void LiftSubsystem::auton() {


}
void LiftSubsystem::teleopInit() {
	m_isLifting = false;

}
void LiftSubsystem::teleop() {

}
bool LiftSubsystem::isLifting() {
	return m_isLifting;
}
bool LiftSubsystem::isLiftDown() {
	return m_isLiftDown;
}
void LiftSubsystem::startLift() {

	if (m_isLifting == false && Robot->m_operatorJoystick.getAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y) >= 0.2) {
		m_leftLiftMotor->Set(ControlMode::PercentOutput, Robot->m_operatorJoystick.getAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y));
		m_rightLiftMotor->Set(ControlMode::PercentOutput, Robot->m_operatorJoystick.getAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y));
		m_isLifting = true;
		if (m_liftPosition == m_liftTopLimit || m_liftPosition == m_liftBottomLimit) {
			m_leftLiftMotor->Set(ControlMode::PercentOutput, 0);
			m_rightLiftMotor->Set(ControlMode::PercentOutput, 0);
		}
	}

}

