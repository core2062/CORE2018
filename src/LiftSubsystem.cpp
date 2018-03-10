#include <LiftSubsystem.h>
#include "ctre/Phoenix.h"
#include "Robot.h"
#include "COREFramework/COREScheduler.h"

LiftSubsystem::LiftSubsystem() {
		m_leftLiftMotor(LEFT_LIFT_MOTOR_PORT),
		m_rightLiftMotor(RIGHT_LIFT_MOTOR_PORT),
		m_liftTopLimit("Lift Top Limit"),
		m_liftBottomLimitSwitch(LIFT_BOTTOM_LIMIT_SWITCH); {
	m_liftPosition = 0;
	m_leftLiftMotor.SetInverted(true);
	m_liftPID(0,0,0);
}
}
void LiftSubsystem::robotInit() {
	m_leftLiftMotor.Set(ControlMode::PercentOutput, 0);
	m_rightLiftMotor.Set(ControlMode::PercentOutput, 0);
    m_leftLiftMotor.SetNeutralMode(NeutralMode::Brake);
    m_rightLiftMotor.SetNeutralMode(NeutralMode::Brake);
    m_rightLiftMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
    m_rightLiftMotor.SetSelectedSensorPosition(0, 0, 0);
    m_rightLiftMotor.SetSensorPhase(true);
    operatorJoystick->registerAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
}

void LiftSubsystem::teleopInit() {
	m_liftPID.setProportionalConstant(m_liftUpP.Get());
	m_liftPID.setIntegralConstant(m_liftUpI.Get());
	m_liftPID.setDerivativeConstant(m_liftUpD.Get());
}

void LiftSubsystem::teleop() {
    SmartDashboard::PutNumber("Lift Speed", y);
    SmartDashboard::PutNumber("Lift Encoder", m_rightLiftMotor.GetSelectedSensorPosition(0));
/*in progress code*/
    double liftSpeed = operatorJoystick -> getAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_X);
    double liftHeight = m_liftPosition();
    if(abs(liftSpeed) > 0.01) {
    	if(liftSpeed > 0 && liftHeight > m_liftTopLimit.Get()) {
                liftSpeed = 0;
            } else if(liftSpeed < 0 && liftHeight < m_liftBottomLimit.Get()) {
                liftSpeed = 0;
            } else {
                liftSpeed() = liftSpeed;
            }
		} else {
			if(liftSpeed > liftHeight){
				m_liftPID.setProportionalConstant(m_liftUpP.Get());
				m_liftPID.setIntegralConstant(m_liftUpI.Get());
				m_liftPID.setDerivativeConstant(m_liftUpD.Get());
				liftSpeed = m_liftPID.calculate(m_liftPosition - liftHeight());
		} else{
				m_liftPID.setProportionalConstant(m_liftUpP.Get());
				m_liftPID.setIntegralConstant(m_liftUpI.Get());
				m_liftPID.setDerivativeConstant(m_liftUpD.Get());
				liftSpeed = m_liftPID.calculate(m_liftPosition - liftHeight());
		}
}
setLift(liftSpeed);
SmartDashboard::PutNumber("Lift Height", liftHeight());
        }

void LiftSubsystem::setLift(double liftMotorPercentage) {
	m_leftLiftMotor.Set(ControlMode::PercentOutput, liftMotorPercentage);
	m_rightLiftMotor.Set(ControlMode::PercentOutput, liftMotorPercentage);
}
