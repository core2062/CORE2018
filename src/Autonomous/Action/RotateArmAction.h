#pragma once

#include <CORERobotLib.h>
#include <ScorerSubsystem.h>

enum rotateArmAction {

	UP,
	MIDDLE,
	DOWN

};

class RotateArmAction : public COREAutonAction {
public:
	RotateArmAction();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
	ScorerSubsystem scorerSubsystem;



private:

	rotateArmAction m_requestedArmAction;
};
