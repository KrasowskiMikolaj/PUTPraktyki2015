/**
 * Project Untitled
 */


#include "../../include/Simulator/simulatorODE.h"

/**
 * simulatorODE implementation
 */
dJointGroupID SimulatorODE::contactgroup;
dWorldID SimulatorODE::world;


/*TEST*/
static dBodyID cylbody;
static dGeomID cylgeom;

static dBodyID sphbody;
static dGeomID sphgeom;
#define CYLRADIUS    0.6
#define CYLLENGTH    2.0
#define SPHERERADIUS 0.5


#ifdef dDOUBLE
#define dsDrawBox dsDrawBoxD
#define dsDrawLine dsDrawLineD
#endif
/*TEST END*/



using namespace simulator;

/// A single instance of SimulatorODE
SimulatorODE::Ptr simulatorODE;

SimulatorODE::SimulatorODE(void) : Simulator("ODE simulator", TYPE_ODE) {

}

/// Construction
SimulatorODE::SimulatorODE(std::string configFilename) : config(configFilename), Simulator("ODE simulator", TYPE_ODE){
}

SimulatorODE::~SimulatorODE(void) {

}

///Attach visualizer
void SimulatorODE::attachVisualizer(QGLVisualizer* visualizer){
    attach(visualizer);
}

simulator::Simulator* simulator::createODESimulator(void) {
    simulatorODE.reset(new SimulatorODE());
    return simulatorODE.get();
}

simulator::Simulator* simulator::createODESimulator(std::string configFilename) {
    simulatorODE.reset(new SimulatorODE(configFilename));
    return simulatorODE.get();
}

void SimulatorODE::startSimulation(){
    InitODE();
    while(1)
        SimLoop();
}

void SimulatorODE::stopSimulation(){
    CloseODE();
}

void SimulatorODE::InitODE(){
    world=dWorldCreate();
    space=dSimpleSpaceCreate(0);
    contactgroup = dJointGroupCreate(0);
    dCreatePlane(space,0,1,0,0);
    dWorldSetGravity(world, 0,-9.81,0);
    dWorldSetERP(world, 0.2);
    dWorldSetCFM(world, 1e-5);
    dWorldSetContactMaxCorrectingVel(world, 0.9);
    dWorldSetContactSurfaceLayer(world, 0.001);
    dWorldSetAutoDisableFlag(world, 1);
    dInitODE();
    dMatrix3 R;
    dMass m;
    double mass = 24;
    Object.Body = dBodyCreate(world);
    double sides[3];

        // Set up for static object - rama glowna
        sides[0] = 0.03;
        sides[1] = 0.03;
        sides[2] = 0.03;
        dBodySetPosition(Object.Body, 0, 10, 0);
        dBodySetLinearVel(Object.Body, 0, 0, 0);
        dRFromAxisAndAngle(R, 1, 0, 0, 0);
        dBodySetRotation(Object.Body, R);
         //ustawia gestosc dla masy dMassSetBoxTotal
        dMassSetParameters(&m,mass,0,0,0,1,1,1,0,0,0);

        Object.Geom[0] = dCreateBox(space, sides[0], sides[1], sides[2]);
        dGeomSetBody(Object.Geom[0], Object.Body);

       // dMassSetBoxTotal(&m, mass, sides[0], sides[1], sides[2]);
        dBodySetMass(Object.Body, &m);
       // dMassTranslate(&m,10,10,10);
    std::cout << "dd1\n";

    //Object.Geom[0] = dCreateBox(Space, sides[0], sides[1], sides[2]);


    std::cout << "dd2\n";

    //dGeomSetBody(Object.Geom[0], Object.Body);

    std::cout << "dd3\n";

    //
    //dMassSetBoxTotal(&m, mass, sides[0], sides[1], sides[2]); //ustawia gestosc dla masy dMassSetBoxTotal

    std::cout<<m.mass;

    //dBodySetMass(Object.Body, &m);
}


void SimulatorODE::CloseODE(){
    dJointGroupDestroy(contactgroup);
    dSpaceDestroy(space);
    dWorldDestroy(world);
}

