#include <CORERobotlib.h>
#include <WPILib.h>

#include "COREUtilities/COREConstant.h"
class ChainbarSubsystem : public CORESubsystem {
public:
	ChainbarSubsystem();
	void robotInit();
	void teleopInit();
	void teleop();
};
