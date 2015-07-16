/**
 * Project Untitled
 */


#include "../../include/RobotModel/robot4legged.h"
#include <iostream>

/**
 * robot4legged implementation
 */


using namespace simulator;

/// A single instance of Robot4Legged
Robot4Legged::Ptr robot4Legged;

Robot4Legged::Robot4Legged(void) : Robot("4 legged robot", TYPE_4LEGGED) {

}

Robot4Legged::~Robot4Legged(void) {

}


simulator::Robot* simulator::create4LeggedRobot(void) {
    robot4Legged.reset(new Robot4Legged());
    return robot4Legged.get();
}
