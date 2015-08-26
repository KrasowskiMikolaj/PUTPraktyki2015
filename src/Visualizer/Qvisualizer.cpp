#include "../include/Visualizer/Qvisualizer.h"
#include <Eigen/Eigenvalues>
#include <memory>
#include <cmath>
#include <stdexcept>
#include <chrono>
#include <GL/glut.h>


using namespace simulator;

/// A single instance of Visualizer
QGLVisualizer::Ptr visualizer;

class SolidSphere
{
protected:
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texcoords;
    std::vector<GLushort> indices;

public:
    SolidSphere(float radius, unsigned int rings, unsigned int sectors)
    {
        float const R = 1./(float)(rings-1);
        float const S = 1./(float)(sectors-1);
        int r, s;

        vertices.resize(rings * sectors * 3);
        normals.resize(rings * sectors * 3);
        texcoords.resize(rings * sectors * 2);
        std::vector<GLfloat>::iterator v = vertices.begin();
        std::vector<GLfloat>::iterator n = normals.begin();
        std::vector<GLfloat>::iterator t = texcoords.begin();
        for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
                float const y = sin( -M_PI_2 + M_PI * r * R );
                float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
                float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );

                *t++ = s*S;
                *t++ = r*R;

                *v++ = x * radius;
                *v++ = y * radius;
                *v++ = z * radius;

                *n++ = x;
                *n++ = y;
                *n++ = z;
        }

        indices.resize(rings * sectors * 4);
        std::vector<GLushort>::iterator i = indices.begin();
        for(r = 0; r < rings-1; r++) for(s = 0; s < sectors-1; s++) {
                *i++ = r * sectors + s;
                *i++ = r * sectors + (s+1);
                *i++ = (r+1) * sectors + (s+1);
                *i++ = (r+1) * sectors + s;
        }
    }

    void draw(GLfloat x, GLfloat y, GLfloat z)
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(x,y,z);
        glEnable(GL_NORMALIZE);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
        glNormalPointer(GL_FLOAT, 0, &normals[0]);
        glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
        glPopMatrix();
    }
};

QGLVisualizer::QGLVisualizer(void) {
}

/// Construction
QGLVisualizer::QGLVisualizer(Config _config): config(_config){

}

/// Construction
QGLVisualizer::QGLVisualizer(std::string configFile) :
        config(configFile) {
    tinyxml2::XMLDocument configXML;
    std::string filename = "../../resources/" + configFile;
    configXML.LoadFile(filename.c_str());
    if (configXML.ErrorID())
        std::cout << "unable to load visualizer config file.\n";
}

/// Destruction
QGLVisualizer::~QGLVisualizer(void) {
}

/// Observer update
void QGLVisualizer::update(std::vector<simulator::Mat34>& envState) {
    mtxObjects.lock();
    objects = envState;
    mtxObjects.unlock();
}

/// draw objects
void QGLVisualizer::draw(){
    // Here we are in the world coordinate system. Draw unit size axis.
    drawAxis();
    SolidSphere sphere(0.1,64,64);
    sphere.draw(0.5,0.5,1.75);
    //DrawBox(0.1,0.1,0.1,objects[0]);
    mtxObjects.lock();
    if (objects.size()>0){
       DrawBox(0.5,0.5,1.5,objects[0]);
        //sphere.draw(objects[0](0,3),objects[0](1,3),objects[0](2,3));
    }
    mtxObjects.unlock();
}

/// draw objects
void QGLVisualizer::animate(){
}

/// initialize visualizer
void QGLVisualizer::init(){
    // Light setup
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0);
    GLfloat specular_color[4] = { 0.99f, 0.99f, 0.99f, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  specular_color);

    //Set global ambient light
    GLfloat black[] = {0.99, 0.99, 0.99, 1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);

    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    // Restore previous viewer state.
    //restoreStateFromFile();

    camera()->setZNearCoefficient(0.00001);
    camera()->setZClippingCoefficient(100.0);

    //setBackgroundColor(config.backgroundColor);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Opens help window
    help();

    startAnimation();
}

