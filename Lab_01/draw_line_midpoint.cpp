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
int get_zone(int x_0,int y_0, int x_1, int y_1);
void drawline_midpoint_zone0(int x_0,int y_0, int x_1, int y_1);
void drawline_midpoint_zone1(int x_0,int y_0, int x_1, int y_1);
void drawline_midpoint_zone2(int x_0,int y_0, int x_1, int y_1);
void drawline_midpoint_zone3(int x_0,int y_0, int x_1, int y_1);
void drawline_midpoint_zone4(int x_0,int y_0, int x_1, int y_1);
void drawline_midpoint_zone5(int x_0,int y_0, int x_1, int y_1);
void drawline_midpoint_zone6(int x_0,int y_0, int x_1, int y_1);
void drawline_midpoint_zone7(int x_0,int y_0, int x_1, int y_1);
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
    glColor3f(0.2, 0.2, 0.2);

    draw_grid();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);

    if (get_zone(x_0,y_0,x_1,y_1) == 0){
        drawline_midpoint_zone0(x_0,y_0,x_1,y_1);
    }
    if (get_zone(x_0,y_0,x_1,y_1) == 1){
        drawline_midpoint_zone1(x_0,y_0,x_1,y_1);
    }
    if (get_zone(x_0,y_0,x_1,y_1) == 2){
        drawline_midpoint_zone2(x_0,y_0,x_1,y_1);
    }
    if (get_zone(x_0,y_0,x_1,y_1) == 3){
        drawline_midpoint_zone3(x_0,y_0,x_1,y_1);
    }
    if (get_zone(x_0,y_0,x_1,y_1) == 4){
        drawline_midpoint_zone4(x_0,y_0,x_1,y_1);
    }
    if (get_zone(x_0,y_0,x_1,y_1) == 5){
        drawline_midpoint_zone5(x_0,y_0,x_1,y_1);
    }
    if (get_zone(x_0,y_0,x_1,y_1) == 6){
        drawline_midpoint_zone6(x_0,y_0,x_1,y_1);
    }
    if (get_zone(x_0,y_0,x_1,y_1) == 7){
        drawline_midpoint_zone7(x_0,y_0,x_1,y_1);
    }

    glEnd();
    glFlush();
}

void drawline_midpoint_zone0(int x_0,int y_0, int x_1, int y_1){
    int dx = x_1 - x_0;
    int dy = y_1 - y_0;
    int d = 2*dy - dx;
    int de = 2*dy;
    int den = 2*(dy-dx);
    int x,y;
    x= x_0;
    y= y_0;

    glVertex2i(x,y);
    while(x<x_1){
        if(d<0){
            x++;
            d+=de;
        }
        else{
            x++;
            y++;
            d+=den;
        }
        glVertex2i(x,y);
    }
}

void drawline_midpoint_zone1(int x_0,int y_0, int x_1, int y_1){
    int dx = x_1 - x_0;
    int dy = y_1 - y_0;
    int d = dy - 2*dx;
    int dn = -2*dx;
    int den = 2*(dy-dx);
    int x,y;
    x= x_0;
    y= y_0;

    glVertex2i(x,y);
    while(y<y_1){
        if(d<0){
            x++;
            y++;
            d+=den;
        }
        else{
            y++;
            d+=dn;
        }
        glVertex2i(x,y);
    }
}

void drawline_midpoint_zone2(int x_0,int y_0, int x_1, int y_1){
    int dx = x_1 - x_0;
    int dy = y_1 - y_0;
    int d = -dy - 2*dx;
    int dn = -2*dx;
    int dwn = -2*(dy+dx);
    int x,y;
    x= x_0;
    y= y_0;

    glVertex2i(x,y);
    while(y<y_1){
        if(d<0){
            y++;
            d+=dn;
        }
        else{
            x--;
            y++;
            d+=dwn;
        }
        glVertex2i(x,y);
    }
}

void drawline_midpoint_zone3(int x_0,int y_0, int x_1, int y_1){
    int dx = x_1 - x_0;
    int dy = y_1 - y_0;
    int d = -2*dy - dx;
    int dw = -2*dy;
    int dnw = -2*(dy+dx);
    int x,y;
    x= x_0;
    y= y_0;

    glVertex2i(x,y);
    while(x>x_1){
        if(d<0){
            x--;
            y++;
            d+=dnw;
        }
        else{
            x--;
            d+=dw;
        }
        glVertex2i(x,y);
    }
}

void drawline_midpoint_zone4(int x_0,int y_0, int x_1, int y_1){
    int dx = x_1 - x_0;
    int dy = y_1 - y_0;
    int d = -2*dy+dx;
    int dw = -2*dy;
    int dsw = 2*(dx-dy);
    int x,y;
    x= x_0;
    y= y_0;

    glVertex2i(x,y);
    while(x>x_1){
        if(d<0){
            x--;
            d+=dw;
        }
        else{
            x--;
            y--;
            d+=dsw;
        }
        glVertex2i(x,y);
    }
}

void drawline_midpoint_zone5(int x_0,int y_0, int x_1, int y_1){
    int dx = x_1 - x_0;
    int dy = y_1 - y_0;
    int d = -dy+2*dx;
    int ds = 2*dx;
    int dws = 2*(dx-dy);
    int x,y;
    x= x_0;
    y= y_0;

    glVertex2i(x,y);
    while(y>y_1){
        if(d<0){
            y--;
            x--;
            d+=dws;
        }
        else{
            y--;
            d+=ds;
        }
        glVertex2i(x,y);
    }
}

void drawline_midpoint_zone6(int x_0,int y_0, int x_1, int y_1){
    int dx = x_1 - x_0;
    int dy = y_1 - y_0;
    int d = dy+2*dx;
    int de = 2*dx;
    int dse = 2*(dy+dx);
    int x,y;
    x= x_0;
    y= y_0;

    glVertex2i(x,y);
    while(y>y_1){
        if(d<0){
            y--;
            d+=de;
        }
        else{
            x++;
            y--;
            d+=dse;
        }
        glVertex2i(x,y);
    }
}

void drawline_midpoint_zone7(int x_0,int y_0, int x_1, int y_1){
    int dx = x_1 - x_0;
    int dy = y_1 - y_0;
    int d = 2*dy + dx;
    int de = 2*dy;
    int dse = 2*(dy+dx);
    int x,y;
    x= x_0;
    y= y_0;

    glVertex2i(x,y);
    while(x<x_1){
        if(d<0){
            x++;
            y--;
            d+=dse;
        }
        else{
            x++;
            d+=de;
        }
        glVertex2i(x,y);
    }
}


int get_zone(int x_0,int y_0, int x_1, int y_1){
    int dx = x_1 - x_0;
    int dy = y_1 -y_0;
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