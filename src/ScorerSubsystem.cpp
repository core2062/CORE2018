#include <ScorerSubsystem.h>

#include "Robot.cpp"

ScorerSubsystem::ScorerSubsystem() : m_frontLeftSolenoid(0, 1), m_frontRightSolenoid(0, 1), m_backRightSolenoid(0, 1), m_backLeftSolenoid(0, 1) {
	m_liftArmPosition = 0;
}

void ScorerSubsystem::robotInit() {

	robot->m_operatorJoystick.registerButton(CORE::COREJoystick::JoystickButton::DPAD_N);
	robot->m_operatorJoystick.registerButton(CORE::COREJoystick::JoystickButton::DPAD_S);
	robot->m_operatorJoystick.registerButton(CORE::COREJoystick::JoystickButton::DPAD_W);
	robot->m_operatorJoystick.registerButton(CORE::COREJoystick::JoystickButton::DPAD_E);
	robot->m_operatorJoystick.registerAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_Y);
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
	if (m_isCubeTurningClockwise == true && robot->m_operatorJoystick.getButton(CORE::COREJoystick::JoystickButton::DPAD_N) == true) {
		 m_cubeRotatorMotor.Set(ControlMode::PercentOutput,0.2);



	}

	else if (m_isCubeTurningClockwise == false && robot->m_operatorJoystick.getButton(CORE::COREJoystick::JoystickButton::DPAD_S) == true) {
		m_cubeRotatorMotor.Set(ControlMode::PercentOutput,-0.2);


	}
	else if((m_isCubeTurningClockwise == false && robot->m_operatorJoystick.getButton(CORE::COREJoystick::JoystickButton::DPAD_S) == false) ||
			(m_isCubeTurningClockwise == true && robot->m_operatorJoystick.getButton(CORE::COREJoystick::JoystickButton::DPAD_N) == true)) {


	}
}

void ScorerSubsystem::liftArm() {
	if (m_isArmGoingUp == false && robot->m_operatorJoystick.getAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_Y) >= 0.1) {

		m_leftArmMotor.Set(ControlMode::PercentOutput,robot->m_operatorJoystick.getAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_Y));
		m_rightArmMotor.Set(ControlMode::PercentOutput,robot->m_operatorJoystick.getAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_Y));
		m_isArmGoingUp = true;
	}
}

void ScorerSubsystem::intakeCube() {
	if (m_intakeIsClosed == false && robot->m_operatorJoystick.getButton(CORE::COREJoystick::JoystickButton::DPAD_W) == true){
		m_frontLeftSolenoid.Set(DoubleSolenoid::kForward);
		m_frontRightSolenoid.Set(DoubleSolenoid::kForward);
		m_backLeftSolenoid.Set(DoubleSolenoid::kForward);
		m_backRightSolenoid.Set(DoubleSolenoid::kForward);
		m_intakeIsClosed = true;
	}
}

void ScorerSubsystem::outakeCube() {
	if (m_intakeIsClosed == true && robot->m_operatorJoystick.getButton(CORE::COREJoystick::JoystickButton::DPAD_E) == true) {
		m_frontLeftSolenoid.Set(DoubleSolenoid::kReverse);
		m_frontRightSolenoid.Set(DoubleSolenoid::kReverse);
		m_backLeftSolenoid.Set(DoubleSolenoid::kReverse);
		m_backRightSolenoid.Set(DoubleSolenoid::kReverse);
		m_intakeIsClosed = false;
	}
}


