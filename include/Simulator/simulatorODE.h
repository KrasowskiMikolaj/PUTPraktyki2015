/**
 * Project Untitled
 */


#ifndef _SIMULATORODE_H
#define _SIMULATORODE_H

#include "simulator.h"
#include "../3rdParty/tinyXML/tinyxml2.h"
#include <ode/ode.h>
#include <iostream>

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

    ///Attach visualizer
    void attachVisualizer(QGLVisualizer* visualizer);

    /// Destructor
    ~SimulatorODE(void);
 protected:
    Config config;
};

#endif //_SIMULATORODE_H
