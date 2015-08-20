#include "../include/Defs/defs.h"
#include "../3rdParty/tinyXML/tinyxml2.h"
#include "../include/Visualizer/Qvisualizer.h"
#include "../include/Simulator/simulatorODE.h"
#include <GL/glut.h>
#include <qapplication.h>
#include <iostream>
#include <thread>

using namespace std;

Simulator* sim;

// run PUTSLAM
void runPUTSLAM(){
    //std::cout << "Press Enter to start\n";
    //getchar();
    sim->startSimulation();
    std::cout << sim->getName() << "\n";
    sim->stopSimulation();
}

int main(int argc, char** argv)
{
    try {
        tinyxml2::XMLDocument config;
        config.LoadFile("../../resources/simulator.xml");
        if (config.ErrorID())
            std::cout << "unable to load config file.\n";
        std::string configFile(config.FirstChildElement( "Visualizer" )->FirstChildElement( "parametersFile" )->GetText());

        QGLVisualizer::Config configVis(configFile);//something is wrong with QApplication when Qapplication
        //object is created. libTinyxml can read only ints from xml file

        sim = simulator::createODESimulator();

        QApplication application(argc,argv);

        glutInit(&argc, argv);

        QGLVisualizer visu(configVis);

        visu.setWindowTitle("Simulator viewer");
std::cout << "df\n";
        // Make the viewer window visible on screen.
        visu.show();
        sim->attachVisualizer(&visu);
std::cout << "df1\n";
        // run PUTSLAM
        std::thread tSLAM(runPUTSLAM);
std::cout << "df2\n";
        // Run main loop.
        application.exec();
        tSLAM.join();

        return 1;
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
