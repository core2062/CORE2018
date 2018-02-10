#include <IntakeSubsystem.h>
IntakeSubsystem::IntakeSubsystem() : m_leftIntakeMotor(0), m_rightIntakeMotor(0) {
	m_isIntaking = false;
}
void IntakeSubsystem::robotInit(){
	//m_button.GetRawButton(1);
	//Sm_rightIntakeMotor.Set(ControlMode::PercentOutput, 0);
	m_leftIntakeMotor.Set(ControlMode::PercentOutput, 0);
}
void IntakeSubsystem::autonInit() {

}
void IntakeSubsystem::auton() {

}
void IntakeSubsystem::teleopInit(){
	m_isIntaking = false;
}
void IntakeSubsystem::teleop(){

}
bool IntakeSubsystem :: isIntaking(){
	return m_isIntaking;
}
void IntakeSubsystem::startIntake(){
	if (/*m_button.GetRawButtonPressed(1) == true &&*/ m_isIntaking == false){
		m_leftIntakeMotor.Set(ControlMode::PercentOutput, 0.2);
		m_rightIntakeMotor.Set(ControlMode::PercentOutput, 0.2);
		m_isIntaking = true;
	}
}
void IntakeSubsystem::stopIntake(){
	if (/*m_button.GetRawButtonPressed(1) == false &&*/ m_isIntaking == true){
		m_leftIntakeMotor.Set(ControlMode::PercentOutput, 0);
		m_rightIntakeMotor.Set(ControlMode::PercentOutput, 0);
		m_isIntaking = false;
	}
}

