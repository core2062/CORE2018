#include "SideAuton.h"
#include "Actions.h"
#include <WPILib.h>
#include <CORERobotLib.h>

SideAuton::SideAuton() :
		COREAuton("Side Auton") {
	m_moveToRightSwitch = new Node(5, new DriveDistanceAction());
	m_moveToLeftSwitch = new Node(5, new DriveDistanceAction());
	m_outtakeCubeToSwitch = new Node(5, new ScorerAction(scorerAction::OPEN));
	m_moveToCubeStackFromRight = new Node(5, new DriveDistanceAction());
	m_moveToCubeStackFromLeft = new Node(5, new DriveDistanceAction());
	m_intakeCube = new Node(5, new ScorerAction(scorerAction::CLOSED));
	m_moveToRightScale = new Node(5, new DriveDistanceAction());
	m_moveToLeftScale = new Node(5, new DriveDistanceAction());
	m_liftUpToScale = new Node(5, new LiftAction(liftAction::SCALE));
	m_outtakeCubeToScale = new Node(5, new ScorerAction(scorerAction::OPEN));
	m_driveToCubesFromLeft = new Node(5, new DriveDistanceAction());
	m_driveToCubesFromRight = new Node(5, new DriveDistanceAction());
	m_intakeSecondCube = new Node(5, new ScorerAction(scorerAction::CLOSED));
	m_driveToRightScaleSecondTime = new Node(5, new DriveDistanceAction());
	m_driveToLeftScaleSecondTime = new Node(5, new DriveDistanceAction());
	m_liftUpToScaleSecondTime = new Node(5, new LiftAction(liftAction::SCALE));
	m_outtakeSecondCube = new Node(5, new ScorerAction(scorerAction::OPEN));
	m_cubePlacementChooser = new SendableChooser<cubePlacement>();
	SmartDashboard::PutData(m_cubePlacementChooser);

	m_gameOrientation = gameDataParser.getGameOrientation();
}

