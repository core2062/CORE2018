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
    m_chainBarMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);
    m_rotationMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);
    m_chainBarMotor.SetSensorPhase(true);
}

void ChainBarSubsystem::teleopInit() {

}

void ChainBarSubsystem::teleop() {
    double y = operatorJoystick->getAxis(COREJoystick::JoystickAxis::RIGHT_STICK_X);
    if(abs(y) > 0.01) {
        setChainBar(y);
    } else {
        setChainBar(0);
    }

    SmartDashboard::PutNumber("Chainbar Encoder", m_chainBarMotor.GetSelectedSensorPosition(0));

    double x = operatorJoystick->getAxis(COREJoystick::JoystickAxis::RIGHT_STICK_Y);
    if(abs(x) > 0.01) {
        setRotation(x);
    } else {
        setRotation(0);
    }
    SmartDashboard::PutNumber("Rotation Encoder", m_rotationMotor.GetSelectedSensorPosition(0));

}

void ChainBarSubsystem::setChainBar(double speed) {
    m_chainBarMotor.Set(ControlMode::PercentOutput, speed);
}

void ChainBarSubsystem::setRotation(double speed) {
    m_rotationMotor.Set(ControlMode::PercentOutput, speed);
}
