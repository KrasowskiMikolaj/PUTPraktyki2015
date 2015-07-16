
#include "../include/Controller/controllerSim.h"
#include <iostream>

using namespace simulator;

/// A single instance of ControllerSim
ControllerSim::Ptr controllerSim;

ControllerSim::ControllerSim(void) : Controller("Controller Simulator", TYPE_SIM_ODE) {

}

ControllerSim::~ControllerSim(void) {

}


/// Set reference position value for servomotor, returns error value
unsigned int ControllerSim::setPosition(unsigned char legNo, unsigned char jointNo, float_type angle){
    return 0;
}

/// Set reference position value for servomotors, returns error value
unsigned int ControllerSim::setPosition(unsigned char legNo, const std::vector<float_type>& angle){

    return 0;
}

/// Set reference position value for servomotors, returns error value
unsigned int ControllerSim::setPosition(const std::vector<float_type>& angle){
    return 0;
}

/// Set reference speed value for servomotor, returns error value
unsigned int ControllerSim::setSpeed(unsigned char legNo, unsigned char jointNo, float_type speed){
    return 0;
}

/// Set reference speed value for servomotors, returns error value
unsigned int ControllerSim::setSpeed(unsigned char legNo, const std::vector<float_type>& speed){
    return 0;
}

/// Set reference speed value for servomotors, returns error value
unsigned int ControllerSim::setSpeed(const std::vector<float_type>& speed){
    return 0;
}

/// Set compliance margin [0,254]- dead zone -- for this area the torque is zero, returns error value
unsigned int ControllerSim::setComplianceMargin(unsigned char legNo, unsigned char jointNo, float_type margin){
    return 0;
}

/// Set compliance margins [0,254]- dead zone -- for this area the torque is zero, returns error value
unsigned int ControllerSim::setComplianceMargin(unsigned char legNo, const std::vector<float_type> margin){
    return 0;
}

/// Set compliance margins [0,254]- dead zone -- for this area the torque is zero, returns error value
unsigned int ControllerSim::setComplianceMargin(const std::vector<float_type> margin){

    return 0;
}

/// Set compiance slope [1,254] - the area with the reduced torque, returns error value
unsigned int ControllerSim::setComplianceSlope(unsigned char legNo, unsigned char jointNo, float_type slope){
    return 0;
}

/// Set compiance slope [1,254] - the area with the reduced torque, returns error value
unsigned int ControllerSim::setComplianceSlope(unsigned char legNo, const std::vector<float_type>& slope){
    return 0;
}

/// Set compiance slope [1,254] - the area with the reduced torque, returns error value
unsigned int ControllerSim::setComplianceSlope(const std::vector<float_type>& slope){
    return 0;
}

/// Set torque limit torque_limit [0,1] - the torque limit, returns error value
unsigned int ControllerSim::setTorqueLimit(unsigned char legNo, unsigned char jointNo, float_type torqueLimit){
    return 0;
}

/// Set torque limit torque_limit [0,1] - the torque limit, returns error value
unsigned int ControllerSim::setTorqueLimit(unsigned char legNo, const std::vector<float_type>& torqueLimit){
    return 0;
}

/// Set torque limit torque_limit [0,1] - the torque limit, returns error value
unsigned int ControllerSim::setTorqueLimit(const std::vector<float_type>& torqueLimit){
    return 0;
}

/// Returns current position of the servomotor, returns error value
unsigned int ControllerSim::readPosition(unsigned char legNo, unsigned char jointNo, float_type& angle){
    return 0;
}

/// Returns current position of the servomotors, returns error value
unsigned int ControllerSim::readPositions(unsigned char legNo, std::vector<float_type>& angle){
    return 0;
}

/// Returns current position of the servomotor, returns error value
unsigned int ControllerSim::readPosition(std::vector<float_type>& angle){
    return 0;
}

/// Returns contact force from 1-axis force sensor
unsigned int ControllerSim::readForce(unsigned char legNo, float_type& contactForce){
    return 0;
}

/// Returns contact force from 1-axis force sensor
unsigned int ControllerSim::readForce(const std::vector<float_type>& contactForce){
    return 0;
}

/// Returns contact force from 3-axis torque/force sensor
unsigned int ControllerSim::readTorqueForce(unsigned char legNo, TorqueForce& valueTF){
    return 0;
}

/// Returns contact force from 3-axis torque/force sensor
unsigned int ControllerSim::readTorqueForce(const std::vector<float_type>& valueTF){
    return 0;
}

/// Returns contact or from microswitch
bool ControllerSim::readContact(unsigned char legNo){
    return false;
}

/// Returns contact or from microswitches
void ControllerSim::readContact(const std::vector<bool> contact){

}

/// Returns current from servo
unsigned int ControllerSim::readCurrent(unsigned char legNo, unsigned char jointNo, float_type& servoCurrent){
    return 0;
}

/// Returns current from servo
unsigned int ControllerSim::readCurrent(unsigned char legNo, std::vector<float_type>& servoCurrent){
    return 0;
}

/// Returns current from servo
unsigned int ControllerSim::readCurrent( std::vector<float_type>& servoCurrent){
    return 0;
}

/// Returns torque/load from servo
unsigned int ControllerSim::readTorque(unsigned char legNo, unsigned char jointNo, float_type& servoTorque){
     return 0;
}

/// Returns torque/load from servo
unsigned int ControllerSim::readTorque(unsigned char legNo,std::vector<float_type>& servoTorque){
    return 0;
}

/// Returns torque/load from servo
unsigned int ControllerSim::readTorque(std::vector<float_type>& servoTorque){
    return 0;
}

/// Set servo Offset
void ControllerSim::setOffset(unsigned char legNo, unsigned char jointNo, float_type offset){

}

/// Set servo Offset
void ControllerSim::setOffset(unsigned char legNo, const std::vector<float_type> offset){

}

/// Set servo Offset
void ControllerSim::setOffset(const std::vector<float_type> offset){
}

/// Controller configuration -- set default value
void ControllerSim::setDefault(void){ }

simulator::Controller* simulator::createControllerSim(void) {
    controllerSim.reset(new ControllerSim());
    return controllerSim.get();
}
