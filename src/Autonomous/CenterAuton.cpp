#include <CORERobotLib.h>
#include "CenterAuton.h"
#include "Actions.h"
#include "Robot.h"


CenterAuton::CenterAuton() :
	COREAuton("Center Auton") {
    m_moveToSwitch = new Node(5, new LiftAction(liftAction::SWITCH));
    m_outtakeCubeToSwitch = new Node(5, new ScorerAction(scorerAction::OPEN));
    m_intakeCube = new Node(5, new ScorerAction(scorerAction::CLOSED));

}

void CenterAuton::addNodes() {
	CORE2018::GetInstance()->driveSubsystem.resetTracker(Position2d(Translation2d(0, 19), Rotation2d::fromRadians(0)));
	switch (CORE2018::GetInstance()->gameDataParser.getCubePlacement()) {
		case SWITCH1:
            addFirstNode(m_intakeCube);
            m_intakeCube->addNext(m_moveToSwitch);
            m_moveToSwitch->addAction(new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.getWallToSwitchPath()));
			m_moveToSwitch->addNext(m_outtakeCubeToSwitch);
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