void SideAuton::addNodes() {

	switch (m_cubePlacementChooser->GetSelected()) {
	case SWITCH1SCALE1: {
		switch (m_gameOrientation) {
		case RR:
			m_moveToRightSwitch->addNext(m_outtakeCubeToSwitch); //might be reversed
			m_outtakeCubeToSwitch->addNext(m_moveToCubeStackFromRight);
			m_moveToCubeStackFromRight->addNext(m_intakeCube); //might be reversed
			m_intakeCube->addNext(m_moveToRightScale);
			m_moveToRightScale->addNext(m_liftUpToScale); //might be reversed
			m_liftUpToScale->addNext(m_outtakeCubeToScale);
			break;
		case LR:
			m_moveToLeftSwitch->addNext(m_outtakeCubeToSwitch); //might be reversed
			m_outtakeCubeToSwitch->addNext(m_moveToCubeStackFromLeft);
			m_moveToCubeStackFromLeft->addNext(m_intakeCube); //might be reversed
			m_intakeCube->addNext(m_moveToRightScale);
			m_moveToRightScale->addNext(m_liftUpToScale); //might be reversed
			m_liftUpToScale->addNext(m_outtakeCubeToScale);
			break;
		case RL:
			m_moveToRightSwitch->addNext(m_outtakeCubeToSwitch); //might be reversed
			m_outtakeCubeToSwitch->addNext(m_moveToCubeStackFromRight);
			m_moveToCubeStackFromRight->addNext(m_intakeCube); //might be reversed
			m_intakeCube->addNext(m_moveToLeftScale);
			m_moveToLeftScale->addNext(m_liftUpToScale); //might be reversed
			m_liftUpToScale->addNext(m_outtakeCubeToScale);
			break;
		case LL:
			m_moveToLeftSwitch->addNext(m_outtakeCubeToSwitch); //might be reversed
			m_outtakeCubeToSwitch->addNext(m_moveToCubeStackFromLeft);
			m_moveToCubeStackFromLeft->addNext(m_intakeCube); //might be reversed
			m_intakeCube->addNext(m_moveToLeftScale);
			m_moveToLeftScale->addNext(m_liftUpToScale); //might be reversed
			m_liftUpToScale->addNext(m_outtakeCubeToScale);
			break;
		}
		break;
	}
	case SWITCH1SCALE2: {
		switch (m_gameOrientation) {
		case RR:
			m_moveToRightSwitch->addNext(m_outtakeCubeToSwitch); //might be reversed
			m_outtakeCubeToSwitch->addNext(m_moveToCubeStackFromRight);
			m_moveToCubeStackFromRight->addNext(m_intakeCube); //might be reversed
			m_intakeCube->addNext(m_moveToRightScale);
			m_moveToRightScale->addNext(m_liftUpToScale); //might be reversed
			m_liftUpToScale->addNext(m_outtakeCubeToScale);
			m_outtakeCubeToScale->addNext(m_driveToCubesFromRight);
			m_driveToCubesFromRight->addNext(m_intakeSecondCube); //might be reversed
			m_intakeSecondCube->addNext(m_driveToRightScaleSecondTime);
			m_driveToRightScaleSecondTime->addNext(m_outtakeSecondCube); //might be reversed
			m_liftUpToScaleSecondTime->addNext(m_outtakeSecondCube);
			break;
		case LR:
			m_moveToLeftSwitch->addNext(m_outtakeCubeToSwitch); //might be reversed
			m_outtakeCubeToSwitch->addNext(m_moveToCubeStackFromLeft);
			m_moveToCubeStackFromLeft->addNext(m_intakeCube); //might be reversed
			m_intakeCube->addNext(m_moveToRightScale);
			m_moveToRightScale->addNext(m_liftUpToScale); //might be reversed
			m_liftUpToScale->addNext(m_outtakeCubeToScale);
			m_outtakeCubeToScale->addNext(m_driveToCubesFromRight);
			m_driveToCubesFromRight->addNext(m_intakeSecondCube); //might be reversed
			m_intakeSecondCube->addNext(m_driveToRightScaleSecondTime);
			m_driveToRightScaleSecondTime->addNext(m_outtakeSecondCube); //might be reversed
			m_liftUpToScaleSecondTime->addNext(m_outtakeSecondCube);
			break;
		case RL:
			m_moveToRightSwitch->addNext(m_outtakeCubeToSwitch); //might be reversed
			m_outtakeCubeToSwitch->addNext(m_moveToCubeStackFromRight);
			m_moveToCubeStackFromRight->addNext(m_intakeCube); //might be reversed
			m_intakeCube->addNext(m_moveToLeftScale);
			m_moveToLeftScale->addNext(m_liftUpToScale); //might be reversed
			m_liftUpToScale->addNext(m_outtakeCubeToScale);
			m_outtakeCubeToScale->addNext(m_driveToCubesFromLeft);
			m_driveToCubesFromLeft->addNext(m_intakeSecondCube); //might be reversed
			m_intakeSecondCube->addNext(m_driveToLeftScaleSecondTime);
			m_driveToLeftScaleSecondTime->addNext(m_outtakeSecondCube); //might be reversed
			m_liftUpToScaleSecondTime->addNext(m_outtakeSecondCube);
			break;
		case LL:
			m_moveToLeftSwitch->addNext(m_outtakeCubeToSwitch); //might be reversed
			m_outtakeCubeToSwitch->addNext(m_moveToCubeStackFromLeft);
			m_moveToCubeStackFromLeft->addNext(m_intakeCube); //might be reversed
			m_intakeCube->addNext(m_moveToLeftScale);
			m_moveToLeftScale->addNext(m_liftUpToScale); //might be reversed
			m_liftUpToScale->addNext(m_outtakeCubeToScale);
			m_outtakeCubeToScale->addNext(m_driveToCubesFromLeft);
			m_driveToCubesFromLeft->addNext(m_intakeSecondCube); //might be reversed
			m_intakeSecondCube->addNext(m_driveToLeftScaleSecondTime);
			m_driveToLeftScaleSecondTime->addNext(m_liftUpToScaleSecondTime); //might be reversed
			m_liftUpToScaleSecondTime->addNext(m_outtakeSecondCube);
			break;
		}
		break;
	}
	}
}

