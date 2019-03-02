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
#include <vector>
#include <algorithm>
using namespace std;

int Wi=640, He=480;
int minx = -320;
int maxx= 319;
int maxy = 239;
int miny = -240;


void myInit (void);
void display(void);
void reshape (int w, int h);
void draw_grid(void);
//##############################Define Prototypes here###########################
void do_fill();
int mapx(int x);
int mapy(int y);

//##############################################################################

//##############################Define Variables here###########################

struct Point {

    int x, y;
    Point(int x1, int y1)
    {
        x = x1;
        y = y1;
    }


    void print(){
        cout<<x<<" "<<y<<endl;
    }

};
struct Line{

    Point p1,p2;
    void setLine(Point p_1,Point p_2){
        if(p_1.y<p_2.y){
            p1 = p_1;
            p2 = p_2;
            return;
        }
        p1 = p_2;
        p2 = p_1;
    }
    bool operator < (const Line &iData) const
    {
        return p1.y < iData.p1.y;
    }

    void print(){
        cout<<"p1: "<<p1.x<<" "<<p1.y<<endl;
        cout<<"p2: "<<p2.x<<" "<<p2.y<<endl;
        cout<<endl;
    }
};


bool edgeTable[500][700];
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
    do_fill();
    glEnd();
    glFlush();
}

void do_fill(){
    for(int y = miny;y<maxy;y++){
        bool par = false;
        for(int x = minx;x<=maxx;x++){
            if(edgeTable[mapy(y)][mapx(x)]){
                par = !par;
            }
            if(par){
                glVertex2i(x,y);
            }
        }
    }



}

Line * createLine(Point p1,Point p2){
    Line* line = (Line* )malloc(sizeof(Line));
    line->setLine(p1,p2);
    return line;
}
void sortLines(vector<Line*> *lines)
{

    for (int i=1;i<lines->size();i++){
        int j=i;
        while (j>=1){
            if(lines->at(j)->p1.y<lines->at(j-1)->p1.y){
                Line * temp = lines->at(j);
                lines->at(j) = lines->at(j-1);
                lines->at(j-1) = temp;
            }
            j--;
        }
    }

}

float get_m_inv(Point p1,Point p2){
    return ((float)(p1.x-p2.x))/(p1.y-p2.y);
}

int mapx(int x){
    return x-minx;
}
int mapy(int y){
    return y-miny;
}

int main (int argc, char **argv){
    freopen ("input.txt","r",stdin);
    //#############Take Inputs###############

    vector<Point> points;
    vector<Line*> lines;
    int n ,x,y;
    cin>>n;

    for (int i=0;i<n;i++){
        cin>>x>>y;
        Point p(x,y);
        points.push_back(p);
    }
    for(int i =0;i<points.size();i++){
        lines.push_back(createLine(points[i],points[(i+1)%n]));
    }

    sortLines(&lines);


    for(int i= 0;i<500;i++){
        for(int j= 0;j<700;j++){
            edgeTable[i][j] = false;
        }
    }

    for(int i=0;i<lines.size();i++){
        if(lines[i]->p1.y==lines[i]->p2.y)continue;
        float m_inv = get_m_inv(lines[i]->p1,lines[i]->p2);
        float x = (float)lines[i]->p1.x;
        for (int y = lines[i]->p1.y;y<lines[i]->p2.y;y++){

            edgeTable[mapy(y)][mapx((int)x)] = !edgeTable[mapy(y)][mapx((int)x)] ;
            x+=m_inv;
        }
    }





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