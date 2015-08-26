#include "../include/Visualizer/matrix.h"

MATRIX::MATRIX()
{
}

GLvoid MATRIX::ODEtoOGL(float* M, const float* p, const float* R)
{

    M[0]  = R[0]; M[1]  = R[4]; M[2]  = R[8];  M[3]  = 0;

    M[4]  = R[1]; M[5]  = R[5]; M[6]  = R[9];  M[7]  = 0;

    M[8]  = R[2]; M[9]  = R[6]; M[10] = R[10]; M[11] = 0;

    M[12] = p[0]; M[13] = p[1]; M[14] = p[2];  M[15] = 1;

}
