/** @file QVisualizer.h
 *
 * implementation - QGLVisualizer
 *
 */

#ifndef QVISUALIZER_H_INCLUDED
#define QVISUALIZER_H_INCLUDED

#include "../Defs/defs.h"
#include "observer.h"
#include "../3rdParty/tinyXML/tinyxml2.h"
#include <QGLViewer/qglviewer.h>
#include <iostream>
#include "../include/Visualizer/matrix.h"
#include "../include/Visualizer/polygon.h"
#include <thread>
#include <mutex>

using namespace simulator;

/// Map implementation
class QGLVisualizer: public QGLViewer, public Observer{
public:
    /// Pointer
    typedef std::unique_ptr<QGLVisualizer> Ptr;

    class Config{
      public:
        Config() {
        }
        Config(std::string configFilename){
            tinyxml2::XMLDocument config;
            std::string filename = "../../resources/" + configFilename;
            config.LoadFile(filename.c_str());
            if (config.ErrorID())
                std::cout << "unable to load Visualizer config file.\n";
            tinyxml2::XMLElement * model = config.FirstChildElement( "VisualizerConfig" );
        }
        public:
    };

    /// Construction
    QGLVisualizer(void);

    /// Construction
    QGLVisualizer(std::string configFile);

    /// Construction
    QGLVisualizer(Config _config);

    /// Destruction
    ~QGLVisualizer(void);

    /// Observer update
    void update(std::vector<simulator::Mat34>& envState);

    void DrawBox(GLfloat sizeX, GLfloat sizeY,GLfloat sizeZ,GLfloat x, GLfloat y,GLfloat z);


private:
    Config config;

    ///objects 2 draw
    std::vector<Mat34> objects;

    ///mutex
    std::mutex mtxObjects;

    /// draw objects
    void draw();

    /// draw objects
    void animate();

    /// initialize visualizer
    void init();

    /// generate help string
    std::string help() const;
};

#endif // QVISUALIZER_H_INCLUDED
