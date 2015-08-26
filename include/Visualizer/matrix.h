#ifndef MATRIX_H
#define MATRIX_H

#include "../include/Visualizer/vector.h"
#include "../include/Visualizer/quat.h"

class MATRIX
{
public:
        MATRIX();
        ~MATRIX();

        GLvoid LoadIdentity();
        GLvoid CopyMatrix(GLfloat m[16]);
        GLvoid MultMatrix(GLfloat m[16]);
        GLvoid MatrixInverse();
        GLvoid MatrixFromAxisAngle(VECTOR axis, GLfloat theta);
        GLvoid QuatToMatrix(QUAT quat);
        GLvoid ODEtoOGL(float* M, const float* p, const float* R);

        GLfloat Element[16];
};

#endif // MATRIX_H

