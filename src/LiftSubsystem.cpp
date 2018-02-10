#include <LiftSubsystem.h>

LiftSubsystem::LiftSubsystem() : m_leftLiftMotor(0), m_rightLiftMotor(0) {
	m_liftPosition = 0;
	m_liftBottomLimit = 0;
	m_liftTopLimit = 0;
	m_isLifting = false;
}
void LiftSubsystem::robotInit() {
	//m_leftLiftMotor.Set(ControlMode::PercentOutput, 0);
	//m_rightLiftMotor.Set(ControlMode::PercentOutput, 0);
	//m_liftJoystick.GetAxis(frc::Joystick::AxisType::kYAxis);
	//m_button2.GetAxisChannel(frc::Joystick::AxisType::kYAxis);
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
	return m_liftPosition;
}
void LiftSubsystem::startLift() {

	if (m_isLifting == false) {
		//m_leftLiftMotor.Set(ControlMode::PercentOutput, 0);
		//m_rightLiftMotor.Set(ControlMode::PercentOutput, 0);
		m_isLifting = true;
	}
}
/*
void LiftSubsystem::stopLift() {
	if (m_liftJoystick.GetRawAxis(0) == false && m_isLifting == true){
	    m_rightLiftMotor.Set(ControlMode::PercentOutput, 0);
		m_isLifting = false;
	}
}
*/
