#include <GL/glui.h>
#include "Block.h"
#include "Camera.h"
#include "Skybox.h"
#include "City.h"

/*
Authors: Austin Mack, Tyler Hartwig
Final Project: Procedurally Generated City
*/

/** These are the live variables passed into GLUI ***/
int	 camRotU = 0;
int	 camRotV = 0;
int	 camRotW = 0;
int  viewAngle = 60;
float eyeX = -350;
float eyeY = 150;
float eyeZ = -350;
float lookX = 1;
float lookY = -0.5;
float lookZ = 1;
float clipNear = 1;
float clipFar = 10000;

SmallBuilding* smallBuilding;
TieredBuilding* tieredBuilding;
ModernBuilding* modernBuilding;
SkyscraperBuilding* skyscraperBuilding;
Building* building;
Block* block;
City* city;
Skybox* skybox;

int  main_window;


/** these are the global variables used for rendering **/
Camera* camera = new Camera();

// Randomize particular things
void randomize(){
    building->randomize();
    block->randomize();
    skybox->randomize();
}

/***************************************** myGlutIdle() ***********/

void myGlutIdle(void)
{
    /* According to the GLUT specification, the current window is
    undefined during an idle callback.  So we need to explicitly change
    it if necessary */
    if (glutGetWindow() != main_window)
        glutSetWindow(main_window);

    glutPostRedisplay();
}


/**************************************** myGlutReshape() *************/

void myGlutReshape(int x, int y)
{
    float xy_aspect;

    xy_aspect = (float)x / (float)y;
    glViewport(0, 0, x, y);

    camera->SetScreenSize(x, y);

    glutPostRedisplay();
}

/***************************************** myGlutDisplay() *****************/

void myGlutDisplay(void)
{
    glClearColor(.0f, .0f, .0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_LIGHTING);

    camera->SetViewAngle(viewAngle);
    camera->SetNearPlane(clipNear);
    camera->SetFarPlane(clipFar);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    Matrix projection = camera->GetProjectionMatrix();
    glMultMatrixd(projection.unpack());


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Point eyeP(eyeX, eyeY, eyeZ);
    Vector lookV(lookX, lookY, lookZ);
    Vector upV(0, 1, 0);
    camera->Orient(eyeP, lookV, upV);
    camera->RotateV(camRotV);
    camera->RotateU(camRotU);
    camera->RotateW(camRotW);
    Matrix modelView = camera->GetModelViewMatrix();
    glMultMatrixd(modelView.unpack());



    // Render City and skybox
    city->render();
    skybox->render();


    camera->RotateV(-camRotV);
    camera->RotateU(-camRotU);
    camera->RotateW(-camRotW);

    glutSwapBuffers();
}

void onExit()
{
    delete camera;
    delete smallBuilding;
    delete tieredBuilding;
    delete modernBuilding;
    delete skyscraperBuilding;
    delete block;
    delete city;
    delete skybox;
}

/**************************************** main() ********************/

int main(int argc, char* argv[])
{
    atexit(onExit);



    /****************************************/
    /*   Initialize GLUT and create window  */
    /****************************************/

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);

    main_window = glutCreateWindow("CSI 4341: Assignment 2");
    glutDisplayFunc(myGlutDisplay);
    glutReshapeFunc(myGlutReshape);

    /****************************************/
    /*       Set up OpenGL lighting         */
    /****************************************/


    glClearColor (0.38, 0.38, 0.38, 0.0);
    glShadeModel (GL_SMOOTH);

    GLfloat light_pos0[] = {20.0f, 20.0f, 20.0f, 0.0f};
    GLfloat diffuse[] = { 0.4f, 0.4f, 0.4f, 1.0 };
    GLfloat ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };

    glLightfv (GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv (GL_LIGHT0, GL_POSITION, light_pos0);

    glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable (GL_COLOR_MATERIAL);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glEnable (GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);



    ///****************************************/
    ///*          Enable z-buferring          */
    ///****************************************/


    glPolygonOffset(1, 1);

    srand(time(0));
    smallBuilding = new SmallBuilding();
    tieredBuilding = new TieredBuilding();
    skyscraperBuilding = new SkyscraperBuilding();
    modernBuilding = new ModernBuilding();
    block = new Block();
    city = new City();
    skybox = new Skybox();


    /****************************************/
    /*         Here's the GLUI code         */
    /****************************************/

    GLUI *glui = GLUI_Master.create_glui("GLUI");


    GLUI_Panel *camera_panel = glui->add_panel("Camera");
    (new GLUI_Spinner(camera_panel, "RotateV:", &camRotV))
            ->set_int_limits(-179, 179);
    (new GLUI_Spinner(camera_panel, "RotateU:", &camRotU))
            ->set_int_limits(-179, 179);
    (new GLUI_Spinner(camera_panel, "RotateW:", &camRotW))
            ->set_int_limits(-179, 179);
    (new GLUI_Spinner(camera_panel, "Angle:", &viewAngle))
            ->set_int_limits(1, 179);

    GLUI_Spinner* eyex_widget = glui->add_spinner_to_panel(camera_panel, "EyeX:", GLUI_SPINNER_FLOAT, &eyeX);
    eyex_widget->set_float_limits(-500, 500);
    GLUI_Spinner* eyey_widget = glui->add_spinner_to_panel(camera_panel, "EyeY:", GLUI_SPINNER_FLOAT, &eyeY);
    eyey_widget->set_float_limits(-500, 500);
    GLUI_Spinner* eyez_widget = glui->add_spinner_to_panel(camera_panel, "EyeZ:", GLUI_SPINNER_FLOAT, &eyeZ);
    eyez_widget->set_float_limits(-500, 500);

    GLUI_Spinner* lookx_widget = glui->add_spinner_to_panel(camera_panel, "LookX:", GLUI_SPINNER_FLOAT, &lookX);
    lookx_widget->set_float_limits(-5, 5);
    GLUI_Spinner* looky_widget = glui->add_spinner_to_panel(camera_panel, "LookY:", GLUI_SPINNER_FLOAT, &lookY);
    looky_widget->set_float_limits(-5, 5);
    GLUI_Spinner* lookz_widget = glui->add_spinner_to_panel(camera_panel, "LookZ:", GLUI_SPINNER_FLOAT, &lookZ);
    lookz_widget->set_float_limits(-5, 5);

    GLUI_Spinner* clipN_widget = glui->add_spinner_to_panel(camera_panel, "Near:", GLUI_SPINNER_FLOAT, &clipNear);
    clipN_widget->set_float_limits(0, 10);
    GLUI_Spinner* clipF_widget = glui->add_spinner_to_panel(camera_panel, "Far:", GLUI_SPINNER_FLOAT, &clipFar);
    clipF_widget->set_float_limits(0, 10000);

    glui->add_column(true);

    glui->add_button("Random", 1, (GLUI_Update_CB)randomize);
    glui->add_button("Quit", 0, (GLUI_Update_CB)exit);

    glui->set_main_gfx_window(main_window);

    /* We register the idle callback with GLUI, *not* with GLUT */
    GLUI_Master.set_glutIdleFunc(myGlutIdle);

    glutMainLoop();

    return EXIT_SUCCESS;
}



