#include <CORERobotLib.h>

#include "WPILib.h"
#include "Robot.h"

class LiftUpToScaleAction: public COREAutonAction {
public:
	LiftUpToScaleAction();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
	double m_scaleHeight;
	CORE2018 Robot;
};
