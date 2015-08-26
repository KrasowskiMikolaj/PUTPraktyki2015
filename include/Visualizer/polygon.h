// Polygon Class    by Alan Baylis 2001

#ifndef PolygonH
#define PolygonH

#include "texture.h"
#include "../include/Visualizer/vector.h"
#include "vertex.h"

class POLYGON
{
public:
     POLYGON();
     ~POLYGON();
     VECTOR GetNormal();
     void SetNormal();
     float Scale[2];
     float Shift[2];
     float Rotate;
     unsigned int Texture;
     VERTEX Vertex[3];
};
#endif
