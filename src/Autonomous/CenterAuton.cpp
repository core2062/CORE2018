#include <CORERobotLib.h>
#include "CenterAuton.h"
#include "Actions.h"
#include "Robot.h"


CenterAuton::CenterAuton() :
	COREAuton("Center Auton") {

}

void CenterAuton::addNodes() {
    m_moveToSwitch = new Node(8, new StateAction(WantedState::WANT_TO_SCORE_ON_SWITCH));
    m_outtakeCubeToSwitch = new Node(5, new ScorerAction(scorerAction::OPEN));
    m_intakeCube = new Node(5, new ScorerAction(scorerAction::CLOSED));
	CORE2018::GetInstance()->driveSubsystem.resetTracker(Position2d(Translation2d(0, 19), Rotation2d::fromRadians(0)));
	switch (CORE2018::GetInstance()->gameDataParser.GetCubePlacement()) {
		case SWITCH1:
            addFirstNode(m_moveToSwitch);
            m_moveToSwitch->addAction(new DriveWaypointAction(
					CORE2018::GetInstance()->gameDataParser.GetWallToSwitchPath()));
			m_moveToSwitch->addNext(m_outtakeCubeToSwitch);
			break;
	}
}
