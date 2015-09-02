/**
 * Project Untitled
 */


#include "../include/RobotModel/legAntropomorphic.h"
#include <iostream>

using namespace simulator;
/**
 * legAntropomorphic implementation
 */


legAntropomorphic::legAntropomorphic(void){

}



void legAntropomorphic::load(std::string legFilename){

    tinyxml2::XMLDocument legConfig;
    std::string filename="../../resources/"+legFilename;
    legConfig.LoadFile(filename.c_str());
    if(legConfig.ErrorID())
        std::cout<<"error loading leg configuration";
    legConfig.FirstChildElement( "Leg" )->QueryIntAttribute("segmentsNo",&segmentNo);
    std::cout<<"Segments no: "<<segmentNo<<"\n";
    segment.resize(segmentNo);
    for(int i=0;i<segmentNo;i++){
        legConfig.FirstChildElement("Segment"+i)->QueryDoubleAttribute("mass",&segment[i].mass);
        legConfig.FirstChildElement("Segment"+i)->QueryDoubleAttribute("sizeX",&segment[i].size.x());
        legConfig.FirstChildElement("Segment"+i)->QueryDoubleAttribute("sizeY",&segment[i].size.y());
        legConfig.FirstChildElement("Segment"+i)->QueryDoubleAttribute("sizeZ",&segment[i].size.z());
        legConfig.FirstChildElement("Segment"+i)->QueryDoubleAttribute("centerX",&segment[i].center.x());
        legConfig.FirstChildElement("Segment"+i)->QueryDoubleAttribute("centerY",&segment[i].center.y());
        legConfig.FirstChildElement("Segment"+i)->QueryDoubleAttribute("centerZ",&segment[i].center.z());
        legConfig.FirstChildElement("Segment"+i)->QueryDoubleAttribute("centerRoll",&segment[i].centerRoll);
        legConfig.FirstChildElement("Segment"+i)->QueryDoubleAttribute("centerPitch",&segment[i].centerPitch);
        legConfig.FirstChildElement("Segment"+i)->QueryDoubleAttribute("centerYaw",&segment[i].centerYaw);
        std::cout<<"Segment "<<i<<" properties: mass="<<segment[i].mass;
    }
}

legAntropomorphic::~legAntropomorphic(){

}
