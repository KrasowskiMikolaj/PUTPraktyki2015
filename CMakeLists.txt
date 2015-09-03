# cmake requirements
cmake_minimum_required(VERSION 2.8)

# Build options have to be before PROJECT(...)
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE PATH "Configuration types")
SET(CMAKE_BUILD_TYPE "Release" CACHE PATH "Current build configuration")

# Example Project configuration
PROJECT(SIMULATOR)
SET(CMAKE_CXX_FLAGS "-std=c++11 -pthread")

# Folders
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# Settings
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/include")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/include/Defs")

# core libraries
option(BUILD_SIMULATOR "Build SIMULATOR libraries" YES)
option(BUILD_SIMULATOR_DEFS "Build SIMULATOR Defs library" YES)
mark_as_advanced(BUILD_SIMULATOR_DEFS)
option(BUILD_SIMULATOR_CONTROLLER "Build SIMULATOR controller library" ON)
mark_as_advanced(BUILD_SIMULATOR_CONTROLLER)
option(BUILD_SIMULATOR_ROBOT "Build SIMULATOR robot model library" ON)
mark_as_advanced(BUILD_SIMULATOR_ROBOT)
option(BUILD_SIMULATOR_SIMULATOR "Build SIMULATOR interface library" ON)
mark_as_advanced(BUILD_SIMULATOR_SIMULATOR)
option(BUILD_SIMULATOR_VISUALIZER "Build PUTSLAM Visualizer" ON)
mark_as_advanced(BUILD_SIMULATOR_VISUALIZER)

# demos
option(BUILD_SIMULATOR_DEMO "Build SIMULATOR demonstration programs and libraries" ON)
option(BUILD_SIMULATOR_DEMO_MAIN "Build main SIMULATOR test" ON)
mark_as_advanced(BUILD_SIMULATOR_DEMO_MAIN)
option(BUILD_SIMULATOR_DEMO_VISUALIZER "Build SIMULATOR visualizer demo" ON)
mark_as_advanced(BUILD_SIMULATOR_DEMO_VISUALIZER)

#additional dependencies
# Boost
#FIND_PACKAGE(Boost COMPONENTS system filesystem thread)
# OpenCV
# FIND_PACKAGE(OpenCV REQUIRED)
# include_directories( ${OpenCV_INCLUDE_DIRS} )

#Eigen
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/3rdParty/Eigen)
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
add_definitions(-Wno-deprecated -DEIGEN_DONT_VECTORIZE -DEIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT)

#QGLViewer library
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
FIND_PACKAGE(OpenGL)
include_directories(${OPENGL_INCLUDE_DIR})
link_directories(${OPENGL_LIBRARY})

#QGLViewer library
FIND_PACKAGE(QGLViewer)
include_directories(${QGLVIEWER_INCLUDE_DIR})
include_directories(${QT_INCLUDES})
link_directories(${QGLVIEWER_LIBRARY})

#ODE library
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
FIND_PACKAGE(ODE)
include_directories(${ODE_INCLUDE_DIR})
link_directories(${ODE_LIBRARY})

# Executable output directory
SET(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin${OUTPUT_DIRECTORY_POSTFIX} CACHE PATH "Executable output directory")
mark_as_advanced(RUNTIME_OUTPUT_DIRECTORY)

# Dynamic library output directory
SET(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin${OUTPUT_DIRECTORY_POSTFIX} CACHE PATH "Dynamic library output directory")
mark_as_advanced(LIBRARY_OUTPUT_DIRECTORY)

# Static library output directory
SET(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/lib${OUTPUT_DIRECTORY_POSTFIX} CACHE PATH "Static library output directory")
mark_as_advanced(ARCHIVE_OUTPUT_DIRECTORY)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIRECTORY})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ARCHIVE_OUTPUT_DIRECTORY})
foreach(CONFIGURATION_TYPE ${CMAKE_CONFIGURATION_TYPES})
	string(TOUPPER ${CONFIGURATION_TYPE} CONFIGURATION_TYPE)
	SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIGURATION_TYPE} ${RUNTIME_OUTPUT_DIRECTORY})
	SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIGURATION_TYPE} ${LIBRARY_OUTPUT_DIRECTORY})
	SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIGURATION_TYPE} ${ARCHIVE_OUTPUT_DIRECTORY})
endforeach(CONFIGURATION_TYPE CMAKE_CONFIGURATION_TYPES)

if(MSVC)
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
endif()

###############################################################################
#
# SIMULATOR tinyXML2 library
#
###############################################################################

#add_library(tinyxml2 SHARED ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/tinyXML/tinyxml2.h ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/tinyXML/tinyxml2.cpp)
add_library(tinyxml2 STATIC ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/tinyXML/tinyxml2.h ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/tinyXML/tinyxml2.cpp)

###############################################################################
#
# SIMULATOR defs library
#
###############################################################################

if(BUILD_SIMULATOR AND BUILD_SIMULATOR_DEFS)
        file(GLOB DEFS_HEADERS
            "${CMAKE_SOURCE_DIR}/include/Defs/defs.h"
        )
        ADD_LIBRARY(SimulatorDefs STATIC ${DEFS_HEADERS})
        set_target_properties(SimulatorDefs PROPERTIES LINKER_LANGUAGE CXX)
# 	INSTALL(TARGETS PUTSLAMDefs RUNTIME DESTINATION bin LIBRARY DESTINATION bin ARCHIVE DESTINATION lib)
        INSTALL(FILES ${DEFS_HEADERS} DESTINATION include/Defs/)

endif(BUILD_SIMULATOR AND BUILD_SIMULATOR_DEFS)

###############################################################################
#
# SIMULATOR Controller library
#
###############################################################################

