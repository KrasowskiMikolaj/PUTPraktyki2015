/**
 * Project Untitled
 */


#ifndef _SIMULATORODE_H
#define _SIMULATORODE_H

#include "simulator.h"
#include "../3rdParty/tinyXML/tinyxml2.h"
#include <ode/ode.h>
#include <iostream>
//#include "../include/Simulator/matrix.h"
//#include "../include/Simulator/vector.h"

namespace simulator {

    /// create a single simulator
    Simulator* createODESimulator(void);
    /// create a single simulator
    Simulator* createODESimulator(std::string configFilename);
};

using namespace simulator;

class SimulatorODE: public Simulator, public Subject {
public:
    /// Pointer
    typedef std::unique_ptr<SimulatorODE> Ptr;
    ///ODE World
    static dWorldID world;
    ///ODE Space
    dSpaceID space;

#define MAX_CONTACTS 1

//    MATRIX GeomMatrix;
#define GEOMSPERBODY 1  // maximum number of geometries per body
struct MyObject
{
    dBodyID Body;  // the dynamics body
    dGeomID Geom[GEOMSPERBODY];  // geometries representing this body
};
    MyObject Object;
    static dJointGroupID contactgroup;


    class Config{
      public:
        Config() {
        }
        Config(std::string configFilename){
            tinyxml2::XMLDocument config;
            std::string filename = "../../resources/" + configFilename;
            config.LoadFile(filename.c_str());
            if (config.ErrorID())
                std::cout << "unable to load Map config file.\n";
            config.FirstChildElement( "Ground" )->FirstChildElement( "parameters" )->QueryDoubleAttribute("friction", &friction);
            std::cout << "Friction: " << friction << "\n";
        }
        public:
            /// friction
            float_type friction;
    };
    /// Construction
    SimulatorODE(void);

    /// Construction
    SimulatorODE(std::string configFilename);

    void startSimulation();

    void stopSimulation();

    ///Attach visualizer
    void attachVisualizer(QGLVisualizer* visualizer);

    /// Destructor
    ~SimulatorODE(void);

    ///ODE Initialization
    void InitODE();

    ///ODE Exit
    void CloseODE();

    ///ODE Loop
    void SimLoop();

    static void nearCallback (void *data, dGeomID o1, dGeomID o2);

    void DrawGeom (dGeomID g, const dReal *pos, const dReal *R, int show_aabb);

     protected:
    Config config;
};


#endif //_SIMULATORODE_H
