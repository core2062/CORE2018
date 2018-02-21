#ifndef SRC_AUTONOMUS_ACTION_DROPCUBE_H_
#define SRC_AUTONOMUS_ACTION_DROPCUBE_H_
#include <CORERobotLib.h>


class DropCube : public COREAutonAction{
public:
	DropCube();
	void actionInit();
	void action();
	void actionEnd();
};

#endif