/// generate help string
std::string QGLVisualizer::help() const{
    std::string text("S i m p l e V i e w e r");
    text += "Use the mouse to move the camera around the object. ";
    text += "You can respectively revolve around, zoom and translate with the three mouse buttons. ";
    text += "Left and middle buttons pressed together rotate around the camera view direction axis<br><br>";
    text += "Pressing <b>Alt</b> and one of the function keys (<b>F1</b>..<b>F12</b>) defines a camera keyFrame. ";
    text += "Simply press the function key again to restore it. Several keyFrames define a ";
    text += "camera path. Paths are saved when you quit the application and restored at next start.<br><br>";
    text += "Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, ";
    text += "<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save a snapshot. ";
    text += "See the <b>Keyboard</b> tab in this window for a complete shortcut list.<br><br>";
    text += "Double clicks automates single click actions: A left button double click aligns the closer axis with the camera (if close enough). ";
    text += "A middle button double click fits the zoom of the camera and the right button re-centers the scene.<br><br>";
    text += "A left button double click while holding right button pressed defines the camera <i>Revolve Around Point</i>. ";
    text += "See the <b>Mouse</b> tab and the documentation web pages for details.<br><br>";
    text += "Press <b>Escape</b> to exit the viewer.";
    return text;
}

void QGLVisualizer::DrawBox(GLfloat sizeX, GLfloat sizeY,GLfloat sizeZ,Mat34 object)
{
    float_type GLmat[16]={object(0,0), object(1,0), object(2,0), object(3,0),
                          object(0,1), object(1,1), object(2,1), object(3,1),
                          object(0,2), object(1,2), object(2,2), object(3,2),
                          object(0,3), object(1,3), object(2,3), object(3,3)};
    glPushMatrix();
    glMultMatrixd(GLmat);
                ///rysowanie szescianu
    glScalef(sizeX,sizeY,sizeZ);
    glBegin(GL_QUADS);

    // Yellow side - FRONT
    glBegin(GL_POLYGON);
    glColor3f( 0.0, 1.0, 1.0 );
    glVertex3f(  0.5, -0.5, -0.5 );    glVertex3f(  0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );    glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();

    // White side - BACK
    glBegin(GL_POLYGON);
    glColor3f(   1.0,  1.0, 1.0 );
    glVertex3f(  0.5, -0.5, 0.5 );
    glVertex3f(  0.5,  0.5, 0.5 );
    glVertex3f( -0.5,  0.5, 0.5 );
    glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();

    // Purple side - RIGHT
    glBegin(GL_POLYGON);
    glColor3f(  1.0,  0.0,  1.0 );
    glVertex3f( 0.5, -0.5, -0.5 );
    glVertex3f( 0.5,  0.5, -0.5  );
    glVertex3f( 0.5,  0.5,  0.5  );
    glVertex3f( 0.5, -0.5,  0.5  );
    glEnd();

    // Green side - LEFT
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  1.0,  0.0 );
    glVertex3f( -0.5 , -0.5 ,  0.5  );
    glVertex3f( -0.5 ,  0.5 ,  0.5  );
    glVertex3f( -0.5 ,  0.5 , -0.5  );
    glVertex3f( -0.5 , -0.5 , -0.5  );
    glEnd();

    // Blue side - TOP
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  0.0,  1.0 );
    glVertex3f(  0.5 ,  0.5 ,  0.5  );
    glVertex3f(  0.5 ,  0.5 , -0.5  );
    glVertex3f( -0.5 ,  0.5 , -0.5  );
    glVertex3f( -0.5 ,  0.5 ,  0.5  );
    glEnd();

    // Red side - BOTTOM
    glBegin(GL_POLYGON);
    glColor3f(   1.0,  0.0,  0.0 );
    glVertex3f(  0.5 , -0.5 , -0.5  );
    glVertex3f(  0.5 , -0.5 ,  0.5  );
    glVertex3f( -0.5 , -0.5 ,  0.5  );
    glVertex3f( -0.5 , -0.5 , -0.5  );
    glEnd();

    //glFlush();

    glEnd();
    glPopMatrix();
}

