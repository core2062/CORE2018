#ifndef SRC_AUTONOMOUS_ACTION_ROTATEARMACTION_H_
#define SRC_AUTONOMOUS_ACTION_ROTATEARMACTION_H_
#include <CORERobotLib.h>
#include <ScorerSubsystem.h>

class RotateArmAction : public COREAutonAction{
public:
	RotateArmAction();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
	ScorerSubsystem scorerSubsystem;
};

#endif /* SRC_AUTONOMOUS_ACTION_ROTATEARMACTION_H_ */
