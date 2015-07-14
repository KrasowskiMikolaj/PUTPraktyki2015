/**
 * Project Untitled
 */


#ifndef _LEG_H
#define _LEG_H

#include "Class2.h"


class leg: public Class2 {
protected: 
    float_type mass;
    Vec3 attach;
    float_type attachRoll;
    float_type attachPitch;
    float_type attachYaw;
    int jointNo;
    int segmentNo;
    string name;
};

#endif //_LEG_H