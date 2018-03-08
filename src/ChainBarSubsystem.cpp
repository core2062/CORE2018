#include <ChainBarSubsystem.h>
#include "ctre/Phoenix.h"
#include "COREFramework/COREScheduler.h"

#include "Robot.h"

ChainBarSubsystem::ChainBarSubsystem() : m_chainBarMotor(CHAINBAR_MOTOR_PORT),
                                         m_rotationMotor(ROTATION_MOTOR_PORT) {

}

void ChainBarSubsystem::robotInit() {
    operatorJoystick->registerAxis(COREJoystick::JoystickAxis::RIGHT_STICK_X);
    operatorJoystick->registerAxis(COREJoystick::JoystickAxis::RIGHT_STICK_Y);
}

void ChainBarSubsystem::teleopInit() {

}

void ChainBarSubsystem::teleop() {
	SmartDashboard::PutNumber("Chainbar Motor Position", m_chainBarMotor.GetSensorCollection().GetAnalogInRaw());
	SmartDashboard::PutNumber("Rotation Motor Position", m_rotationMotor.GetSensorCollection().GetAnalogInRaw());
    double y = operatorJoystick->getAxis(COREJoystick::JoystickAxis::RIGHT_STICK_Y);
    if(abs(y) < 0.05) {
        setChainBar(y);
    } else {
        setChainBar(0);
    }

    double x = operatorJoystick->getAxis(COREJoystick::JoystickAxis::RIGHT_STICK_X);
    if(abs(x) < 0.05) {
        setRotation(x);
    } else {
        setRotation(0);
    }
}

void ChainBarSubsystem::setChainBar(double speed) {
    m_chainBarMotor.Set(ControlMode::PercentOutput, speed);
}

void ChainBarSubsystem::setRotation(double speed) {
    m_rotationMotor.Set(ControlMode::PercentOutput, speed);
}
