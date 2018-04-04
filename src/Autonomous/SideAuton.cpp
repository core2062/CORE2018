#include "SideAuton.h"
#include "Robot.h"

SideAuton::SideAuton() : COREAuton("Side Auton") {

}

void SideAuton::addNodes() {
    m_moveToSwitch = new Node(14, new StateAction(WantedState::WANT_TO_SCORE_ON_SWITCH));
    m_dropCube = new Node(2, new ScorerAction(scorerAction::OPEN));
    m_moveToScale = new Node(9);
    m_raiseToScale = new Node(5, new StateAction(WantedState::WANT_TO_SCORE_ON_SCALE, WantedScaleScoreHeight::MID_SCALE));
    m_intakeCube = new Node(5, new StateAction(WantedState::WANT_TO_PICKUP_CUBE), new IntakeAction(intakeAction::WIDE_RANGE_INTAKE));
    m_driveForward = new Node(5);
    m_waitingToBringLiftUp = new Node(5);

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
        case DRIVE_FORWARD: {
            addFirstNode(m_driveForward);
            bool flip = CORE2018::GetInstance()->gameDataParser.GetStartingPosition() == LEFT_SIDE;
            driveAction = new DriveWaypointAction(CORE2018::GetInstance()->
                    gameDataParser.LoadPath(sidePath::DRIVE_FORWARD, flip));
            m_driveForward->addAction(driveAction);
            m_driveForward->addNext(m_dropCube);
        }
            break;
        case SWITCH1: {
            addFirstNode(m_moveToSwitch);
            driveAction = new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.GetWallToSwitchPath());
            m_moveToSwitch->addAction(driveAction);
            m_moveToSwitch->addNext(m_dropCube);
        }
            break;
        case SCALE1: {
            addFirstNode(m_moveToScale);
            addFirstNode(m_waitingToBringLiftUp);
            if(CORE2018::GetInstance()->gameDataParser.IsScaleRight() && CORE2018::GetInstance()->gameDataParser.GetStartingPosition() == RIGHT_SIDE
               || CORE2018::GetInstance()->gameDataParser.IsScaleLeft() && CORE2018::GetInstance()->gameDataParser.GetStartingPosition() == LEFT_SIDE) {
                m_waitingToBringLiftUp->addAction(new WaitAction(2));
                CORELog::logInfo("2 sec delay");
            } else {
                m_waitingToBringLiftUp->addAction(new WaitAction(5));
                CORELog::logInfo("6 sec delay");
            }
            m_waitingToBringLiftUp->addNext(m_raiseToScale);
            driveAction = new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.GetWallToScalePath());
            m_moveToScale->addAction(driveAction);
            m_moveToScale->addNext(m_dropCube);
        }
            break;
        case SWITCH1SCALE1: {
            addFirstNode(m_moveToSwitch);
            driveAction = new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.GetWallToSwitchPath());
            m_moveToSwitch->addAction(driveAction);
            m_moveToSwitch->addNext(m_dropCube);
            driveAction = new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.GetSwitchToCubePath());
            m_moveToCubeStack->addAction(driveAction);
            m_dropCube->addNext(m_moveToCubeStack);
            m_moveToCubeStack->addNext(m_intakeCube);
            m_intakeCube->addNext(m_waitingToBringLiftUp);
            m_waitingToBringLiftUp->addAction(new WaitAction(1));
            /*if(CORE2018::GetInstance()->gameDataParser.IsScaleRight() && CORE2018::GetInstance()->gameDataParser.GetStartingPosition() == RIGHT
                    || CORE2018::GetInstance()->gameDataParser.IsScaleLeft() && CORE2018::GetInstance()->gameDataParser.GetStartingPosition() == LEFT) {
                m_waitingToBringLiftUp->addAction(new WaitAction(2));
            } else {
                m_waitingToBringLiftUp->addAction(new WaitAction(6));
            }*/
            driveAction = new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.GetScaleToCubePath());
            m_moveToScaleFromCube->addAction(driveAction);
            m_waitingToBringLiftUp->addNext(m_moveToScaleFromCube);
            m_moveToScaleFromCube->addNext(m_dropCube);
        }
            break;
        case SWITCH1SCALE2: {
            addFirstNode(m_moveToSwitch);
            driveAction = new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.GetWallToSwitchPath());
            m_moveToSwitch->addAction(driveAction);
            m_moveToSwitch->addNext(m_dropCube);
            driveAction = new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.GetSwitchToCubePath());
            m_moveToCubeStack->addAction(driveAction);
            m_dropCube->addNext(m_moveToCubeStack);
            m_moveToCubeStack->addNext(m_intakeCube);
            m_intakeCube->addNext(m_waitingToBringLiftUp);
            if(CORE2018::GetInstance()->gameDataParser.IsScaleRight() && CORE2018::GetInstance()->gameDataParser.GetStartingPosition() == RIGHT
                    || CORE2018::GetInstance()->gameDataParser.IsScaleLeft() && CORE2018::GetInstance()->gameDataParser.GetStartingPosition() == LEFT) {
                m_waitingToBringLiftUp->addAction(new WaitAction(2));
            } else {
                m_waitingToBringLiftUp->addAction(new WaitAction(6));
            }
            driveAction = new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.GetScaleToCubePath());
            m_moveToScaleFromCube->addAction(driveAction);
            m_waitingToBringLiftUp->addNext(m_moveToScaleFromCube);
            m_moveToScaleFromCube->addNext(m_dropCube);
            driveAction = new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.GetScaleToCubePath());
            m_dropCube->addNext(m_moveToCubeStackSecondTime);
            m_moveToCubeStackSecondTime->addNext(m_intakeCube);
            driveAction = new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.GetScaleToCubePath());
            m_moveToScaleSecondTime->addAction(driveAction);
            m_intakeCube->addNext(m_waitingToBringLiftUp);
            if(CORE2018::GetInstance()->gameDataParser.IsScaleRight() && CORE2018::GetInstance()->gameDataParser.GetStartingPosition() == RIGHT
                    || CORE2018::GetInstance()->gameDataParser.IsScaleLeft() && CORE2018::GetInstance()->gameDataParser.GetStartingPosition() == LEFT) {
                m_waitingToBringLiftUp->addAction(new WaitAction(2));
            } else {
                m_waitingToBringLiftUp->addAction(new WaitAction(5));
            }
            driveAction = new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.GetCubeToScalePath());
            m_waitingToBringLiftUp->addNext(m_moveToScaleSecondTime);
            m_moveToScaleSecondTime->addNext(m_dropCube);

        }
            break;
        }
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


