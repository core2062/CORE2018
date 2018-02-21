#ifndef SRC_AUTONOMUS_ACTION_LIFTUPTOSCALE_H_
#define SRC_AUTONOMUS_ACTION_LIFTUPTOSCALE_H_
#include <CORERobotlib.h>

class LiftUpToScale {
public:
	LiftUpToScale();
	void actionInit();
	void action();
	void actionEnd();
};

#endif