void SimulatorODE::nearCallback (void *data, dGeomID o1, dGeomID o2)
{
    int i;
    dBodyID b1 = dGeomGetBody(o1);
    dBodyID b2 = dGeomGetBody(o2);
    dContact contact[MAX_CONTACTS];
    for (i = 0; i < MAX_CONTACTS; i++)
    {
        contact[i].surface.mode = dContactBounce | dContactSoftCFM;
        contact[i].surface.mu = dInfinity;
        contact[i].surface.mu2 = 0;
        contact[i].surface.bounce = 0.01;
        contact[i].surface.bounce_vel = 0.1;
        contact[i].surface.soft_cfm = 0.01;
    }
    if (int numc = dCollide(o1, o2, MAX_CONTACTS, &contact[0].geom, sizeof(dContact)))
    {
        for (i = 0; i < numc; i++)
        {
            dJointID c = dJointCreateContact(SimulatorODE::world, SimulatorODE::contactgroup, contact + i);
            dJointAttach(c, b1, b2);
        }
    }
}


/*
void SimulatorODE::ODEtoOGL(float* M, const float* p, const float* R)
{
    M[0]  = R[0]; M[1]  = R[4]; M[2]  = R[8];  M[3]  = 0;
    M[4]  = R[1]; M[5]  = R[5]; M[6]  = R[9];  M[7]  = 0;
    M[8]  = R[2]; M[9]  = R[6]; M[10] = R[10]; M[11] = 0;
    M[12] = p[0]; M[13] = p[1]; M[14] = p[2];  M[15] = 1;
}

void SimulatorODE::DrawGeom (dGeomID g, const dReal *pos, const dReal *R, int show_aabb)
{
    if (!g)
        return;
    if (!pos)
        pos = dGeomGetPosition (g);
    if (!R)
        R = dGeomGetRotation (g);
    int type = dGeomGetClass (g);

    if (type == dBoxClass)
    {
        dReal sides[3];
        dGeomBoxGetLengths(g, sides);
        DrawBox(sides, pos, R);
    }
}

void SimulatorODE::DrawBox(const float sides[3], const float pos[3], const float R[12])
{
    float mat_ambient[] = { 0.8, 0.8, 0.8, 1.0 };
    float mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

    //glBindTexture(GL_TEXTURE_2D, texture[0].TexID);

    glPushMatrix();
    float M[16];
    GeomMatrix.ODEtoOGL(M, pos, R);
    glMultMatrixf(GeomMatrix.Element);
    glBegin(GL_TRIANGLES);
        // Front Face
            glNormal3fv(&polygon[0].Vertex[0].nx);
        glTexCoord2f(0.0f, 0.0f); glVertex3fv(&polygon[0].Vertex[0].x);
        glTexCoord2f(1.0f, 0.0f); glVertex3fv(&polygon[0].Vertex[1].x);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(&polygon[0].Vertex[2].x);

        glTexCoord2f(0.0f, 0.0f); glVertex3fv(&polygon[1].Vertex[0].x);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(&polygon[1].Vertex[1].x);
        glTexCoord2f(0.0f, 1.0f); glVertex3fv(&polygon[1].Vertex[2].x);
        // Back Face
            glNormal3fv(&polygon[2].Vertex[0].nx);
        glTexCoord2f(0.0f, 0.0f); glVertex3fv(&polygon[2].Vertex[0].x);
        glTexCoord2f(1.0f, 0.0f); glVertex3fv(&polygon[2].Vertex[1].x);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(&polygon[2].Vertex[2].x);

        glTexCoord2f(0.0f, 0.0f); glVertex3fv(&polygon[3].Vertex[0].x);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(&polygon[3].Vertex[1].x);
        glTexCoord2f(0.0f, 1.0f); glVertex3fv(&polygon[3].Vertex[2].x);
        // Top Face
            glNormal3fv(&polygon[4].Vertex[0].nx);
        glTexCoord2f(0.0f, 0.0f); glVertex3fv(&polygon[4].Vertex[0].x);
        glTexCoord2f(1.0f, 0.0f); glVertex3fv(&polygon[4].Vertex[1].x);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(&polygon[4].Vertex[2].x);

        glTexCoord2f(0.0f, 0.0f); glVertex3fv(&polygon[5].Vertex[0].x);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(&polygon[5].Vertex[1].x);
        glTexCoord2f(0.0f, 1.0f); glVertex3fv(&polygon[5].Vertex[2].x);
        // Bottom Face
            glNormal3fv(&polygon[6].Vertex[0].nx);
        glTexCoord2f(0.0f, 0.0f); glVertex3fv(&polygon[6].Vertex[0].x);
        glTexCoord2f(1.0f, 0.0f); glVertex3fv(&polygon[6].Vertex[1].x);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(&polygon[6].Vertex[2].x);

        glTexCoord2f(0.0f, 0.0f); glVertex3fv(&polygon[7].Vertex[0].x);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(&polygon[7].Vertex[1].x);
        glTexCoord2f(0.0f, 1.0f); glVertex3fv(&polygon[7].Vertex[2].x);
        // Right face
            glNormal3fv(&polygon[8].Vertex[0].nx);
        glTexCoord2f(0.0f, 0.0f); glVertex3fv(&polygon[8].Vertex[0].x);
        glTexCoord2f(1.0f, 0.0f); glVertex3fv(&polygon[8].Vertex[1].x);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(&polygon[8].Vertex[2].x);

        glTexCoord2f(0.0f, 0.0f); glVertex3fv(&polygon[9].Vertex[0].x);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(&polygon[9].Vertex[1].x);
        glTexCoord2f(0.0f, 1.0f); glVertex3fv(&polygon[9].Vertex[2].x);
        // Left Face
            glNormal3fv(&polygon[10].Vertex[0].nx);
        glTexCoord2f(0.0f, 0.0f); glVertex3fv(&polygon[10].Vertex[0].x);
        glTexCoord2f(1.0f, 0.0f); glVertex3fv(&polygon[10].Vertex[1].x);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(&polygon[10].Vertex[2].x);

        glTexCoord2f(0.0f, 0.0f); glVertex3fv(&polygon[11].Vertex[0].x);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(&polygon[11].Vertex[1].x);
        glTexCoord2f(0.0f, 1.0f); glVertex3fv(&polygon[11].Vertex[2].x);
    glEnd();
    glPopMatrix();
}
*/
void SimulatorODE::SimLoop()
{
    dSpaceCollide(space, 0, &nearCallback);
    dWorldQuickStep(world, 0.0001);
    dJointGroupEmpty(contactgroup);
    const dReal *pos;
    pos = dGeomGetPosition (Object.Geom[0]);
    std::cout << "pos: x: " << pos[0] << ",y: " << pos[1] << ",z: " << pos[2] << "\n";
    getchar();
    //this->notify(
//  DrawGeom(Object.Geom[0], 0, 0, 0);
}

