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
		m_chainBarAngleOffset("Chain Bar Angle Offset"),
		m_rotationAngleOffset("Rotation Angle Offset"),
		m_rotationTopLimit("Rotation Top Limit"),
		m_rotationBottomLimit("Rotation Bottom Limit"),
		m_chainBarUpP("Chain Bar Up PID P"),
		m_chainBarUpI("Chain Bar Up PID I"),
		m_chainBarUpD("Chain Bar Up PID D"),
		m_chainBarDownP("Chain Bar Down PID P"),
		m_chainBarDownI("Chain Bar Down PID I"),
		m_chainBarDownD("Chain Bar Down PID D"),
		m_rotationP("Rotation PID P"),
		m_rotationI("Rotation PID I"),
		m_rotationD("Rotation PID D"),
		m_maxAngularAcceleration("thing"),
		m_chainBarPID(0, 0, 0),
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
    m_requestedChainBarSpeed = 0;
    m_requestedRotationSpeed = 0;

    //int pos = m_rotationMotor.GetSelectedSensorPosition(0);

    //CORELog::logError("Rotation Value: " + to_string(pos));

    //m_rotationMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
    m_rotationMotor.SetSelectedSensorPosition(0, 0, 0);

    m_chainBarPID.setProportionalConstant(m_chainBarUpP.Get());
    m_chainBarPID.setIntegralConstant(m_chainBarUpI.Get());
    m_chainBarPID.setDerivativeConstant(m_chainBarUpD.Get());
//	SetChainBarRequestedAngle(GetChainBarAngle());

    m_rotationPID.setProportionalConstant(m_rotationP.Get());
    m_rotationPID.setIntegralConstant(m_rotationI.Get());
    m_rotationPID.setDerivativeConstant(m_rotationD.Get());
}

void ChainBarSubsystem::teleopInit() {
	SmartDashboard::PutNumber("Selected Sensor Position", m_chainBarMotor.GetSelectedSensorPosition(0));
	SmartDashboard::PutNumber("Get Selected Quadrature Position", 
                              m_chainBarMotor.GetSensorCollection().GetQuadraturePosition());
	m_chainBarPID.setProportionalConstant(m_chainBarUpP.Get());
	m_chainBarPID.setIntegralConstant(m_chainBarUpI.Get());
	m_chainBarPID.setDerivativeConstant(m_chainBarUpD.Get());
	SetChainBarRequestedAngle(GetChainBarAngle());

	m_rotationPID.setProportionalConstant(m_rotationP.Get());
	m_rotationPID.setIntegralConstant(m_rotationI.Get());
	m_rotationPID.setDerivativeConstant(m_rotationD.Get());
	SetRotationRequestedAngle(GetRotationAngle());
    SetChainBarSpeed(0);
    SetRotationSpeed(0);
}

void ChainBarSubsystem::teleop() {
	SetChainBarRequestedSpeed(-operatorJoystick->getAxis(COREJoystick::JoystickAxis::RIGHT_STICK_Y));
    SetRotationRequestedSpeed(operatorJoystick->getAxis(COREJoystick::JoystickAxis::RIGHT_STICK_X));
}

void ChainBarSubsystem::SetChainBarSpeed(double speed) {
	m_chainBarMotor.Set(ControlMode::PercentOutput, speed);
}

void ChainBarSubsystem::SetRotationSpeed(double speed) {
	m_rotationMotor.Set(ControlMode::PercentOutput, speed);
}

