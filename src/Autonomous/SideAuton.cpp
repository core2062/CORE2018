#include "SideAuton.h"
#include "Actions.h"
#include <WPILib.h>
#include <CORERobotLib.h>

SideAuton::SideAuton() :
		COREAuton("Side Auton") {
	m_moveToSwitch = new Node(5, new DriveDistanceAction());
	m_outtakeCubeToSwitch = new Node(5, new ScorerAction(scorerAction::OPEN));
	m_moveToCubeStack = new Node(5, new DriveDistanceAction());
	m_intakeCube = new Node(5, new ScorerAction(scorerAction::CLOSED));
	m_moveToScale = new Node(5, new DriveDistanceAction());
	m_liftUpToScale = new Node(5, new LiftAction(liftAction::SCALE));
	m_outtakeCubeToScale = new Node(5, new ScorerAction(scorerAction::OPEN));
	m_driveToCubes = new Node(5, new DriveDistanceAction());
	m_intakeSecondCube = new Node(5, new ScorerAction(scorerAction::CLOSED));
	m_driveToScaleSecondTime = new Node(5, new DriveDistanceAction());
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
			m_moveToSwitch->addNext(m_outtakeCubeToSwitch); //might be reversed
			m_outtakeCubeToSwitch->addNext(m_moveToCubeStack);
			m_moveToCubeStack->addNext(m_intakeCube); //might be reversed
			m_intakeCube->addNext(m_moveToScale);
			m_moveToScale->addNext(m_liftUpToScale); //might be reversed
			m_liftUpToScale->addNext(m_outtakeCubeToScale);
			break;
		case LR:
			m_moveToSwitch->addNext(m_outtakeCubeToSwitch); //might be reversed
			m_outtakeCubeToSwitch->addNext(m_moveToCubeStack);
			m_moveToCubeStack->addNext(m_intakeCube); //might be reversed
			m_intakeCube->addNext(m_moveToScale);
			m_moveToScale->addNext(m_liftUpToScale); //might be reversed
			m_liftUpToScale->addNext(m_outtakeCubeToScale);
			break;
		case RL:
			m_moveToSwitch->addNext(m_outtakeCubeToSwitch); //might be reversed
			m_outtakeCubeToSwitch->addNext(m_moveToCubeStack);
			m_moveToCubeStack->addNext(m_intakeCube); //might be reversed
			m_intakeCube->addNext(m_moveToScale);
			m_moveToScale->addNext(m_liftUpToScale); //might be reversed
			m_liftUpToScale->addNext(m_outtakeCubeToScale);
			break;
		case LL:
			m_moveToSwitch->addNext(m_outtakeCubeToSwitch); //might be reversed
			m_outtakeCubeToSwitch->addNext(m_moveToCubeStack);
			m_moveToCubeStack->addNext(m_intakeCube); //might be reversed
			m_intakeCube->addNext(m_moveToScale);
			m_moveToScale->addNext(m_liftUpToScale); //might be reversed
			m_liftUpToScale->addNext(m_outtakeCubeToScale);
			break;
		}
		break;
	}
	case SWITCH1SCALE2: {
		switch (m_gameOrientation) {
		case RR:
			m_moveToSwitch->addNext(m_outtakeCubeToSwitch); //might be reversed
			m_outtakeCubeToSwitch->addNext(m_moveToCubeStack);
			m_moveToCubeStack->addNext(m_intakeCube); //might be reversed
			m_intakeCube->addNext(m_moveToScale);
			m_moveToScale->addNext(m_liftUpToScale); //might be reversed
			m_liftUpToScale->addNext(m_outtakeCubeToScale);
			m_outtakeCubeToScale->addNext(m_driveToCubes);
			m_driveToCubes->addNext(m_intakeSecondCube); //might be reversed
			m_intakeSecondCube->addNext(m_driveToScaleSecondTime);
			m_driveToScaleSecondTime->addNext(m_outtakeSecondCube); //might be reversed
			m_liftUpToScaleSecondTime->addNext(m_outtakeSecondCube);
			break;
		case LR:
			m_moveToSwitch->addNext(m_outtakeCubeToSwitch); //might be reversed
			m_outtakeCubeToSwitch->addNext(m_moveToCubeStack);
			m_moveToCubeStack->addNext(m_intakeCube); //might be reversed
			m_intakeCube->addNext(m_moveToScale);
			m_moveToScale->addNext(m_liftUpToScale); //might be reversed
			m_liftUpToScale->addNext(m_outtakeCubeToScale);
			m_outtakeCubeToScale->addNext(m_driveToCubes);
			m_driveToCubes->addNext(m_intakeSecondCube); //might be reversed
			m_intakeSecondCube->addNext(m_driveToScaleSecondTime);
			m_driveToScaleSecondTime->addNext(m_outtakeSecondCube); //might be reversed
			m_liftUpToScaleSecondTime->addNext(m_outtakeSecondCube);
			break;
		case RL:
			m_moveToSwitch->addNext(m_outtakeCubeToSwitch); //might be reversed
			m_outtakeCubeToSwitch->addNext(m_moveToCubeStack);
			m_moveToCubeStack->addNext(m_intakeCube); //might be reversed
			m_intakeCube->addNext(m_moveToScale);
			m_moveToScale->addNext(m_liftUpToScale); //might be reversed
			m_liftUpToScale->addNext(m_outtakeCubeToScale);
			m_outtakeCubeToScale->addNext(m_driveToCubes);
			m_driveToCubes->addNext(m_intakeSecondCube); //might be reversed
			m_intakeSecondCube->addNext(m_driveToScaleSecondTime);
			m_driveToScaleSecondTime->addNext(m_outtakeSecondCube); //might be reversed
			m_liftUpToScaleSecondTime->addNext(m_outtakeSecondCube);
			break;
		case LL:
			m_moveToSwitch->addNext(m_outtakeCubeToSwitch); //might be reversed
			m_outtakeCubeToSwitch->addNext(m_moveToCubeStack);
			m_moveToCubeStack->addNext(m_intakeCube); //might be reversed
			m_intakeCube->addNext(m_moveToScale);
			m_moveToScale->addNext(m_liftUpToScale); //might be reversed
			m_liftUpToScale->addNext(m_outtakeCubeToScale);
			m_outtakeCubeToScale->addNext(m_driveToCubes);
			m_driveToCubes->addNext(m_intakeSecondCube); //might be reversed
			m_intakeSecondCube->addNext(m_driveToScaleSecondTime);
			m_driveToScaleSecondTime->addNext(m_liftUpToScaleSecondTime); //might be reversed
			m_liftUpToScaleSecondTime->addNext(m_outtakeSecondCube);
			break;
		}
		break;
	}
	}
}

