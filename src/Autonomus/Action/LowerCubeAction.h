#ifndef SRC_AUTONOMUS_ACTION_LOWERCUBEACTION_H_
#define SRC_AUTONOMUS_ACTION_LOWERCUBEACTION_H_
#include <CORERobotlib.h>

class LowerCubeAction: public COREAutonAction {
public:
	LowerCubeAction();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
};

