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

//##############################Define Variables here###########################



struct Point {

    double x, y, z;
    Point(double x1, double y1, double z1)
    {
        x = x1;
        y = y1;
        z = z1;
    }


    void print(){
        cout<<x<<" "<<y<<" "<<z<<endl;
    }

};

struct Matrix{
    double matrix[4][4];
};
struct Vector{
    double vector[4];
};

vector<Point*> points;
//##############################################################################


void myInit (void);
void display(void);
void reshape (int w, int h);
void draw_grid(void);
//##############################Define Prototypes here###########################


int get_zone(int x_0,int y_0, int x_1, int y_1);
void draw_vertex(int x, int y, int zone);
void drawline_midpoint(int x_0,int y_0, int x_1, int y_1, int zone);
void drawline(int x_0,int y_0, int x_1, int y_1);
double degree_to_radian(double theta);

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

Matrix* rotation_z(double theta){
    Matrix* m = (Matrix*)malloc(sizeof(Matrix));
    m->matrix[0][0]=cos(degree_to_radian(theta));
    m->matrix[0][1] = -sin(degree_to_radian(theta));
    m->matrix[0][2] = 0;
    m->matrix[0][3] = 0;

    m->matrix[1][0]=sin(degree_to_radian(theta));
    m->matrix[1][1] = cos(degree_to_radian(theta));
    m->matrix[1][2] = 0;
    m->matrix[1][3] = 0;


    m->matrix[2][0]= 0;
    m->matrix[2][1] = 0;
    m->matrix[2][2] = 1;
    m->matrix[2][3] = 0;


    m->matrix[3][0]= 0;
    m->matrix[3][1] = 0;
    m->matrix[3][2] = 0;
    m->matrix[3][3] = 1;

    return m;
}



Matrix* rotation_y(double theta){
    Matrix* m = (Matrix*)malloc(sizeof(Matrix));
    m->matrix[0][0]=cos(degree_to_radian(theta));
    m->matrix[0][1] = 0;
    m->matrix[0][2] = sin(degree_to_radian(theta));
    m->matrix[0][3] = 0;

    m->matrix[1][0] = 0;
    m->matrix[1][1] = 1;
    m->matrix[1][2] = 0;
    m->matrix[1][3] = 0;


    m->matrix[2][0] = -sin(degree_to_radian(theta));
    m->matrix[2][1] = 0;
    m->matrix[2][2] = cos(degree_to_radian(theta));;
    m->matrix[2][3] = 0;


    m->matrix[3][0]= 0;
    m->matrix[3][1] = 0;
    m->matrix[3][2] = 0;
    m->matrix[3][3] = 1;

    return m;
}

Matrix* rotation_x(double theta){
    Matrix* m = (Matrix*)malloc(sizeof(Matrix));
    m->matrix[0][0]=1;
    m->matrix[0][1] = 0;
    m->matrix[0][2] = 0;
    m->matrix[0][3] = 0;

    m->matrix[1][0] = 0;
    m->matrix[1][1] = cos(degree_to_radian(theta));
    m->matrix[1][2] =  -sin(degree_to_radian(theta));
    m->matrix[1][3] = 0;


    m->matrix[2][0] = 0;
    m->matrix[2][1] = sin(degree_to_radian(theta));
    m->matrix[2][2] = cos(degree_to_radian(theta));
    m->matrix[2][3] = 0;


    m->matrix[3][0]= 0;
    m->matrix[3][1] = 0;
    m->matrix[3][2] = 0;
    m->matrix[3][3] = 1;

    return m;
}

Vector* multiply(Matrix* m, Vector* v){
    Vector* result = (Vector*) malloc(sizeof(Vector));
    for (int i = 0;i<4;i++){
        double sum = 0;
        for(int j = 0;j<4;j++){
            sum+=m->matrix[i][j]*v->vector[j];
        }
        result->vector[i] = sum;
    }
    return result;
}

Vector* point_to_vector(Point* p){
    Vector* result = (Vector*) malloc(sizeof(Vector));
    result->vector[0] = p->x;
    result->vector[1] = p->y;
    result->vector[2] = p->z;
    result->vector[3] = 1;
    return result;
}

Point* vector_to_point(Vector* v){
    Point* p = (Point*)malloc(sizeof(Point));
    p->x = v->vector[0]/v->vector[3];
    p->y = v->vector[1]/v->vector[3];
    p->z = v->vector[2]/v->vector[3];
    return p;
}

