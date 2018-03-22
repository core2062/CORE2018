#pragma once

//#include "Robot.h"
#include "ctre/Phoenix.h"
#include <CORERobotLib.h>
//#include "COREKinematics/SwerveTracker.h"
#include "AHRS.h"
#include "COREFramework/COREScheduler.h"

#include "WaypointFollower/WaypointFollower.h"


class DriveSubsystem : public CORESubsystem, public CORETask {
public:
	DriveSubsystem();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void teleopEnd() override;
	void preLoopTask();
	void resetEncoders();
	void initTalons();
	void autonInitTask() override;
	double getGyroYaw(bool raw = false);
	bool pathDone();
	void resetYaw();
	void zeroMotors();

	void startPath(Path path, bool reversed, double maxAccel, double maxAngAccel,
                   double tolerance, bool gradualStop, double lookahead);
	void resetTracker(Position2d initialPos);
	Path m_path;
	AdaptivePursuit m_pursuit;
	COREVector path;

private:
	double m_wheelbase = 20.8;
	double m_trackwidth = 25.881;
	COREConstant <double> m_steerPID_P, m_steerPID_I, m_steerPID_D, m_rotationkP;
	TalonSRX m_rightFrontSteerMotor, m_leftFrontSteerMotor, m_rightBackSteerMotor, m_leftBackSteerMotor,
			m_rightFrontDriveMotor, m_leftFrontDriveMotor, m_rightBackDriveMotor, m_leftBackDriveMotor;
	CORESwerve::SwerveModule *m_rightFrontModule, *m_leftFrontModule, *m_rightBackModule, *m_leftBackModule;
	CORESwerve* m_swerveDrive;
	AHRS *m_gyro;
	double m_x, m_y, m_theta, m_gyroOffset;
    int count = 0;
};
