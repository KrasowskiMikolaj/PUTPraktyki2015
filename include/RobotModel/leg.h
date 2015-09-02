/**
 * Project Untitled
 */


#ifndef _LEG_H
#define _LEG_H

#include "../../include/Defs/defs.h"
#include <iostream>
#include <string>

using namespace simulator;

class leg {
protected:
    float_type mass;
    Vec3 attach;
    float_type attachRoll;
    float_type attachPitch;
    float_type attachYaw;
    int jointNo;
    int segmentNo;
    std::string name;
};

#endif //_LEG_H