double ChainBarSubsystem::GetChainBarAngle(bool raw) {
	double rawAngle = 360 - (-m_chainBarMotor.GetSelectedSensorPosition(0) / 4096.0 * 360);
//		double rawAngle = 360 - (-m_chainBarMotor.GetSensorCollection().GetQuadraturePosition() / 4096.0 * 360);
	if (raw) {
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
    double rawAngle = (m_rotationMotor.GetSelectedSensorPosition(0) / 4096.0 * 360);
//	double rawAngle = 360 - (-m_rotationMotor.GetSensorCollection().GetQuadraturePosition() / 4096.0 * 360);
		rawAngle *= -1;
		if (raw) {
			return rawAngle;
		} else {
			return rawAngle - m_rotationAngleOffset.Get();
		}
}

void ChainBarSubsystem::SetRotationRequestedAngle(double angle) {
    m_requestedRotationAngle = angle;
}

void ChainBarSubsystem::postLoopTask() {
    double chainBarAngle = GetChainBarAngle();

    if (abs(m_requestedChainBarSpeed) > 0.01) {
        SetChainBarRequestedAngle(GetChainBarAngle());
    } else {
        if (m_requestedChainBarAngle > GetChainBarAngle()) {
            m_chainBarPID.setProportionalConstant(m_chainBarUpP.Get());
            m_chainBarPID.setIntegralConstant(m_chainBarUpI.Get());
            m_chainBarPID.setDerivativeConstant(m_chainBarUpD.Get());
            m_requestedChainBarSpeed = m_chainBarPID.calculate(m_requestedChainBarAngle - GetChainBarAngle());
        } else {
            m_chainBarPID.setProportionalConstant(m_chainBarDownP.Get());
            m_chainBarPID.setIntegralConstant(m_chainBarDownI.Get());
            m_chainBarPID.setDerivativeConstant(m_chainBarDownD.Get());
            m_requestedChainBarSpeed = m_chainBarPID.calculate(m_requestedChainBarAngle - GetChainBarAngle());
        }
    }
    
    /************************* Check Chain Bar Limits *************************/
    if (m_requestedChainBarSpeed < 0 && chainBarAngle < m_chainBarBottomLimit.Get()) { //Bottom limit of arm
        m_requestedChainBarSpeed = 0;
    } else if (CORE2018::GetInstance()->liftSubsystem.GetLiftPosition() < m_liftChangePoint.Get()
               && m_requestedChainBarSpeed > 0
               && chainBarAngle > m_chainBarLowerTopLimit.Get()) { //Top limit of arm below change point
        m_requestedChainBarSpeed = 0;
    } else if (m_requestedChainBarSpeed > 0 
               && chainBarAngle > m_chainBarUpperTopLimit.Get()) { //Top limit of arm above change point
        m_requestedChainBarSpeed = 0;
    }

    SetChainBarSpeed(m_requestedChainBarSpeed);
    m_requestedChainBarSpeed = 0;

    SmartDashboard::PutNumber("Chainbar Angle", GetChainBarAngle());
    SmartDashboard::PutNumber("Chainbar Requested Angle", m_requestedChainBarAngle);

    double rotationAngleRelative = GetRotationAngleRelativeToChainBar();
    if (abs(m_requestedRotationSpeed) > 0.01) {
        m_requestedRotationSpeed *= 0.8;
        SetRotationRequestedAngle(GetRotationAngle());
    } else {
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
        m_requestedRotationSpeed = m_rotationPID.calculate(m_requestedRotationAngle - GetRotationAngle());
        if (m_requestedRotationSpeed > 0 && rotationAngleRelative > m_rotationTopLimit.Get()) {
            m_requestedRotationSpeed = 0;
        } else if (m_requestedRotationSpeed < 0 && rotationAngleRelative < m_rotationBottomLimit.Get()) {
            m_requestedRotationSpeed = 0;
        }
    }
    
     //TODO: Fix the wrapping over zero point

//    if(m_requestedChainBarAngle > GetRotationAngleRelativeToChainBar() - 90) {
//        SetRotationRequestedAngle(GetRotationAngleRelativeToChainBar() + 90);
//    }

    SetRotationSpeed(m_requestedRotationSpeed);
    m_requestedRotationSpeed = 0;

    SmartDashboard::PutNumber("Rotation Angle", GetRotationAngle());
    SmartDashboard::PutNumber("Rotation Angle Relative To Chain Bar", GetRotationAngleRelativeToChainBar());
}

void ChainBarSubsystem::SetChainBarRequestedSpeed(double speed) {
    m_requestedChainBarSpeed = speed;
}

void ChainBarSubsystem::SetRotationRequestedSpeed(double speed) {
    m_requestedRotationSpeed = speed;
}
