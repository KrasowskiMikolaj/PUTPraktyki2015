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
        std::cout<<"error loading leg configuration: \n" << filename << "\n";
    legConfig.FirstChildElement( "Leg" )->QueryIntAttribute("segmentsNo",&segmentNo);
    std::cout<<"Segments no: "<<segmentNo<<"\n";
    segment.resize(segmentNo);
    for(int i=0;i<segmentNo;i++){
        std::stringstream ss;
        ss << "Segment" << i;
        std::string segmentName(ss.str());
        legConfig.FirstChildElement(segmentName.c_str())->QueryDoubleAttribute("mass",&segment[i].mass);
        legConfig.FirstChildElement(segmentName.c_str())->QueryDoubleAttribute("sizeX",&segment[i].size.x());
        legConfig.FirstChildElement(segmentName.c_str())->QueryDoubleAttribute("sizeY",&segment[i].size.y());
        legConfig.FirstChildElement(segmentName.c_str())->QueryDoubleAttribute("sizeZ",&segment[i].size.z());
        legConfig.FirstChildElement(segmentName.c_str())->QueryDoubleAttribute("centerX",&segment[i].center.x());
        legConfig.FirstChildElement(segmentName.c_str())->QueryDoubleAttribute("centerY",&segment[i].center.y());
        legConfig.FirstChildElement(segmentName.c_str())->QueryDoubleAttribute("centerZ",&segment[i].center.z());
        legConfig.FirstChildElement(segmentName.c_str())->QueryDoubleAttribute("centerRoll",&segment[i].centerRoll);
        legConfig.FirstChildElement(segmentName.c_str())->QueryDoubleAttribute("centerPitch",&segment[i].centerPitch);
        legConfig.FirstChildElement(segmentName.c_str())->QueryDoubleAttribute("centerYaw",&segment[i].centerYaw);
        std::cout<<"Segment "<<i<<" properties: mass="<<segment[i].mass;
    }
}

legAntropomorphic::~legAntropomorphic(){

}
