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

struct Edge{
    int y,x;
    Edge *next = NULL;
};

struct Edget{
    Edge *head = NULL;
    Edge *tail= NULL;


    void insert(int y,int x){

        Edge * edge = (Edge*)malloc(sizeof(Edge));
        edge->x=x;
        edge->y=y;
        edge->next=NULL;
        if(head==NULL){
            head = edge;
        }

        else if(head->x>x){
            edge->next=head;
            head=edge;
        }
        else{
            Edge* temp = head;
            while (temp->next!=NULL&&temp->next->x<x){
                temp = temp->next;
            }
            edge->next=temp->next;
            temp->next=edge;
        }
    }
    void print(){
        Edge* edge = head;
        while(edge!=NULL){
            cout<<edge->y<<" "<<edge->x<<endl;
            edge = edge->next;
        }
    }
};
vector<Edget*> edgeTable;
vector<Point> points;
vector<int> counts;
//##############################################################################


void myInit (void){
    glClearColor(0.0, 0.0, 0.0,1.0);
}

void reshape (int w, int h){
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    //gluOrtho2D (-Wi/2, Wi/2-1, -He/2, He/2-1); // size of projection plane (origin at the center)
    gluOrtho2D (-5, 74, -5, 54);
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
        Edge* edge = edgeTable[mapy(y)]->head;

        for(int x = minx;x<=maxx;x++){
            while (edge!=NULL&&edge->x==x){
                par = !par;
                edge = edge->next;
            }
            if(par){
                glVertex2i(x,y);
            }
        }
    }
    glEnd();
    glPointSize(5);
    glBegin(GL_POINTS);

    for(int i=0;i<points.size();i++){
        if(counts[i]==2){
            glColor3f(0.0, 1.0, 0.0);

        }
        else if(counts[i]==1){
            glColor3f(1.0, 0.0, 0.0);

        } else{
            glColor3f(0.0, 0.0, 1.0);

        }
        glVertex2i(points[i].x,points[i].y);
    }


    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(1);
    glBegin(GL_POINTS);


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


    vector<Line*> lines;
    int n ,x,y;
    cin>>n;

    for (int i=0;i<n;i++){
        cin>>x>>y;
        if(x>maxx||x<miny||y>maxy||y<miny){
            cout<<"Pixel out of window"<<endl;
        }
        Point p(x,y);
        points.push_back(p);
        counts.push_back(0);
    }

    for(int i =0;i<points.size();i++){
        lines.push_back(createLine(points[i],points[(i+1)%n]));
        if(points[i].y==points[(i+1)%n].y)continue;
        if(points[i].y==lines[i]->p1.y){
            counts[i]++;
        } else{
            counts[(i+1)%n]++;
        }
    }



    sortLines(&lines);

    for(int i=0;i<500;i++){
        Edget *edget = (Edget*)malloc(sizeof(Edget));
        edget->head =NULL;
        edget->tail =NULL;
        edgeTable.push_back(edget);
    }

    for(int i=0;i<lines.size();i++){
        if(lines[i]->p1.y==lines[i]->p2.y)continue;

        float m_inv = get_m_inv(lines[i]->p1,lines[i]->p2);
        float x = (float)lines[i]->p1.x;
        for (int y = lines[i]->p1.y;y<lines[i]->p2.y;y++){
            edgeTable[mapy(y)]->insert(y,x);
            x+=m_inv;
        }
    }

    for(int i=1;i<20;i++){
        cout<<i<<": "<<endl;
        edgeTable[i-miny]->print();
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