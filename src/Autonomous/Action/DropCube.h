#ifndef SRC_AUTONOMOUS_ACTION_DROPCUBE_H_
#define SRC_AUTONOMOUS_ACTION_DROPCUBE_H_
#include <CORERobotLib.h>
#include <COREAuton.h>
#include <ScorerSubsystem.h>


class DropCube : public COREAutonAction{
public:
	DropCube();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
	ScorerSubsystem scorerSubsystem;
};

#endif
