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
    dWorldSetContactMaxCorrectingVel(world, 2.9);
    dWorldSetContactSurfaceLayer(world, 0.0);
    dWorldSetAutoDisableFlag(world, 0);
    dInitODE();
    dMatrix3 R;
    dMass m;
    double mass = 1;
    Object.Body = dBodyCreate(world);
    double sides[3];
        // Set up for static object - rama glowna
        sides[0] = 0.1;
        sides[1] = 0.1;
        sides[2] = 0.1;
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
        contact[i].surface.mu = 0.5;
        contact[i].surface.mu2 = 0.5;
        contact[i].surface.bounce = 0.15;    // changed
        contact[i].surface.bounce_vel = 0.5;     // changed
        contact[i].surface.soft_cfm = 0.107;
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
    dSpaceCollide(space, 0, &nearCallback);
    dWorldQuickStep(world, 0.000001);
    dJointGroupEmpty(contactgroup);
    const dReal *pos;
    pos = dGeomGetPosition (Object.Geom[0]);
    std::vector<Mat34> objects;
    Mat34 box1(Vec3(pos[0],pos[1],pos[2])*Quaternion(1,0,0,0));
    objects.push_back(box1);
    this->notify(objects);
    //this->notify(
//  DrawGeom(Object.Geom[0], 0, 0, 0);
}