Point* create_point(double x, double y, double z){
    Point* p = (Point*)malloc(sizeof(Point));
    p->x=x;
    p->y=y;
    p->z=z;
    return p;
}
Point *rotate(Point* p, int axis, double theta){
    Matrix* m;
    if(axis==0)
        m = rotation_x(theta);
    if(axis==1)
        m = rotation_y(theta);
    if(axis==2)
        m = rotation_z(theta);
    return vector_to_point(multiply(m,point_to_vector(p)));
}
void animate(){

        for(int i =0;i<points.size();i++){
            Point* p1 = points[i];
            p1 = rotate(p1,0,1);
            p1 = rotate(p1,1,1);
            p1 = rotate(p1,2,1);
            points[i] = p1;
            Point* p2 = points[(i+1)%points.size()];
            p2 = rotate(p2,0,1);
            p2 = rotate(p2,1,1);
            p2 = rotate(p2,2,1);
            points[(i+1)%points.size()] = p2;
        }

}
void draw_polygon(vector<Point*> polygon){
    for(int i =0;i<polygon.size();i++){
        Point* p1 = polygon[i];
        Point* p2 = polygon[(i+1)%polygon.size()];
        drawline(p1->x,p1->y,p2->x,p2->y);
    }
}

double get_normal(vector<Point*> polygon){
    Point* p1 = polygon[1];
    Point* p2 = polygon[2];
    Point* p3 = polygon[0];
    return (p2->x-p1->x)*(p3->y-p1->y)-(p3->x-p1->x)*(p2->y-p1->y);
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    draw_grid();

    glBegin(GL_POINTS);
    if (get_normal(points)<0)
    draw_polygon(points);

    glEnd();

    glutSwapBuffers();
}



double degree_to_radian(double theta){
    return theta*3.1416/180.0;
}


void drawline(int x_0,int y_0, int x_1, int y_1){
    if (get_zone(x_0,y_0,x_1,y_1) == 0){
        drawline_midpoint(x_0,y_0,x_1,y_1, 0);
    }
    if (get_zone(x_0,y_0,x_1,y_1) == 1){
        drawline_midpoint(y_0,x_0,y_1,x_1,1);
    }
    if (get_zone(x_0,y_0,x_1,y_1) == 2){
        drawline_midpoint(y_0,-x_0,y_1,-x_1,2);
    }
    if (get_zone(x_0,y_0,x_1,y_1) == 3){
        drawline_midpoint(-x_0,y_0,-x_1,y_1,3);
    }
    if (get_zone(x_0,y_0,x_1,y_1) == 4){
        drawline_midpoint(-x_0,-y_0,-x_1,-y_1,4);
    }
    if (get_zone(x_0,y_0,x_1,y_1) == 5){
        drawline_midpoint(-y_0,-x_0,-y_1,-x_1,5);
    }
    if (get_zone(x_0,y_0,x_1,y_1) == 6){
        drawline_midpoint(-y_0,x_0,-y_1,x_1,6);
    }
    if (get_zone(x_0,y_0,x_1,y_1) == 7){
        drawline_midpoint(x_0,-y_0,x_1,-y_1,7);
    }
}
//midpoint line drawing algorithm for zone 0
void drawline_midpoint(int x_0,int y_0, int x_1, int y_1, int zone){
    int dx = x_1 - x_0;
    int dy = y_1 - y_0;
    int d = 2*dy - dx;
    int de = 2*dy;
    int den = 2*(dy-dx);
    int x,y;
    x= x_0;
    y= y_0;

    draw_vertex(x,y,zone);
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
        draw_vertex(x,y,zone);
    }
}

//draws the pixel using 8 way symmetry
void draw_vertex(int x, int y, int zone){
    if(zone==0)
        glVertex2i(x,y);
    else if(zone==1)
        glVertex2i(y,x);
    else if(zone==2)
        glVertex2i(-y,x);
    else if(zone==3)
        glVertex2i(-x,y);
    else if(zone==4)
        glVertex2i(-x,-y);
    else if(zone==5)
        glVertex2i(-y,-x);
    else if(zone==6)
        glVertex2i(y,-x);
    else if(zone==7)
        glVertex2i(x,-y);

}

// returns the zone of a line
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


void keyboard(unsigned char key, int x, int y)
{
    if(key==' '){

        animate();
        glutPostRedisplay();
    }
}

int main (int argc, char **argv){
    freopen ("input.txt","r",stdin);
    //#############Take Inputs###############
    int n,x,y,z;
    cin>>n;

    for(int i=0;i<n;i++){
        cin>>x>>y>>z;

        Point* p = create_point(x,y,z);
        points.push_back(p);
    }

    for(int i =0;i<points.size();i++){
        points[i]->print();
    }
    cout<<endl;

    //#######################################
    glutInit (&argc, argv); // to initialize the toolkit;
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); // sets the display mode
    glutInitWindowSize (Wi, He); // sets the window size
    glutInitWindowPosition (0, 0); // sets the starting position for the window
    glutCreateWindow ("Line Drawing"); // creates the window and sets the title
    myInit(); // additional initializations as necessary
    glutReshapeFunc(reshape);
    glutDisplayFunc (display);
    glutKeyboardFunc(keyboard);

    glutMainLoop(); // go into a loop until event occurs
    return 0;
}