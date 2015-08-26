/**
 * Project Untitled
 */


#include "../../include/Simulator/simulatorODE.h"

/**
 * simulatorODE implementation
 */
dJointGroupID SimulatorODE::contactgroup;
dWorldID SimulatorODE::world;



using namespace simulator;

/// A single instance of SimulatorODE
SimulatorODE::Ptr simulatorODE;

SimulatorODE::SimulatorODE(void) : Simulator("ODE simulator", TYPE_ODE) {

}

/// Construction
SimulatorODE::SimulatorODE(std::string configFilename) : config(configFilename), Simulator("ODE simulator", TYPE_ODE){
}

SimulatorODE::~SimulatorODE(void) {

}

///Attach visualizer
void SimulatorODE::attachVisualizer(QGLVisualizer* visualizer){
    attach(visualizer);
}

simulator::Simulator* simulator::createODESimulator(void) {
    simulatorODE.reset(new SimulatorODE());
    return simulatorODE.get();
}

simulator::Simulator* simulator::createODESimulator(std::string configFilename) {
    simulatorODE.reset(new SimulatorODE(configFilename));
    return simulatorODE.get();
}

void SimulatorODE::startSimulation(){
    InitODE();
    std::cout <<"end ode\n";
    while(1)
        SimLoop();
}

void SimulatorODE::stopSimulation(){
    CloseODE();
}

void SimulatorODE::InitODE(){
    world=dWorldCreate();
    space=dSimpleSpaceCreate(0);
    contactgroup = dJointGroupCreate(0);
    dCreatePlane(space,0,0,1,0);
    dWorldSetGravity(world, 0,0,-9.81);
    dWorldSetERP(world, 0.2);
    dWorldSetCFM(world, 1e-5);
    dWorldSetContactMaxCorrectingVel(world, 0.9);
    dWorldSetContactSurfaceLayer(world, 0.001);
    dWorldSetAutoDisableFlag(world, 1);
    dInitODE();
    dReal R[9];
    dMass m;
    double mass = 24;
    Object.Body = dBodyCreate(world);
    double sides[3];
std::cout << "ds4\n";
        // Set up for static object - rama glowna
        sides[0] = 0.03;
        sides[1] = 0.03;
        sides[2] = 0.03;
        dReal pos[3];
        pos[0]=0;
        pos[1]=0;
        pos[2]=10;
        dBodySetPosition(Object.Body, pos[0],pos[1],pos[2]);
        dBodySetLinearVel(Object.Body, 0, 0, 0);
        dRFromAxisAndAngle(R, 1, 0, 0, 0);
        dBodySetRotation(Object.Body, R);
         //ustawia gestosc dla masy dMassSetBoxTotal
        dMassSetParameters(&m,mass,0,0,0,1,1,1,0,0,0);
        Object.Geom[0] = dCreateBox(space, sides[0], sides[1], sides[2]);
        dGeomSetBody(Object.Geom[0], Object.Body);
        dBodySetMass(Object.Body, &m);
        std::cout << "ds3\n";
}


void SimulatorODE::CloseODE(){
    dJointGroupDestroy(contactgroup);
    dSpaceDestroy(space);
    dWorldDestroy(world);
}

void SimulatorODE::nearCallback (void *data, dGeomID o1, dGeomID o2)
{
    int i;
    dBodyID b1 = dGeomGetBody(o1);
    dBodyID b2 = dGeomGetBody(o2);
    dContact contact[MAX_CONTACTS];
    for (i = 0; i < MAX_CONTACTS; i++)
    {
        contact[i].surface.mode = dContactBounce | dContactSoftCFM;
        contact[i].surface.mu = dInfinity;
        contact[i].surface.mu2 = 0;
        contact[i].surface.bounce = 0.01;
        contact[i].surface.bounce_vel = 0.1;
        contact[i].surface.soft_cfm = 0.01;
    }
    if (int numc = dCollide(o1, o2, MAX_CONTACTS, &contact[0].geom, sizeof(dContact)))
    {
        for (i = 0; i < numc; i++)
        {
            dJointID c = dJointCreateContact(SimulatorODE::world, SimulatorODE::contactgroup, contact + i);
            dJointAttach(c, b1, b2);
        }
    }
}


void SimulatorODE::SimLoop()
{
    std::cout << "ds1\n";
    dSpaceCollide(space, 0, &nearCallback);
    dWorldQuickStep(world, 0.0001);
    dJointGroupEmpty(contactgroup);
    const dReal *pos;
    std::cout << "ds\n";
    pos = dGeomGetPosition (Object.Geom[0]);
    std::cout << "pos: x: " << pos[0] << ",y: " << pos[1] << ",z: " << pos[2] << "\n";
    getchar();
    //this->notify(
//  DrawGeom(Object.Geom[0], 0, 0, 0);
}
