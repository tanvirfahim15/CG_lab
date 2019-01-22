#ifdef _WIN32
#include <windows.h>
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"GLUT32.lib")
#pragma warning(disable:4244)
#pragma warning(disable:4305)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>
#include<cstdio>
#include<iostream>
#include <iostream>
using namespace std;

int Wi=640, He=480;

//##############################Define Variables here###########################

int x_0,x_1,y_0,y_1;

//##############################################################################


void myInit (void);
void display(void);
void reshape (int w, int h);
void draw_grid(void);
//##############################Define Prototypes here###########################
void draw_line_math(int x_0,int y_0, int x_1, int y_1);


//##############################################################################

void myInit (void){
    glClearColor(0.0, 0.0, 0.0,1.0);
}

void reshape (int w, int h){
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D (-Wi/2, Wi/2-1, -He/2, He/2-1); // size of projection plane (origin at the center)
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}

void draw_grid(void){
    glBegin(GL_LINES);
    glVertex2i(-320,0);
    glVertex2i(319,0);
    glVertex2i(0,239);
    glVertex2i(0,-240);
    glEnd();
}

void draw_line_math(int x_0,int y_0, int x_1, int y_1){


    double m = ((double)(y_1-y_0))/(x_1-x_0);
    if(x_0>x_1){
        swap(x_0,x_1);
        swap(y_0,y_1);
    }
    double y = y_0;
    for(int x = x_0;x<=x_1;x++){
        glVertex2i(x, (int)y);
        y += m;
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    draw_grid();

    glBegin(GL_POINTS);
    draw_line_math(x_0,y_0,x_1,y_1);
    glEnd();
    glFlush();
}


int main (int argc, char **argv){
    freopen ("input.txt","r",stdin);
    //#############Take Inputs###############
    cin>>x_0>>y_0>>x_1>>y_1;
    //#######################################
    glutInit (&argc, argv); // to initialize the toolkit;
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // sets the display mode
    glutInitWindowSize (Wi, He); // sets the window size
    glutInitWindowPosition (0, 0); // sets the starting position for the window
    glutCreateWindow ("Line Drawing"); // creates the window and sets the title
    myInit(); // additional initializations as necessary
    glutReshapeFunc(reshape);
    glutDisplayFunc (display);
    glutMainLoop(); // go into a loop until event occurs
    return 0;
}