#pragma once

//#include "Robot.h"
#include "ctre/Phoenix.h"
#include <CORERobotLib.h>
//#include "COREKinematics/SwerveTracker.h"
#include "AHRS.h"
#include "COREFramework/COREScheduler.h"

#include "WaypointFollower/WaypointFollower.h"
#include "COREUtilities/CORETimer.h"


class DriveSubsystem : public CORESubsystem, public CORETask {
public:
	DriveSubsystem();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void teleopEnd() override;
	void preLoopTask();
	void initTalons();
	void autonInitTask() override;
	double getGyroYaw(bool raw = false);
	bool pathDone();
	void resetYaw();
	void zeroMotors();

	void startPath(Path path, bool reversed, double maxAccel, double maxAngAccel,
                   double tolerance, bool gradualStop, double lookahead);
	void resetTracker(Position2d initialPos);
	AdaptivePursuit m_pursuit;
	COREVector path;
	CORESwerve* m_swerveDrive;
	CORETimer m_timer;

private:
	double m_wheelbase = 20.8;
	double m_trackwidth = 25.881;
	COREConstant <double> m_steerPID_P, m_steerPID_I, m_steerPID_D, m_rotationkP;
	TalonSRX m_frontRightSteerMotor, m_frontLeftSteerMotor, m_backRightSteerMotor, m_backLeftSteerMotor,
			m_frontRightDriveMotor, m_frontLeftDriveMotor, m_backRightDriveMotor, m_backLeftDriveMotor;
	CORESwerve::SwerveModule *m_frontRightModule, *m_frontLeftModule, *m_backRightModule, *m_backLeftModule;
	AHRS *m_gyro;
	double m_x, m_y, m_theta, m_thetaOffset, m_gyroOffset;
    int count = 0;
};
