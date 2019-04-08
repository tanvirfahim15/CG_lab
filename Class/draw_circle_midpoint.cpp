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



//##############################################################################


void myInit (void);
void display(void);
void reshape (int w, int h);
void draw_grid(void);
//##############################Define Prototypes here###########################
void draw_circle_0r(int cx,int cy, int r);
void draw_8way(int x, int y, int cx,int cy);

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

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    draw_grid();

    glBegin(GL_POINTS);

    draw_circle_0r(0,0,20);
    glEnd();
    glFlush();
}

void draw_circle_0r(int cx,int cy, int r){
    int d = 5-4*r;
    int x = 0, y = r;
    draw_8way(x, y, cx, cy);
    cout<<x<<" "<<y<<" "<<d<<endl;
    while (x<y){
        if(d<0){
            d+=(8*x+12);
            x++;
        }
        else{
            d+=(8*x-8*y+20);
            x++;
            y--;
        }
        cout<<x<<" "<<y<<" "<<d<<endl;
        draw_8way(x,y,cx,cy);
    }
}

void draw_8way(int x, int y, int cx,int cy){
    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(x+cx,y+cy);

    glColor3f(0.0, 1.0, 0.0);
    glVertex2i(-x+cx,y+cy);

    glColor3f(0.0, 0.0, 1.0);
    glVertex2i(x+cx,-y+cy);

    glColor3f(0.5, 0.5, 0.5);
    glVertex2i(-x+cx,-y+cy);

    glColor3f(1.0, 1.0, 1.0);
    glVertex2i(y+cx,x+cy);

    glColor3f(1.0, 0.0, 1.0);
    glVertex2i(-y+cx,x+cy);

    glColor3f(0.0, 1.0, 1.0);
    glVertex2i(y+cx,-x+cy);

    glColor3f(1.0, 1.0, 0.0);
    glVertex2i(-y+cx,-x+cy);
}

int main (int argc, char **argv){
    freopen ("input.txt","r",stdin);
    //#############Take Inputs###############

    //#######################################
    glutInit (&argc, argv); // to initialize the toolkit;
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // sets the display mode
    glutInitWindowSize (Wi, He); // sets the window size
    glutInitWindowPosition (0, 0); // sets the starting position for the window
    glutCreateWindow ("Circle Drawing"); // creates the window and sets the title
    myInit(); // additional initializations as necessary
    glutReshapeFunc(reshape);
    glutDisplayFunc (display);
    glutMainLoop(); // go into a loop until event occurs
    return 0;
}