#include <Robot.h>
#include "ctre/Phoenix.h"
#include "CORELogging/COREDataLog.h"

CORE2018::CORE2018() {
    std::cout << "CORE2018" << std::endl;
    CORELog::logInfo("Testing");

}

void CORE2018::robotInit() {
    CORELog::logInfo("Robot init");
}

void CORE2018::teleopInit() {

}

void CORE2018::teleop() {

}


START_ROBOT_CLASS(CORE2018)
