/*#include <ScorerSubsystem.h>

#include "Robot.cpp"

ScorerSubsystem::ScorerSubsystem() : m_frontLeftSolenoid(0, 1), m_frontRightSolenoid(0, 1), m_backRightSolenoid(0, 1), m_backLeftSolenoid(0, 1) {

}

void ScorerSubsystem::robotInit() {

}

void ScorerSubsystem::autonInit() {

}

void ScorerSubsystem::auton() {

}

void ScorerSubsystem::teleopInit() {

}

void ScorerSubsystem::teleop() {

}

void ScorerSubsystem::rotateCube() {
	if (m_isCubeTurningClockwise == true && m_operatorJoystick) {
		 m_cubeRotatorMotor.Set(ControlMode::PercentOutput,0.2);



	}

	else if (m_isCubeTurningClockwise == false) {
		m_cubeRotatorMotor.Set(ControlMode::PercentOutput,-0.2);


	}
	else if(){


	}
}

void ScorerSubsystem::liftArm() {
	if (m_isArmGoingUp == false) {
		m_leftArmMotor.Set(ControlMode::PercentOutput,0.2);
		m_rightArmMotor.Set(ControlMode::PercentOutput,0.2);
		m_isArmGoingUp = true;
	}

	else if (m_isArmGoingUp == true) {

		m_leftArmMotor.Set(ControlMode::PercentOutput,-0.2);
		m_rightArmMotor.Set(ControlMode::PercentOutput,-0.2);
		m_isArmGoingUp = false;

	}
}

void ScorerSubsystem::intakeCube() {
	if (m_intakeIsClosed == false){
		m_frontLeftSolenoid.Set(DoubleSolenoid::kForward);
		m_frontRightSolenoid.Set(DoubleSolenoid::kForward);
		m_backLeftSolenoid.Set(DoubleSolenoid::kForward);
		m_backRightSolenoid.Set(DoubleSolenoid::kForward);
		m_intakeIsClosed = true;
	}
}

void ScorerSubsystem::outakeCube() {
	if (m_intakeIsClosed == true) {
		m_frontLeftSolenoid.Set(DoubleSolenoid::kReverse);
		m_frontRightSolenoid.Set(DoubleSolenoid::kReverse);
		m_backLeftSolenoid.Set(DoubleSolenoid::kReverse);
		m_backRightSolenoid.Set(DoubleSolenoid::kReverse);
		m_intakeIsClosed = false;
	}
}
*/

