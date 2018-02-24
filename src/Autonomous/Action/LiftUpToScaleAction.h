#include <CORERobotLib.h>

#include "WPILib.h"
#include "Robot.h"

class LiftUpToScale: public COREAutonAction {
public:
	LiftUpToScale();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
	double m_scaleHeight;
	CORE2018 Robot;
};
