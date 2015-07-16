/**
 * Project Untitled
 */

#include "../Defs/defs.h"
#include "../Visualizer/observer.h"
#include "../include/Visualizer/Qvisualizer.h"

#ifndef _SIMULATOR_H
#define _SIMULATOR_H

using namespace simulator;

namespace simulator {
    /// Controller interface
    class Simulator {
    public:
        /// Sim type
        enum Type {
                /// ODE
                TYPE_ODE,
        };

        /// overloaded constructor
        Simulator(const std::string _name, Type _type) : name(_name), type(_type) {};

        /// Name of the Simulator
        virtual const std::string& getName() const { return name; }

        ///
        void startSimulation();

        ///
        void stopSimulation();

        ///Attach visualizer
        virtual void attachVisualizer(QGLVisualizer* visualizer) = 0;

        ///
        std::vector<Mat34> getRobotState();
    protected:
        /// Controller type
        Type type;

        /// Controller name
        const std::string name;
    };
};

#endif //_SIMULATOR_H
