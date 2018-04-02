#include "SideAuton.h"
#include "Robot.h"

SideAuton::SideAuton() : COREAuton("Side Auton") {
    m_moveToSwitch = new Node(5, new StateAction(WantedState::WANT_TO_SCORE_ON_SWITCH));
	m_dropCube = new Node(1, new ScorerAction(scorerAction::OPEN));
	m_moveToScale = new Node(5, new StateAction(WantedState::WANT_TO_SCORE_ON_SCALE_BEHIND));
    m_raiseToScale = new Node(1, new StateAction(WantedState::WANT_TO_SCORE_ON_SCALE_BEHIND));
    m_intakeCube = new Node(5, new StateAction(WantedState::WANT_TO_PICKUP_CUBE), new IntakeAction(intakeAction::WIDE_RANGE_INTAKE));
    m_driveForward = new Node(5);
}

void SideAuton::addNodes() {
    if(CORE2018::GetInstance()->gameDataParser.GetStartingPosition() == RIGHT_SIDE) {
        CORE2018::GetInstance()->driveSubsystem.resetTracker(Position2d(Translation2d(97, 19),
                                                                        Rotation2d::fromRadians(-PI / 2)));
        CORELog::logInfo("Setting robot position to right side");
    } else {
        CORE2018::GetInstance()->driveSubsystem.resetTracker(Position2d(Translation2d(-97, 19),
                                                                        Rotation2d::fromRadians(PI / 2)));
        CORELog::logInfo("Setting robot position to left side");
    }

    DriveWaypointAction* driveAction;
	switch (CORE2018::GetInstance()->gameDataParser.GetCubePlacement()) {
        case DRIVE_FORWARD:
            addFirstNode(m_driveForward);
            bool flip = CORE2018::GetInstance()->gameDataParser.GetStartingPosition() == LEFT_SIDE;
            driveAction = new DriveWaypointAction(CORE2018::GetInstance()->
                    gameDataParser.LoadPath(sidePath::DRIVE_FORWARD, flip));
            m_driveForward->addAction(driveAction);
        case SWITCH1:
            addFirstNode(m_moveToSwitch);
            driveAction = new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.GetWallToSwitchPath());
            m_moveToSwitch->addAction(driveAction);
            m_moveToSwitch->addNext(m_dropCube);
            break;
        case SCALE1:
            addFirstNode(m_moveToScale);
            driveAction = new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.GetWallToScalePath());
            m_moveToScale->addAction(driveAction);
            m_moveToScale->addNext(m_dropCube);
            break;
        case SWITCH1SCALE1:
            addFirstNode(m_moveToScale);
            driveAction = new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.GetWallToScalePath());
            m_moveToScale->addAction(driveAction);
            m_moveToScale->addNext(m_dropCube);
            m_dropCube->addCondition([]{
                return CORE2018::GetInstance()->gameDataParser.GetWallToScalePath().eventPassed("switchWaypoint");
            });
            m_dropCube->addNext(m_intakeCube);
            break;
//        case SWITCH1SCALE1:
//            m_moveToSwitch->
//                    addAction(new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.getWallToSwitchPath()));
//            addFirstNode(m_moveToSwitch);
//            m_moveToSwitch->addNext(m_dropCube);
//            m_moveToCubeStack =
//                    new Node(5, new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.loadPath(sidePath::)));
//            m_dropCube->addNext(m_moveToCubeStack);
//            m_m
//            break;
	}
}

