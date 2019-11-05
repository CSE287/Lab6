#include <GL/gl.h>
#include <GL/freeglut.h>   // freeglut.h might be a better alternative, if available.
#include <cstdio>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>

#include "pnm.hpp"

int main_window = -1; // The one and only main window
int displayedProblem = 1;

static Image screenshot() {
    unsigned int width = glutGet(GLUT_WINDOW_WIDTH);
    unsigned int height = glutGet(GLUT_WINDOW_HEIGHT);
    std::vector<float> pixels(width*height*3);
    glReadPixels(0, 0, width, height, GL_RGB, GL_FLOAT, (float*)&pixels[0]);

    Image image(width, height);
    for (int i = 0; i < height; ++i){
        std::copy_n(&pixels[i*width*3], width*3, (double*)image[height-i-1]);
    }
    return image;
}

void problem1() {
    /* Use the linear algebra functions of GLM to solve the following system of
     * linear equations. Return the solution as a glm::dvec3.
     *
     *  3x + 7y + 2z =  4
     *  2x - 4y - 3z = -1
     *  5x + 2y +  z =  1
     */

    std::ostringstream answer;
    answer << "Replace this with the answer\nTo Problem 1";
    glColor3f(0, 0, 1);
    glRasterPos2d(-0.5, 0);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)(answer.str().c_str()));
}


void triangle(){
    glBegin(GL_TRIANGLES);
    glVertex2d(-1, 1);
    glVertex2d( -1, -1);
    glVertex2d( 1, 0);
    glEnd();
}

void problem2() {
    // Make the triangle half as big and translate it to to the right until the rightmost corner
    // touches the edge of thw window.

    glColor3f(1, 0,0);
    triangle();
}



void problem3()
{
    // Use a scale transformation to shrink the triangle to three quarters the
    // original size

    glColor3f(1, 0,0);
    triangle();

} // end Problem3

void problem4()
{
    // Use a scale transformation to reflect the triangle across the x axis

    glColor3f(1, 0,0);
    triangle();
} // end Problem4



// Shear the triangle by a factor of 3 in the horizontal direction by
// calling transformVertices
void problem5()
{




} // end Problem5

// Rotate the triangle by negative 90 degrees by calling transformVertices.
void problem6()
{


} // end Problem6


// Create a composite transformation that translates the triangle 200 in the
// horizontal direction 300 in the vertical direction and rotates it in that
// position by 180 degrees. Use the transformVertices function.
void problem7()
{



} // end Problem7

// Translate to the same position as the previous question. Instead of a
// fixed rotation. Have the triangle continously rotate in place in a
// counter clockwise direction. Use the transformVertices function.
void problem8()
{

    static float angle = 0.0f;

    angle += 1.0f;


} // end Problem8


// Implement and animation that makes the triangle continuously orbit in a clockwise
// direction around the origin at a distance of 400 pixels use the transformVertices function.
void problem9()
{


} // end Problem9



// Accomplish the same orbit as the previous question with the exception that
// the triangle always points at the top of the screen while it orbits. Use
// the transformVertices function.
void problem10() {



} // end Problem10


// Create and animation that causes the triangle to continously bounce from one
// side of the screen to the other. You can get the width and/or height of the
// screen in pixels by using glutGet( GLUT_WINDOW_WIDTH ) and
// glutGet( GLUT_WINDOW_HEIGHT ). If you want to get fancy, you can move the
// triangle with a "velocity" vector and reflect the velocity vector each
// time the triangle hits the edge of the screen.
void problem11()
{



} // end Problem11


/**
* Acts as the display function for the window.
*/
static void RenderSceneCB()
{
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Drawn the reference lines
    glBegin(GL_LINES);
        glColor4f(1, 0, 0, 1);
        glVertex3d(-1, 0, 0);
        glVertex3d(1, 0, 0);

        glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
        glVertex3d(0, -1, 0);
        glVertex3d(0, 1, 0);
    glEnd();

    switch (displayedProblem) {

        case 1:
            problem1();
            break;
        case 2:
            problem2();
            break;
        case 3:
            problem3();
            break;
        case 4:
            problem4();
            break;
        case 5:
            problem5();
            break;
        case 6:
            problem6();
            break;
        case 7:
            problem7();
            break;
        case 8:
            problem8();
            break;
        case 9:
            problem9();
            break;
        case 10:
            problem10();
            break;
        case 11:
            problem11();
            break;
        default:
            std::cout << "Invalid displayProblem" << std::endl;
    }

    glutSwapBuffers();
} // end RenderSceneCB