if(BUILD_SIMULATOR AND BUILD_SIMULATOR_CONTROLLER)
        file(GLOB CONTROLLER_SOURCES
            "${CMAKE_SOURCE_DIR}/src/Controller/*.cpp"
        )
        file(GLOB CONTROLLER_HEADERS
            "${CMAKE_SOURCE_DIR}/include/Controller/*.h"
        )

        ADD_LIBRARY(Controller STATIC ${CONTROLLER_SOURCES} ${CONTROLLER_HEADERS})
#        INSTALL(TARGETS Controller RUNTIME DESTINATION bin LIBRARY DESTINATION bin ARCHIVE DESTINATION lib)
#        INSTALL(FILES ${CONTROLLER_HEADERS} DESTINATION include/putslam/Utilities/)
endif(BUILD_SIMULATOR AND BUILD_SIMULATOR_CONTROLLER)

###############################################################################
#
# SIMULATOR Robot library
#
###############################################################################

if(BUILD_SIMULATOR AND BUILD_SIMULATOR_ROBOT)
        file(GLOB ROBOT_SOURCES
            "${CMAKE_SOURCE_DIR}/src/RobotModel/*.cpp"
        )
        file(GLOB ROBOT_HEADERS
            "${CMAKE_SOURCE_DIR}/include/RobotModel/*.h"
        )

        ADD_LIBRARY(Robot STATIC ${ROBOT_SOURCES} ${ROBOT_HEADERS})
#        INSTALL(TARGETS Controller RUNTIME DESTINATION bin LIBRARY DESTINATION bin ARCHIVE DESTINATION lib)
#        INSTALL(FILES ${CONTROLLER_HEADERS} DESTINATION include/putslam/Utilities/)
endif(BUILD_SIMULATOR AND BUILD_SIMULATOR_ROBOT)

###############################################################################
#
# SIMULATOR Simulator library
#
###############################################################################

if(BUILD_SIMULATOR AND BUILD_SIMULATOR_SIMULATOR)
        file(GLOB SIMULATOR_SOURCES
            "${CMAKE_SOURCE_DIR}/src/Simulator/*.cpp"
        )
        file(GLOB SIMULATOR_HEADERS
            "${CMAKE_SOURCE_DIR}/include/Simulator/*.h"
        )

        ADD_LIBRARY(Simulator STATIC ${SIMULATOR_SOURCES} ${SIMULATOR_HEADERS})
        TARGET_LINK_LIBRARIES(Simulator Robot Visualizer tinyxml2 ode)
#        INSTALL(TARGETS Controller RUNTIME DESTINATION bin LIBRARY DESTINATION bin ARCHIVE DESTINATION lib)
#        INSTALL(FILES ${CONTROLLER_HEADERS} DESTINATION include/putslam/Utilities/)
endif(BUILD_SIMULATOR AND BUILD_SIMULATOR_SIMULATOR)

###############################################################################
#
# SIMULATOR Visualizer library
#
###############################################################################

if(BUILD_SIMULATOR AND BUILD_SIMULATOR_VISUALIZER)
        file(GLOB VISUALIZER_SOURCES
            "${CMAKE_SOURCE_DIR}/src/Visualizer/*.cpp"
        )
        file(GLOB VISUALIZER_HEADERS
            "${CMAKE_SOURCE_DIR}/include/Visualizer/*.h"
        )
        ADD_LIBRARY(Visualizer STATIC ${VISUALIZER_SOURCES} ${VISUALIZER_HEADERS})
        TARGET_LINK_LIBRARIES(Visualizer tinyxml2 Simulator ${QGLVIEWER_LIBRARY} ${QT_LIBRARIES} QtCore QtXml QtOpenGL QtGui ${OPENGL_LIBRARY})
#        INSTALL(TARGETS Utilities RUNTIME DESTINATION bin LIBRARY DESTINATION bin ARCHIVE DESTINATION lib)
#        INSTALL(FILES ${VISUALIZER_HEADERS} DESTINATION include/putslam/Visualizer/)
endif(BUILD_SIMULATOR AND BUILD_SIMULATOR_VISUALIZER)

###############################################################################
#
# SIMULATOR demo
#
###############################################################################

if(BUILD_SIMULATOR_DEMO AND BUILD_SIMULATOR_DEMO_MAIN)
        SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath ./")
        SET(DEMO_SOURCES ./main.cpp)
        ADD_EXECUTABLE(simulator ${DEMO_SOURCES})
#        add_dependencies(demoVisualizer Map)
        TARGET_LINK_LIBRARIES(simulator tinyxml2 Robot Simulator ode)
        INSTALL(TARGETS simulator RUNTIME DESTINATION bin)

endif(BUILD_SIMULATOR_DEMO AND BUILD_SIMULATOR_DEMO_MAIN)


###############################################################################
#
# SIMULATOR demo Visualizer
#
###############################################################################

if(BUILD_SIMULATOR_DEMO AND BUILD_SIMULATOR_DEMO_VISUALIZER)
        SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath ./")
        SET(DEMO_SOURCES ./demos/demoVisualizer.cpp)
        ADD_EXECUTABLE(demoVisualizer ${DEMO_SOURCES})
#        add_dependencies(demoVisualizer Map)
        TARGET_LINK_LIBRARIES(demoVisualizer Simulator tinyxml2 ${QGLVIEWER_LIBRARY} ${QT_LIBRARIES} ${QT_LIBRARIES} QtCore QtXml QtOpenGL QtGui ${OPENGL_LIBRARY} glut)
        INSTALL(TARGETS demoVisualizer RUNTIME DESTINATION bin)

endif(BUILD_SIMULATOR_DEMO AND BUILD_SIMULATOR_DEMO_VISUALIZER)
