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
#include <unistd.h>
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
void draw_circle_anime(float cx1,float cy1,float cx2,float cy2,int r);
int get_zone(int dx,int dy);
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
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2i(-320,0);
    glVertex2i(319,0);
    glVertex2i(0,239);
    glVertex2i(0,-240);
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    draw_grid();

    glBegin(GL_POINTS);
    int x1 = -200;
    int y1 = 0;
    int x2 = 200;
    int y2 = 0;
    int r = 50;
    draw_circle_anime(x1,y1,x2,y2,r);

    glEnd();
    glutSwapBuffers();
}


void draw_circle_anime(float cx1,float cy1,float cx2,float cy2,int r){

    float dx1 = 1;
    float dy1 = 3;
    float dx2 = -1;
    float dy2 = -2;
    int maxy =He/2-1 ;
    int miny =-He/2 ;
    int maxx =Wi/2-1 ;
    int minx =-Wi/2 ;
    while (1){

        glClear(GL_COLOR_BUFFER_BIT);
        draw_grid();

        glBegin(GL_POINTS);
        draw_circle_0r(cx1,cy1,r);
        draw_circle_0r(cx2,cy2,r);
        cx1+=dx1;
        cy1+=dy1;
        cx2+=dx2;
        cy2+=dy2;
        if(sqrt((cx1-cx2)*(cx1-cx2)+(cy1-cy2)*(cy1-cy2))<=r*2.0){

            if(cx1>=cx2){
                if(dx1<0)
                    dx1*=-1;
                if(dx2>=0)
                    dx2*=-1;
            } else{
                if(dx1>=0)
                    dx1*=-1;
                if(dx2<0)
                    dx2*=-1;
            }
            if(cy1>=cy2){
                if(dy1<0)
                    dy1*=-1;
                if(dy2>=0)
                    dy2*=-1;
            } else{
                if(dy1>=0)
                    dy1*=-1;
                if(dy2<0)dy2*=-1;
            }
        }

        else{
            if(cy1+r>=maxy){
                dy1*=-1;
            }
            if(cy1-r<=miny){
                dy1*=-1;
            }
            if(cx1+r>=maxx){
                dx1*=-1;
            }
            if(cx1-r<=minx){
                dx1*=-1;
            }
            if(cy2+r>=maxy){
                dy2*=-1;
            }
            if(cy2-r<=miny){
                dy2*=-1;
            }
            if(cx2+r>=maxx){
                dx2*=-1;
            }
            if(cx2-r<=minx){
                dx2*=-1;
            }
        }
        glEnd();
        glutSwapBuffers();
    }

}

void draw_circle_0r(int cx,int cy, int r){
    int d = 5-4*r;
    int x = 0, y = r;
    draw_8way(x, y, cx, cy);
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
        draw_8way(x,y,cx,cy);
    }
}
int get_zone(int dx,int dy){

    if(dx>=0 && dy>=0){
        if (abs(dx)>=abs(dy))
            return 0;
        else
            return 1;
    }
    else if(dx<0 && dy>=0){
        if (abs(dx)>=abs(dy))
            return 3;
        else
            return 2;
    }
    else if(dx<0 && dy<0){
        if (abs(dx)>=abs(dy))
            return 4;
        else
            return 5;
    }
    else if(dx>=0 && dy<0){
        if (abs(dx)>=abs(dy))
            return 7;
        else
            return 6;
    }

}
void draw_8way(int x, int y, int cx,int cy){
    glVertex2i(x+cx,y+cy);

    glVertex2i(-x+cx,y+cy);

    glVertex2i(x+cx,-y+cy);

    glVertex2i(-x+cx,-y+cy);

    glVertex2i(y+cx,x+cy);

    glVertex2i(-y+cx,x+cy);

    glVertex2i(y+cx,-x+cy);

    glVertex2i(-y+cx,-x+cy);
}

int main (int argc, char **argv){
    freopen ("input.txt","r",stdin);
    //#############Take Inputs###############

    //#######################################
    glutInit (&argc, argv); // to initialize the toolkit;
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); // sets the display mode
    glutInitWindowSize (Wi, He); // sets the window size
    glutInitWindowPosition (0, 0); // sets the starting position for the window
    glutCreateWindow ("Circle Drawing"); // creates the window and sets the title
    myInit(); // additional initializations as necessary
    glutReshapeFunc(reshape);
    glutDisplayFunc (display);
    glutMainLoop(); // go into a loop until event occurs
    return 0;
}