#include <LiftSubsystem.h>
#include <CORERobotLib.h>
#include "COREUtilities/COREConstant.h"
#include "WPILib.h"

LiftSubsystem::LiftSubsystem(COREJoystick * operatorJoystick) :
		m_leftLiftMotor(/*RIGHT_LIFT_MOTOR_PORT*/0),
		m_rightLiftMotor(/*LEFT_LIFT_MOTOR_PORT*/1),
		m_liftTopLimit("Lift Top Limit", 0),
		m_liftBottomLimit("Lift Bottom Limit", 0) {
	m_operatorJoystick = operatorJoystick;
	m_liftPosition = 0;
}

void LiftSubsystem::robotInit() {
	m_leftLiftMotor.Set(ControlMode::PercentOutput, 0);
	m_rightLiftMotor.Set(ControlMode::PercentOutput, 0);
	m_operatorJoystick->registerAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
}

void LiftSubsystem::teleopInit() {
}

void LiftSubsystem::teleop() {
	double y = m_operatorJoystick->getAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
	if (y >= 0.1 || y <= -0.1) {
		setLift(y);
	}
}

void LiftSubsystem::setLift(double liftMotorPercentage) {
	m_leftLiftMotor.Set(ControlMode::PercentOutput, liftMotorPercentage);
	m_rightLiftMotor.Set(ControlMode::PercentOutput, -liftMotorPercentage);
}