/*init cylinder from ode/demos*/

/*void SimulatorODE::InitODE(){
    {
      dMass m;

      // setup pointers to drawstuff callback functions


      // create world
      dInitODE2(0);
      world = dWorldCreate();
      space = dHashSpaceCreate (0);
      contactgroup = dJointGroupCreate (0);
      dWorldSetGravity (world,0,0,-9.8);
      dWorldSetQuickStepNumIterations (world, 32);

      dCreatePlane (space,0,0,1, 0.0);

      cylbody = dBodyCreate (world);
      dQuaternion q;
    #if 0
      dQFromAxisAndAngle (q,1,0,0,M_PI*0.5);
    #else
    //  dQFromAxisAndAngle (q,1,0,0, M_PI * 1.0);
      dQFromAxisAndAngle (q,1,0,0, M_PI * -0.77);
    #endif
      dBodySetQuaternion (cylbody,q);
      dMassSetCylinder (&m,1.0,3,CYLRADIUS,CYLLENGTH);
      dBodySetMass (cylbody,&m);
      cylgeom = dCreateCylinder(0, CYLRADIUS, CYLLENGTH);
      dGeomSetBody (cylgeom,cylbody);
      dBodySetPosition (cylbody, 0, 0, 3);
      dSpaceAdd (space, cylgeom);

      sphbody = dBodyCreate (world);
      dMassSetSphere (&m,1,SPHERERADIUS);
      dBodySetMass (sphbody,&m);
      sphgeom = dCreateSphere(0, SPHERERADIUS);
      dGeomSetBody (sphgeom,sphbody);
      dBodySetPosition (sphbody, 0, 0, 5.5);
      dSpaceAdd (space, sphgeom);

      // run simulation
      //dsSimulationLoop (argc,argv,352,288,&fn);

      dJointGroupEmpty (contactgroup);
      dJointGroupDestroy (contactgroup);

      dGeomDestroy(sphgeom);
      dGeomDestroy (cylgeom);

      dSpaceDestroy (space);
      dWorldDestroy (world);
      dCloseODE();
      return 0;
    }
*/
