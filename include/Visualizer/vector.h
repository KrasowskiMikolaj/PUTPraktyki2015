#ifndef VECTOR_H
#define VECTOR_H
#include<GL/glut.h>
class VECTOR
{
        public:
                VECTOR(GLfloat sx = 0, GLfloat sy = 0, GLfloat sz = 0);
                ~VECTOR();

                GLfloat GetMagnitude();
                GLvoid Normalize();
                GLvoid Reset();
                GLvoid Set(GLfloat sx, GLfloat sy, GLfloat sz) {x = sx, y = sy, z = sz;}
                GLvoid CrossVector(VECTOR vect);
                GLfloat DotProduct(VECTOR vect);

                GLfloat x;
                GLfloat y;
                GLfloat z;
};

#endif // VECTOR_H

