#include <ChainBarSubsystem.h>

#include "Robot.h"

ChainBarSubsystem::ChainBarSubsystem() : chainBarMotor(CHAINBAR_MOTOR_PORT),
                                         rotationMotor(ROTATION_MOTOR_PORT) {

}

void ChainBarSubsystem::robotInit() {
    operatorJoystick->registerAxis(COREJoystick::JoystickAxis::RIGHT_STICK_X);
    operatorJoystick->registerAxis(COREJoystick::JoystickAxis::RIGHT_STICK_Y);
}

void ChainBarSubsystem::teleopInit() {

}

void ChainBarSubsystem::teleop() {
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
    chainBarMotor.Set(ControlMode::PercentOutput, speed);
}

void ChainBarSubsystem::setRotation(double speed) {
    rotationMotor.Set(ControlMode::PercentOutput, speed);
}
