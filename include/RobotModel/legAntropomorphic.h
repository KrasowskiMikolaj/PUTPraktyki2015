/**
 * Project Untitled
 */


#ifndef _LEGANTROPOMORPHIC_H
#define _LEGANTROPOMORPHIC_H

#include "../../include/RobotModel/leg.h"
#include "../../3rdParty/tinyXML/tinyxml2.h"
#include <stdio.h>
#include <vector>
#include "../include/Defs/defs.h"

class rigidBody{
public:
    float_type mass;
    Vec3 center;
    Vec3 size;
    float_type centerRoll;
    float_type centerPitch;
    float_type centerYaw;
};

class legAntropomorphic: public leg {
public:
    ///Construction
    legAntropomorphic();

    legAntropomorphic(std::string legFilename){
        load(legFilename);
    }

    void load(std::string legFilename);
    ///Destructor
    ~legAntropomorphic();
    std::vector<rigidBody> segment;
};

#endif //_LEGANTROPOMORPHIC_H
