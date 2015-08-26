#ifndef QUAT_H
#define QUAT_H

class QUAT
{
    public:
        QUAT(GLfloat sx = 0, GLfloat sy = 0, GLfloat sz = 0, GLfloat sw = 1);
        ~QUAT();

        GLvoid Reset();
        GLvoid CopyQuat(QUAT q);
                GLvoid Set(GLfloat sx, GLfloat sy, GLfloat sz, GLfloat sw) {x = sx, y = sy, z = sz, w = sw;}
                GLvoid AxisAngleToQuat(VECTOR axis, GLfloat theta);
        GLvoid EulerToQuat(GLfloat pitch, GLfloat yaw, GLfloat roll);
                GLvoid NormaliseQuat();
                GLfloat MagnitudeQuat();
                GLvoid MultQuat(QUAT q);
        GLvoid MatrixToQuat(float m[4][4]);

            GLfloat x;
            GLfloat y;
            GLfloat z;
            GLfloat w;
};

#endif // QUAT_H

