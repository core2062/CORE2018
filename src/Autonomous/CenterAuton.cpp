#include <CORERobotLib.h>
#include "CenterAuton.h"
#include "Actions.h"
#include "Robot.h"


CenterAuton::CenterAuton() :
	COREAuton("Center Auton") {
	m_outtakeCubeToExchange = new Node(5, new ScorerAction(scorerAction::OPEN));
	m_moveToCubeStack = new Node(5, new DriveDistanceAction());
	m_intakeCube = new Node(5, new IntakeAction());
	m_moveToExchange = new Node(5, new DriveDistanceAction());
	m_outtakeCubeSecondTime = new Node(5, new ScorerAction(scorerAction::OPEN));
	m_moveToCubeStackSecondTime = new Node(5, new DriveDistanceAction());
	m_intakeSecondCube = new Node(5, new IntakeAction());
	m_moveToExchangeSecondTime = new Node(5, new DriveDistanceAction());
	m_outtakeCubeThirdTime  = new Node(5, new ScorerAction(scorerAction::OPEN));

}

void CenterAuton::addNodes() {
	CORE2018::GetInstance()->driveSubsystem.resetTracker(Position2d(Translation2d(0, 19), Rotation2d::fromRadians(PI / 2)));
	switch (CORE2018::GetInstance()->gameDataParser.getCubePlacement()) {
		case SWITCH1:
			m_moveToSwitch->addAction(new DriveWaypointAction(CORE2018::GetInstance()->gameDataParser.getWallToSwitchPath()));
			addFirstNode(m_moveToSwitch);
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
