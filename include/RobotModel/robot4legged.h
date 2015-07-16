/**
 * Project Untitled
 */


#ifndef _ROBOT4LEGGED_H
#define _ROBOT4LEGGED_H

#include "robot.h"


namespace simulator {

    /// create a single 4 legged robot
    Robot* create4LeggedRobot(void);
};

using namespace simulator;

/**
 * \brief Robot implementation.
 */
class Robot4Legged : public Robot{
    public:
        /// Pointer
        typedef std::unique_ptr<Robot4Legged> Ptr;

        /// Construction
        Robot4Legged(void);

        /// Destructor
        ~Robot4Legged(void);
     protected:

};

#endif //_ROBOT4LEGGED_H
