#ifndef SRC_AUTONOMUS_ACTION_DROPCUBE_H_
#define SRC_AUTONOMUS_ACTION_DROPCUBE_H_
#include <CORERobotLib.h>
#include <COREAuton.h>


class DropCube : public COREAutonAction{
public:
	DropCube();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
};

#endif
