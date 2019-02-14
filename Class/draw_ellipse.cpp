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

void draw_ellipes_clockwise(int cx,int cy, int a, int b);
void draw_ellipes_counterclockwise(int cx,int cy, int a, int b);
void draw4way(int x,int y,int cx,int cy);
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

void draw_ellipes_clockwise(int cx,int cy, int a, int b){
    int d = 4*b*b-a*a*(4*b-1);
    int x = 0,y = b;
    draw4way(x,y,cx,cy);
    while(a*a*(4*y-2)>4*b*b*(x+1)){
        if (d<0){
            d+= 4*b*b*(2*x+3);
            x++;
        }
        else{
            d+=4*b*b*(2*x+3)-4*a*a*(2*y-2);
            x++;
            y--;
        }
        draw4way(x,y,cx,cy);
    }
    while (y>0){
        if(d<0){
            d+=4*(a*a*(3-2*y)+b*b*(2*x+2));
            x++;
            y--;
        } else{
            d+=4*a*a*(3-2*y);
            y--;
        }
        draw4way(x,y,cx,cy);
    }
}

void draw_ellipes_counterclockwise(int cx,int cy, int a, int b) {
    int d = 4*a*a-b*b*(4*a-1);
    int x = a,y = 0;
    draw4way(x,y,cx,cy);
    while(4*a*a*(y+1)<b*b*(4*x-2)){
        if (d<0){
            d+= 4*a*a*(2*y+3);
            y++;
        }
        else{
            d+=4*a*a*(2*y+3)+4*b*b*(2-2*x);
            x--;
            y++;
        }
        draw4way(x,y,cx,cy);
    }
    while (x>0){
        if(d<0){
            d+=4*b*b*(3-2*x)+4*a*a*(2*y+2);
            x--;
            y++;
        } else{
            d+=4*b*b*(3-2*x);
            x--;
        }
        draw4way(x,y,cx,cy);
    }

}

void draw4way(int x,int y,int cx,int cy){
    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(x+cx,y+cy);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2i(-x+cx,y+cy);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2i(x+cx,-y+cy);
    glColor3f(1.0, 0.0, 1.0);
    glVertex2i(-x+cx,-y+cy);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    draw_grid();

    glBegin(GL_POINTS);
    draw_ellipes_counterclockwise(0,0,200,100);
    glEnd();
    glFlush();
}


int main (int argc, char **argv){
    freopen ("input.txt","r",stdin);
    //#############Take Inputs###############

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