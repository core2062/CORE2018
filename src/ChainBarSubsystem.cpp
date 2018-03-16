#include <ChainBarSubsystem.h>
#include "ctre/Phoenix.h"
#include "COREFramework/COREScheduler.h"

#include "COREUtilities/COREConstant.h"
#include "Robot.h"

ChainBarSubsystem::ChainBarSubsystem() :
        m_chainBarMotor(CHAINBAR_MOTOR_PORT),
        m_rotationMotor(ROTATION_MOTOR_PORT),
        m_chainBarLowerTopLimit("Chain Bar Lower Top Limit"),
        m_chainBarUpperTopLimit("Chain Bar Upper Top Limit"),
        m_chainBarBottomLimit("Chain Bar Bottom Limit"),
        m_liftChangePoint("Lift Change Point"),
        m_chainBarAngleOffset("Chain Bar Angle Offset"),
        m_chainBarPID(0, 0, 0),
        m_rotationPID(0, 0, 0),
        m_chainBarUpP("Chain Bar Up PID P"),
        m_chainBarUpI("Chain Bar Up PID I"),
        m_chainBarUpD("Chain Bar Up PID D"),
        m_chainBarDownP("Chain Bar Down PID P"),
        m_chainBarDownI("Chain Bar Down PID I"),
        m_chainBarDownD("Chain Bar Down PID D"),
        m_rotationP("Rotation PID P"),
        m_rotationI("Rotation PID I"),
        m_rotationD("Rotation PID D"),
        m_rotationAngleOffset("Rotation Angle Offset"),
        m_rotationTopLimit("Rotation Top Limit"),
        m_rotationBottomLimit("Rotation Bottom Limit") {

}

void ChainBarSubsystem::robotInit() {
    operatorJoystick->registerAxis(COREJoystick::JoystickAxis::RIGHT_STICK_X);
    operatorJoystick->registerAxis(COREJoystick::JoystickAxis::RIGHT_STICK_Y);
    m_chainBarMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);
    m_chainBarMotor.SetInverted(true);
    m_rotationMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);
    m_rotationMotor.SetInverted(true);
}

void ChainBarSubsystem::teleopInit() {
    m_chainBarPID.setProportionalConstant(m_chainBarUpP.Get());
    m_chainBarPID.setIntegralConstant(m_chainBarUpI.Get());
    m_chainBarPID.setDerivativeConstant(m_chainBarUpD.Get());
//    SetChainBarRequestedAngle(GetChainBarAngle());


    m_rotationPID.setProportionalConstant(m_rotationP.Get());
    m_rotationPID.setIntegralConstant(m_rotationI.Get());
    m_rotationPID.setDerivativeConstant(m_rotationD.Get());
    SetRotationRequestedAngle(GetRotationAngle());
}

void ChainBarSubsystem::teleop() {
    double chainBarSpeed = -operatorJoystick->getAxis(COREJoystick::JoystickAxis::RIGHT_STICK_Y);
    double chainBarAngle = GetChainBarAngle();

    if(abs(chainBarSpeed) > 0.01) {
        /************************* Check Chain Bar Limits *************************/
        if (chainBarSpeed < 0 && chainBarAngle < m_chainBarBottomLimit.Get()) { //Bottom limit of arm
            chainBarSpeed = 0;
        } else if (/*m_liftPosition > m_liftChangePoint.Get() && */ chainBarSpeed > 0 && chainBarAngle > m_chainBarLowerTopLimit.Get()) { //Top limit of arm below change point
            chainBarSpeed = 0;
        } else if (chainBarSpeed > 0 && chainBarAngle > m_chainBarUpperTopLimit.Get()) { //Top limit of arm above change point
            chainBarSpeed = 0;
        } else {
            SetChainBarRequestedAngle(GetChainBarAngle());
        }
    } else {
        if(m_requestedChainBarAngle > GetChainBarAngle()) {
            m_chainBarPID.setProportionalConstant(m_chainBarUpP.Get());
            m_chainBarPID.setIntegralConstant(m_chainBarUpI.Get());
            m_chainBarPID.setDerivativeConstant(m_chainBarUpD.Get());
            chainBarSpeed = m_chainBarPID.calculate(m_requestedChainBarAngle - GetChainBarAngle());
        } else {
            m_chainBarPID.setProportionalConstant(m_chainBarDownP.Get());
            m_chainBarPID.setIntegralConstant(m_chainBarDownI.Get());
            m_chainBarPID.setDerivativeConstant(m_chainBarDownD.Get());
            chainBarSpeed = m_chainBarPID.calculate(m_requestedChainBarAngle - GetChainBarAngle());
        }
    }

    SetChainBarSpeed(chainBarSpeed);

    SmartDashboard::PutNumber("Chainbar Angle", GetChainBarAngle());
    SmartDashboard::PutNumber("Chainbar Requested Angle", m_requestedChainBarAngle);

    double rotationSpeed = operatorJoystick->getAxis(COREJoystick::JoystickAxis::RIGHT_STICK_X);
    double rotationAngle = GetRotationAngle();
    double rotationAngleRelative = GetRotationAngleRelativeToChainBar();
    if(abs(rotationSpeed) > 0.01) {
        if(rotationSpeed > 0 && rotationAngleRelative > m_rotationTopLimit.Get()) {
            rotationSpeed = 0;
        } else if(rotationSpeed < 0 && rotationAngleRelative < m_rotationBottomLimit.Get()) {
            rotationSpeed = 0;
        } else {
            SetRotationRequestedAngle(GetRotationAngle());
        }
    } else {
        if(operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::DPAD_S)) {
            m_requestedRotationAngle = -180;
        } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::DPAD_E)) {
            m_requestedRotationAngle = -90;
        }
        rotationSpeed = m_rotationPID.calculate(m_requestedRotationAngle - GetRotationAngle());
    }

    SetRotationSpeed(rotationSpeed);

    SmartDashboard::PutNumber("Rotation Angle", GetRotationAngle());
    SmartDashboard::PutNumber("Rotation Angle Relative To Chain Bar", GetRotationAngleRelativeToChainBar());
}

void ChainBarSubsystem::SetChainBarSpeed(double speed) {
    m_chainBarMotor.Set(ControlMode::PercentOutput, speed);
}

void ChainBarSubsystem::SetRotationSpeed(double speed) {
    m_rotationMotor.Set(ControlMode::PercentOutput, speed);
}

double ChainBarSubsystem::GetChainBarAngle(bool raw) {
    double rawAngle = 360 - (-m_chainBarMotor.GetSelectedSensorPosition(0) / 4096.0 * 360);
    if(raw) {
        return rawAngle;
    } else {
        return rawAngle - m_chainBarAngleOffset.Get();
    }
}

void ChainBarSubsystem::SetChainBarRequestedAngle(double angle) {
    m_requestedChainBarAngle = angle;
}

double ChainBarSubsystem::GetRotationAngleRelativeToChainBar() {
    double rawAngle = GetRotationAngle();
    rawAngle -= GetChainBarAngle();

    return rawAngle;
}

double ChainBarSubsystem::GetRotationAngle(bool raw) {
    double rawAngle = 360 - (-m_rotationMotor.GetSelectedSensorPosition(0) / 4096.0 * 360);
    rawAngle *= -1;
    if(raw) {
        return rawAngle;
    } else {
        return rawAngle - m_rotationAngleOffset.Get();
    }
}

void ChainBarSubsystem::SetRotationRequestedAngle(double angle) {
    m_requestedRotationAngle = angle;
}
