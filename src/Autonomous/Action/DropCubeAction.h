#include <CORERobotLib.h>
#include <ScorerSubsystem.h>
#include <Robot.h>


class DropCube : public COREAutonAction{
public:
	DropCube();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
	CORE2018 Robot;
};

