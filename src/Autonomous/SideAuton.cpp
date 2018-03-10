
#include "SideAuton.h"
#include "Autonomous/Action/ScorerAction.h"
#include "Autonomous/Action/IntakeAction.h"
#include "Action/DriveDistanceAction.h"
#include "Autonomous/Action/ScorerAction.h"

SideAuton::SideAuton() :
	COREAuton("One switch one scale auton") {
	m_moveToSwitch = new Node(5, new DriveDistanceAction());
	m_outtakeCubeToSwitch = new Node(5, new ScorerAction(scorerAction::OPEN));
	m_moveToCubeStack = new Node(5, new DriveDistanceAction());
	m_intakeCube = new Node(5, new IntakeAction());
	m_moveToScale = new Node(5, new DriveDistanceAction());
	m_liftUpToScale = new Node(5, new LiftAction(liftAction::SCALE));
	m_outtakeCubeToScale = new Node(5, new ScorerAction(scorerAction::OPEN));
	m_outtakeCubeToScale = new Node(5, new ScorerAction(scorerAction::OPEN));
	m_intakeSecondCube = new Node(5, new IntakeAction());
	m_driveToScaleSecondTime = new Node(5, new DriveDistanceAction());
}

void SideAuton::addNodes() {
	switch (/*Number of cubes and to where*/) {
	case /*One cube in switch, one cube in scale*/:
		switch(/*Field config*/) {
		case /*Switch is on the right, scale is on the right*/:
			m_moveToSwitch->addNext(m_outtakeCubeToSwitch); //might be reversed
			m_outtakeCubeToSwitch->addNext(m_moveToCubeStack);
			m_moveToCubeStack->addNext(m_intakeCube); //might be reversed
			m_intakeCube->addNext(m_moveToScale);
			m_moveToScale->addNext(m_liftUpToScale); //might be reversed
			m_liftUpToScale->addNext(m_outtakeCubeToScale);
		case /*Switch is on the left, scale is on the right*/:
			m_moveToSwitch->addNext(m_outtakeCubeToSwitch); //might be reversed
			m_outtakeCubeToSwitch->addNext(m_moveToCubeStack);
			m_moveToCubeStack->addNext(m_intakeCube); //might be reversed
			m_intakeCube->addNext(m_moveToScale);
			m_moveToScale->addNext(m_liftUpToScale); //might be reversed
			m_liftUpToScale->addNext(m_outtakeCubeToScale);
		case /*Switch is on the right, scale is on the left*/:
			m_outtakeCubeToSwitch->addNext(m_moveToCubeStack);
			m_moveToCubeStack->addNext(m_intakeCube); //might be reversed
			m_intakeCube->addNext(m_moveToScale);
			m_moveToScale->addNext(m_liftUpToScale); //might be reversed
			m_liftUpToScale->addNext(m_outtakeCubeToScale);
		case /*Switch is on the left, scale is on the left*/:
			m_outtakeCubeToSwitch->addNext(m_moveToCubeStack);
			m_moveToCubeStack->addNext(m_intakeCube); //might be reversed
			m_intakeCube->addNext(m_moveToScale);
			m_moveToScale->addNext(m_liftUpToScale); //might be reversed
			m_liftUpToScale->addNext(m_outtakeCubeToScale);
		}
	case /*One cube in switch, two cubes in scale*/)
		switch(/*Field config*/) {
		case /*Switch is on the right, scale is on the right*/ :
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
		case /*Switch is on the left, scale is on the right*/ :
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
		case /*Switch is on the right, scale is on the left*/ :
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
		case /*Switch is on the left, scale is on the left*/ :
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

		}
	}
}
