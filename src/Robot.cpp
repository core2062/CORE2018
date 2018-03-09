#include <Robot.h>
#include "ctre/Phoenix.h"
#include "CORELogging/COREDataLog.h"
#include <CORERobotLib.h>

CORE2018* CORE2018::m_instance;

CORE2018::CORE2018() {
    m_instance = this;
}

void CORE2018::robotInit() {

}

void CORE2018::teleopInit() {

}

void CORE2018::teleop() {
    scorerSubsystem.teleop();
}

void CORE2018::testInit() {
	CORELog::logInfo("test init");
}

void CORE2018::test() {
	CORELog::logInfo("test");
}
CORE2018* CORE2018::GetInstance() {
	if(!m_instance) {
		CORELog::logError("Get instance returning null pointer!");
	}
	return m_instance;
}


START_ROBOT_CLASS(CORE2018)
