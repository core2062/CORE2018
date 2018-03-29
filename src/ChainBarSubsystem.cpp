#include <ChainBarSubsystem.h>
#include "ctre/Phoenix.h"
#include "COREFramework/COREScheduler.h"

#include "COREUtilities/COREConstant.h"
#include "COREControl/COREPID.h"
#include "Robot.h"

ChainBarSubsystem::ChainBarSubsystem() :
		m_chainBarMotor(CHAINBAR_MOTOR_PORT),
		m_rotationMotor(ROTATION_MOTOR_PORT),
		m_chainBarLowerTopLimit("Chain Bar Lower Top Limit"),
		m_chainBarUpperTopLimit("Chain Bar Upper Top Limit"),
		m_chainBarBottomLimit("Chain Bar Bottom Limit"),
		m_liftChangePoint("Lift Change Point"),
		m_rotationTopLimit("Rotation Top Limit"),
		m_rotationBottomLimit("Rotation Bottom Limit"),
        m_chainBarMaxAcel("Chain Bar Max Acceleration"),
        m_chainBarCruiseVel("Chain Bar Cruise Velocity"),
        m_rotationMaxAcel("Rotation Max Acceleration"),
        m_rotationCruiseVel("Rotation Cruise Velocity"),
        m_chainBarIntakePostionAngle("Chain Bar Intake Position Angle"),
        m_rotationIntakePostionAngle("Rotation Intake Position Angle"),
		m_rotationPID(0, 0, 0) {

}

void ChainBarSubsystem::robotInit() {
	operatorJoystick->registerAxis(COREJoystick::JoystickAxis::RIGHT_STICK_X);
	operatorJoystick->registerAxis(COREJoystick::JoystickAxis::RIGHT_STICK_Y);
    operatorJoystick->registerButton(COREJoystick::JoystickButton::DPAD_N);
    operatorJoystick->registerButton(COREJoystick::JoystickButton::DPAD_NE);
    operatorJoystick->registerButton(COREJoystick::JoystickButton::DPAD_E);
    operatorJoystick->registerButton(COREJoystick::JoystickButton::DPAD_SE);
    operatorJoystick->registerButton(COREJoystick::JoystickButton::DPAD_S);
    operatorJoystick->registerButton(COREJoystick::JoystickButton::DPAD_SW);
    operatorJoystick->registerButton(COREJoystick::JoystickButton::DPAD_W);
    operatorJoystick->registerButton(COREJoystick::JoystickButton::DPAD_NW);

	m_chainBarMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);
	m_chainBarMotor.SetInverted(true);

	m_rotationMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);
	m_rotationMotor.SetInverted(true);
    m_rotationMotor.SetSensorPhase(true);

    m_requestedChainBarSpeed = 0;
    m_requestedRotationSpeed = 0;

    SmartDashboard::PutBoolean("Zero Rotation", false);

    SmartDashboard::PutBoolean("Zero Chain Bar", false);

    //int pos = m_rotationMotor.GetSelectedSensorPosition(0);

    //CORELog::logError("Rotation Value: " + to_string(pos));

    //m_rotationMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
//    m_rotationMotor.SetSelectedSensorPosition(0, 0, 0);

//	SetChainBarRequestedAngle(GetChainBarAngle());
}

void ChainBarSubsystem::teleopInit() {
    m_chainBarMotor.ConfigMotionCruiseVelocity(m_chainBarCruiseVel.Get(), 0);
    m_chainBarMotor.ConfigMotionAcceleration(m_chainBarMaxAcel.Get(), 0);

	SetChainBarRequestedAngle(GetChainBarAngle());
    SetChainBarSpeed(0);

    m_rotationMotor.ConfigMotionCruiseVelocity(m_rotationCruiseVel.Get(), 0);
    m_rotationMotor.ConfigMotionAcceleration(m_rotationMaxAcel.Get(), 0);

	SetRotationRequestedAngle(GetRotationAngle());
    SetRotationSpeed(0);

    if(SmartDashboard::GetBoolean("Zero Rotation", false)) {
        SmartDashboard::PutBoolean("Zero Rotation", false);
        m_rotationMotor.SetSelectedSensorPosition(0, 0, 0);
    }

    if(SmartDashboard::GetBoolean("Zero Chain Bar", false)) {
        SmartDashboard::PutBoolean("Zero Chain Bar", false);
        m_chainBarMotor.SetSelectedSensorPosition(0, 0, 0);
    }
}

void ChainBarSubsystem::teleop() {

}

void ChainBarSubsystem::SetChainBarSpeed(double speed) {
	m_chainBarMotor.Set(ControlMode::PercentOutput, speed);
}

void ChainBarSubsystem::SetRotationSpeed(double speed) {
	m_rotationMotor.Set(ControlMode::PercentOutput, speed);
}

double ChainBarSubsystem::GetChainBarAngle(bool raw) {
	double rawAngle = (m_chainBarMotor.GetSelectedSensorPosition(0) / 4096.0 * 360);
//		double rawAngle = 360 - (-m_chainBarMotor.GetSensorCollection().GetQuadraturePosition() / 4096.0 * 360);
	return rawAngle;
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
    double rawAngle = (m_rotationMotor.GetSelectedSensorPosition(0) / 4096.0 * 360);
//	double rawAngle = 360 - (-m_rotationMotor.GetSensorCollection().GetQuadraturePosition() / 4096.0 * 360);
    return rawAngle;
}