static void ResizeCB(int width, int height)
{
    // Reset viewport limits for full window rendering each time the window is resized.
    // This function is called when the program starts up and each time the window is
    // resized.

    // Size the color buffer to match the window size.
    // Signal the operating system to re-render the window
    glutPostRedisplay();

} // end ResizeCB


// Responds to 'f' and escape keys. 'f' key allows
// toggling full screen viewing. Escape key ends the
// program. Allows lights to be individually turned on and off.
static void KeyboardCB(unsigned char key, int x, int y)
{
    switch (key) {

        case('f') : case('F') : // 'f' key to toggle full screen
            glutFullScreenToggle();
            break;
        case(27) : // Escape key
            glutLeaveMainLoop();
            break;
        default:
            std::cout << key << " key pressed." << std::endl;
    }
    glutPostRedisplay();

} // end KeyboardCB


// Responds to presses of the arrow keys
static void SpecialKeysCB(int key, int x, int y)
{
    switch (key) {

        case(GLUT_KEY_RIGHT) :

            break;
        case(GLUT_KEY_LEFT) :

            break;
        default:
            std::cout << key << " key pressed." << std::endl;
    }
    glutPostRedisplay();

} // end SpecialKeysCB

// Register as the "idle" function to have the screen continously
// repainted. Due to software rendering, the frame rate will not
// be fast enough to support motion simulation
static void animate()
{
    glutPostRedisplay();

} // end animate

void problemMenu(int value)
{

    if (value != 0) {
        displayedProblem = value;
        std::ostringstream title;
        title << "Problem " <<  displayedProblem;
        glutSetWindowTitle((const char*)title.str().c_str());
    }
    else {
        glutLeaveMainLoop();
    }


    // Signal GLUT to call display callback
    glutPostRedisplay();
} // end subMenu1


int main(int argc, char** argv)
{
    // freeGlut and Window initialization ***********************

    // Pass any applicable command line arguments to GLUT. These arguments
    // are platform dependent.
    glutInit(&argc, argv);

    // Set the initial display mode.
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    // Set the initial window size
    glutInitWindowSize(600, 600);

    // Create a window using a string and make it the current window.
    GLuint world_Window = glutCreateWindow("2D Transformations");

    // Indicate to GLUT that the flow of control should return to the program after
    // the window is closed and the GLUTmain loop is exited.
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    // Callback for window redisplay
    glutDisplayFunc(RenderSceneCB);
    glutReshapeFunc(ResizeCB);
    glutKeyboardFunc(KeyboardCB);
    glutSpecialFunc(SpecialKeysCB);
    glutIdleFunc(animate);

    // Create polygon submenu
    int menu1id = glutCreateMenu(problemMenu);
    // Specify menu items and integer identifiers
    glutAddMenuEntry("Problem 1", 1);
    glutAddMenuEntry("Problem 2", 2);
    glutAddMenuEntry("Problem 3", 3);
    glutAddMenuEntry("Problem 4", 4);
    glutAddMenuEntry("Problem 5", 5);
    glutAddMenuEntry("Problem 6", 6);
    glutAddMenuEntry("Problem 7", 7);
    glutAddMenuEntry("Problem 8", 8);
    glutAddMenuEntry("Problem 9", 9);
    glutAddMenuEntry("Problem 10", 10);
    glutAddMenuEntry("Problem 11", 11);
    glutAddMenuEntry("Quit", 0);

    // Attach menu to right mouse button
    glutAttachMenu(GLUT_RIGHT_BUTTON);


    // Set red, green, blue, and alpha to which the color buffer is cleared.
    glClearColor(0.784, 0.784, 1.0, 1.0);

    // Request that the window be made full screen
//    glutFullScreen( );

    // Enter the GLUT main loop. Control will not return until the window is closed.
    glutMainLoop();

    return 0;

} // end main


