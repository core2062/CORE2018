#include "IntakeSubsystem.h"
#include "Robot.h"

// TODO fill this in with actual motor ports and solenoid stuff
IntakeSubsystem::IntakeSubsystem() :
		m_leftIntakeMotor(LEFT_INTAKE_MOTOR_PORT),
		m_rightIntakeMotor(RIGHT_INTAKE_MOTOR_PORT),
		m_intakeSolenoid(INTAKE_IN_SOLENOID_PORT, INTAKE_OUT_SOLENOID_PORT) {
	m_leftIntakeMotor.SetInverted(true);
}

void IntakeSubsystem::robotInit() {
	m_leftIntakeMotor.Set(ControlMode::PercentOutput, 0);
    m_rightIntakeMotor.Set(ControlMode::PercentOutput, 0);
    driverJoystick->registerButton(CORE::COREJoystick::JoystickButton::LEFT_BUTTON);
	driverJoystick->registerButton(CORE::COREJoystick::JoystickButton::LEFT_TRIGGER);
	driverJoystick->registerButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON);
}

void IntakeSubsystem::teleopInit() {

}

void IntakeSubsystem::teleop() {
	if (driverJoystick->getButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)) { //Wide Range Intake
		wideRangeIntake();
	} else if (driverJoystick->getButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON)) { //Small Range Intake
		smallRangeIntake();
	} else if (driverJoystick->getButton(CORE::COREJoystick::JoystickButton::LEFT_BUTTON)) { //Small Range Outtake
		outtakeCube();
	} else {
		setIntakeSpeed(0);
	}
}

void IntakeSubsystem::openIntake() {
	m_intakeSolenoid.Set(DoubleSolenoid::kReverse);
}

void IntakeSubsystem::closeIntake() {
	m_intakeSolenoid.Set(DoubleSolenoid::kForward);
}

void IntakeSubsystem::setIntakeSpeed(double intakeMotorPercent) {
	m_leftIntakeMotor.Set(ControlMode::PercentOutput, intakeMotorPercent);
	m_rightIntakeMotor.Set(ControlMode::PercentOutput, intakeMotorPercent);
}

void IntakeSubsystem::wideRangeIntake() {
	openIntake();
	setIntakeSpeed(-0.8);
}

void IntakeSubsystem::smallRangeIntake() {
	closeIntake();
	setIntakeSpeed(-0.8);
}

void IntakeSubsystem::outtakeCube() {
	closeIntake();
	setIntakeSpeed(1);
}
