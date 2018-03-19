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
	m_chainBarMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);
	m_chainBarMotor.SetInverted(true);
	m_rotationMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);
	m_rotationMotor.SetInverted(true);
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
}

void ChainBarSubsystem::teleop() {
	SetChainBarRequestedSpeed(-operatorJoystick->getAxis(COREJoystick::JoystickAxis::RIGHT_STICK_Y));
    SetRotationRequestedSpeed(operatorJoystick->getAxis(COREJoystick::JoystickAxis::RIGHT_STICK_X));
}

void ChainBarSubsystem::SetChainBarSpeed(double speed) {
	m_chainBarMotor.Set(ControlMode::PercentOutput, speed);
}

void ChainBarSubsystem::SetRotationSpeed(double speed) {
	m_rotationMotor.Set(ControlMode::PercentOutput, speed * 0.8);
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
    double rawAngle = 360 - (-m_rotationMotor.GetSelectedSensorPosition(0) / 4096.0 * 360);
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
    double chainBarAngle = GetChainBarAngle(m_firstIteration);

    if (abs(m_requestedChainBarSpeed) > 0.01) {
        SetChainBarRequestedAngle(GetChainBarAngle(m_firstIteration));
    } else {
        if (m_requestedChainBarAngle > GetChainBarAngle(m_firstIteration)) {
            m_chainBarPID.setProportionalConstant(m_chainBarUpP.Get());
            m_chainBarPID.setIntegralConstant(m_chainBarUpI.Get());
            m_chainBarPID.setDerivativeConstant(m_chainBarUpD.Get());
            m_requestedChainBarSpeed = m_chainBarPID.calculate(m_requestedChainBarAngle - GetChainBarAngle(m_firstIteration));
        } else {
            m_chainBarPID.setProportionalConstant(m_chainBarDownP.Get());
            m_chainBarPID.setIntegralConstant(m_chainBarDownI.Get());
            m_chainBarPID.setDerivativeConstant(m_chainBarDownD.Get());
            m_requestedChainBarSpeed = m_chainBarPID.calculate(m_requestedChainBarAngle - GetChainBarAngle(m_firstIteration));
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

    SmartDashboard::PutNumber("Chainbar Angle", GetChainBarAngle(m_firstIteration));
    SmartDashboard::PutNumber("Chainbar Requested Angle", m_requestedChainBarAngle);

    double rotationAngleRelative = GetRotationAngleRelativeToChainBar();
    if (abs(m_requestedRotationSpeed) > 0.01) {
        SetRotationRequestedAngle(GetRotationAngle(m_firstIteration));
    } else {
        if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::DPAD_N)) {
            m_requestedRotationAngle = 0;
        } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::DPAD_NE)) {
            m_requestedRotationAngle = -45;
        } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::DPAD_E)) {
            m_requestedRotationAngle = -90;
        } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::DPAD_SE)) {
            m_requestedRotationAngle = -135;
        } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::DPAD_S)) {
            if(GetRotationAngle(false) < 0) {
                m_requestedRotationAngle = -180;
            } else {
                m_requestedRotationAngle = 180;
            }
        }  else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::DPAD_SW)) {
            m_requestedRotationAngle = 135;
        } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::DPAD_W)) {
            m_requestedRotationAngle = 90;
        } else if (operatorJoystick->getRisingEdge(COREJoystick::JoystickButton::DPAD_NW)) {
            m_requestedRotationAngle = 45;
        }
        m_requestedRotationSpeed = m_rotationPID.calculate(m_requestedRotationAngle - GetRotationAngle(m_firstIteration));
    }
    
    if (m_requestedRotationSpeed > 0 && rotationAngleRelative > m_rotationTopLimit.Get()) {
        m_requestedRotationSpeed = 0;
    } else if (m_requestedRotationSpeed < 0 && rotationAngleRelative < m_rotationBottomLimit.Get()) {
        m_requestedRotationSpeed = 0;
    }

    SetRotationSpeed(m_requestedRotationSpeed);
    m_requestedRotationSpeed = 0;

    SmartDashboard::PutNumber("Rotation Angle", GetRotationAngle(m_firstIteration));
    SmartDashboard::PutNumber("Rotation Angle Relative To Chain Bar", GetRotationAngleRelativeToChainBar());
}

void ChainBarSubsystem::SetChainBarRequestedSpeed(double speed) {
    m_requestedChainBarSpeed = speed;
}

void ChainBarSubsystem::SetRotationRequestedSpeed(double speed) {
    m_requestedRotationSpeed = speed;
}
