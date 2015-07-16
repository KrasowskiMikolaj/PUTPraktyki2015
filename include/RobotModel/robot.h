/**
 * Project Untitled
 */

#include "../include/Defs/defs.h"
#include <iostream>

#ifndef _ROBOT_H
#define _ROBOT_H

namespace simulator {
    class Robot {
    public:
        /// Robot model type
        enum Type {
                /// 4 legged
                TYPE_4LEGGED,
        };

        /// overloaded constructor
        Robot(const std::string _name, Type _type) : name(_name), type(_type) {};

        /// Name of the Controller
        virtual const std::string& getName() const { return name; }


    protected:
        /// Controller type
        Type type;

        /// Controller name
        const std::string name;

        /// Total mass of the robot
        float_type mass;
        ///
        Vec3 initPosition;
        ///
        float_type initRoll;
        float_type initPitch;
        float_type initYaw;
        int legNo;
    };
};

#endif //_ROBOT_H
