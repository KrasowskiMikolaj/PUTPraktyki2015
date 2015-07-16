#include "include/Defs/defs.h"
#include "include/Simulator/simulatorODE.h"
#include "3rdParty/tinyXML/tinyxml2.h"
#include <iostream>

int main()
{
    try {
        using namespace simulator;

        tinyxml2::XMLDocument config;
        config.LoadFile("../../resources/simulator.xml");
        if (config.ErrorID())
            std::cout << "unable to load config file.\n";
        std::string simConfig = config.FirstChildElement( "Environment" )->Attribute("config");

        Simulator* sim;
        sim = createODESimulator(simConfig);
        sim->startSimulation();
        std::cout << sim->getName() << "\n";
        sim->stopSimulation();
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
