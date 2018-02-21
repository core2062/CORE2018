#ifndef SRC_AUTONOMUS_ACTION_INTAKECUBEACTION_H_
#define SRC_AUTONOMUS_ACTION_INTAKECUBEACTION_H_
#include <CORERobotlib.h>

class IntakeCubeAction : public COREAutonAction {
public:
	IntakeCubeAction();
	void actionInit();
	actionStatus action();
	void actionEnd();
};

#endif