void ChainBarSubsystem::SetRotationRequestedAngle(double angle) {
    m_requestedRotationAngle = angle;
}

void ChainBarSubsystem::postLoopTask() {
    SmartDashboard::PutNumber("Chain Bar Position", m_chainBarMotor.GetSelectedSensorPosition(0));
    SmartDashboard::PutNumber("Chain Bar Velocity", m_chainBarMotor.GetSelectedSensorVelocity(0));
    SmartDashboard::PutNumber("Requested Chain Bar Angle", m_requestedChainBarAngle);
    SmartDashboard::PutNumber("Chain Bar Angle", GetChainBarAngle());


    SetChainBarRequestedSpeed(-operatorJoystick->getAxis(COREJoystick::JoystickAxis::RIGHT_STICK_Y));
    SetRotationRequestedSpeed(operatorJoystick->getAxis(COREJoystick::JoystickAxis::RIGHT_STICK_X));

    double chainBarAngle = GetChainBarAngle();
    if (abs(m_requestedChainBarSpeed) > 0.01) {
        SetChainBarRequestedAngle(chainBarAngle);
    } else {
        m_chainBarMotor.Set(ControlMode::MotionMagic, m_requestedChainBarAngle * 4096.0 / 360);
    }

    /************************* Check Chain Bar Limits *************************/
    if (m_chainBarMotor.GetMotorOutputPercent() < 0 && chainBarAngle < m_chainBarBottomLimit.Get()) { //Bottom limit of arm
        m_requestedChainBarSpeed = 0;
        m_chainBarMotor.Set(ControlMode::PercentOutput, 0);
        SetChainBarRequestedAngle(m_chainBarBottomLimit.Get());
    } else if (CORE2018::GetInstance()->liftSubsystem.GetLiftPosition() < m_liftChangePoint.Get()
               && m_chainBarMotor.GetMotorOutputPercent() > 0
               && chainBarAngle > m_chainBarLowerTopLimit.Get()) { //Top limit of arm below change point
        m_requestedChainBarSpeed = 0;
        m_chainBarMotor.Set(ControlMode::PercentOutput, 0);
        SetChainBarRequestedAngle(m_chainBarLowerTopLimit.Get());
    } else if (m_chainBarMotor.GetMotorOutputPercent() > 0
               && chainBarAngle > m_chainBarUpperTopLimit.Get()) { //Top limit of arm above change point
        m_requestedChainBarSpeed = 0;
        m_chainBarMotor.Set(ControlMode::PercentOutput, 0);
        SetChainBarRequestedAngle(m_chainBarUpperTopLimit.Get());
    }

    if (abs(m_requestedChainBarSpeed) > 0.01) {
        m_chainBarMotor.Set(ControlMode::PercentOutput, m_requestedChainBarSpeed);
    }

    m_requestedChainBarSpeed = 0;

    SmartDashboard::PutNumber("Rotation Position", m_rotationMotor.GetSelectedSensorPosition(0));
    SmartDashboard::PutNumber("Rotation Velocity", m_rotationMotor.GetSelectedSensorVelocity(0));
    SmartDashboard::PutNumber("Rotation Angle", GetRotationAngle());

    if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::DPAD_N)) {
        SetRotationRequestedAngle(0);
    } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::DPAD_NE)) {
        SetRotationRequestedAngle(-45);
    } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::DPAD_E)) {
        SetRotationRequestedAngle(-90);
    } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::DPAD_SE)) {
        SetRotationRequestedAngle(-135);
    } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::DPAD_S)) {
        if(GetChainBarAngle() < 0) {
            SetRotationRequestedAngle(-180);
        } else {
            SetRotationRequestedAngle(180);
        }
    } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::DPAD_SW)) {
        SetRotationRequestedAngle(135);
    } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::DPAD_W)) {
        SetRotationRequestedAngle(90);
    } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::DPAD_NW)) {
        SetRotationRequestedAngle(45);
    }

    if (abs(m_requestedRotationSpeed) > 0.01) {
        m_requestedRotationSpeed *= 0.8;
        SetRotationRequestedAngle(GetRotationAngle());
    } else {
        m_rotationMotor.Set(ControlMode::MotionMagic, m_requestedRotationAngle * 4096.0 / 360);
    }

    if (abs(m_requestedRotationSpeed) > 0.01) {
        m_rotationMotor.Set(ControlMode::PercentOutput, m_requestedRotationSpeed);
    }

    m_requestedRotationSpeed = 0;

    SmartDashboard::PutNumber("Requested Rotation Angle", m_requestedRotationAngle);
    SmartDashboard::PutNumber("Rotation Angle Relative To Chain Bar", GetRotationAngleRelativeToChainBar());
}

void ChainBarSubsystem::SetChainBarRequestedSpeed(double speed) {
    m_requestedChainBarSpeed = speed;
}

void ChainBarSubsystem::SetRotationRequestedSpeed(double speed) {
    m_requestedRotationSpeed = speed;
}

void ChainBarSubsystem::SetIntakePosition() {
    SetRotationRequestedAngle(m_rotationIntakePostionAngle.Get());
    SetChainBarRequestedAngle(m_chainBarIntakePostionAngle.Get());
}
