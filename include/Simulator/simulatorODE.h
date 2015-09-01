/**
 * Project Untitled
 */


#ifndef _SIMULATORODE_H
#define _SIMULATORODE_H

#include "simulator.h"
#include "../3rdParty/tinyXML/tinyxml2.h"
#include <ode/ode.h>
#include <iostream>
#include "../include/Visualizer/observer.h"

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

#define MAX_CONTACTS 1024

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
        Config(std::string configFilename) {
            load(configFilename);
        }
        void load(std::string configFilename){
            tinyxml2::XMLDocument config;
            std::string filename = "../../resources/" + configFilename;
            config.LoadFile(filename.c_str());
            if (config.ErrorID())
                std::cout << "unable to load Map config file.\n";
            config.FirstChildElement( "Ground" )->FirstChildElement( "parameters" )->QueryDoubleAttribute("friction", &friction);
            config.FirstChildElement( "Ground" )->FirstChildElement( "parameters" )->QueryDoubleAttribute("bounce", &bounce);
            config.FirstChildElement( "Ground" )->FirstChildElement( "parameters" )->QueryDoubleAttribute("bounce_vel", &bounce_vel);
            config.FirstChildElement( "Ground" )->FirstChildElement( "parameters" )->QueryDoubleAttribute("soft_cfm", &soft_cfm);
            std::cout << "ODE parameters:\n";
            std::cout << "Friction: " << friction << "\n";
            std::cout << "Bounce: " << bounce << "\n";
            std::cout << "Bounce_vel: " << bounce_vel << "\n";
            std::cout << "soft_cfm: " << soft_cfm << "\n";
        }

        public:
            /// friction
            float_type friction;
            float_type bounce;
            float_type bounce_vel;
            float_type soft_cfm;
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

     protected:
    static Config config;

    std::string configFilename;
};


#endif //_SIMULATORODE_H
