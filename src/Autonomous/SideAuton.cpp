#include "SideAuton.h"
#include "Robot.h"

SideAuton::SideAuton() :
        COREAuton("Side Auton") {
    m_moveToSwitch = new Node(5, new LiftAction(liftAction::SWITCH));
	m_outtakeCubeToSwitch = new Node(5, new ScorerAction(scorerAction::OPEN));
	m_intakeCube = new Node(5, new ScorerAction(scorerAction::CLOSED));
	m_moveToScale = new Node(5, new LiftAction(liftAction::SCALE));
//	m_liftUpToScale = new Node(5, new LiftAction(liftAction::SCALE));
	m_outtakeCubeToScale = new Node(5, new ScorerAction(scorerAction::OPEN));
	m_driveToCubes = new Node(5, new DriveDistanceAction());
	m_intakeSecondCube = new Node(5, new ScorerAction(scorerAction::CLOSED));
	m_driveToScaleSecondTime = new Node(5, new DriveDistanceAction(), new LiftAction(liftAction::SCALE));
//	m_liftUpToScaleSecondTime = new Node(5, new LiftAction(liftAction::SCALE));
	m_outtakeSecondCube = new Node(5, new ScorerAction(scorerAction::OPEN));
}

void SideAuton::addNodes() {
    if(CORE2018::GetInstance()->gameDataParser.getStartingPosition() == RIGHT_SIDE) {
        CORE2018::GetInstance()->driveSubsystem.resetTracker(Position2d(Translation2d(97, 19),
                                                                        Rotation2d::fromRadians(-PI / 2)));
        CORELog::logInfo("Setting to right side");
    } else {
        CORE2018::GetInstance()->driveSubsystem.resetTracker(Position2d(Translation2d(-97, 19),
                                                                        Rotation2d::fromRadians(PI / 2)));
        CORELog::logInfo("Setting to left side");
    }
	switch (CORE2018::GetInstance()->gameDataParser.getCubePlacement()) {
        case SWITCH1:
            m_moveToSwitch->addAction(
                    new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.getWallToSwitchPath()));
            addFirstNode(m_moveToSwitch);
            m_moveToSwitch->addNext(m_outtakeCubeToSwitch);
            break;
        case SCALE1:
            m_moveToScale
                    ->addAction(new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.getWallToScalePath()));
            addFirstNode(m_moveToScale);
            m_moveToScale->addNext(m_outtakeCubeToScale);
            break;
//        case SWITCH1SCALE1:
//            m_moveToSwitch->
//                    addAction(new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.getWallToSwitchPath()));
//            addFirstNode(m_moveToSwitch);
//            m_moveToSwitch->addNext(m_outtakeCubeToSwitch);
//            m_moveToCubeStack =
//                    new Node(5, new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.loadPath(sidePath::)));
//            m_outtakeCubeToSwitch->addNext(m_moveToCubeStack);
//            m_m
//            break;
	}
}

