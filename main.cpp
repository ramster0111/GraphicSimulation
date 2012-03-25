/* 
 * File:   main.cpp
 * Author: nero
 *
 * Created on October 19, 2010, 8:37 PM
 */

#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include <string.h>
#include <cmath>
#include <GL/glut.h>
#include <stdlib.h>

#include "GraphicSimulation.h"

using namespace std;
GraphicsSimulation g("map3.bmp");

int Xangle = 0, Yangle = 0, Zangle = 0;
float Scale = 1.0;
float Xdir, Ydir, Zdir;
int n = 50;
bool typeWired = false;

void enable() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
 //   glEnable(GL_LIGHTING);
}

void keyboardManager(unsigned char key, int x, int y) {
    switch (key) {
        case 27: exit(0);
            break;
        case 'w':Xangle += 1;
            break;
        case 's':Xangle -= 1;
            break;
        case 'a':Yangle -= 1;
            break;
        case 'd':Yangle += 1;
            break;
        case 'l': Xdir += 0.1;
            break;
        case 'k': Zdir -= 0.3;
            if (n > 2)n--;
            break;
        case 'i': Zdir += 0.3;
            if (n < 50)n++;
            break;
        case 'j': Xdir -= 0.1;
            break;
        case 't' :
                if(typeWired)    typeWired = false;
                else typeWired = true;
                break;
    }
    glutPostRedisplay();
}

void mouseManager(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {

                Zangle += 1;
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN) {
                Zangle -= 1;
            }
            break;
        case GLUT_MIDDLE_BUTTON:
            if (state == GLUT_DOWN) {
            }
    }

    glutPostRedisplay();
}

void mouseWheelManager(int button, int dir, int x, int y) {
    if (dir > 0) {
        //      cout<<"Zoom In - "<<dir<<endl;
    }
    if (dir < 0) {
        //    cout<<"Zoom Out - "<<dir<<endl;
    }
    //cout<<"Cursor Position - "<<x<<","<<y<<endl;
    //cout<<"Button Value - "<<button<<endl;
}

void reshapeManager(int w, int h) {
    //cout<<"Reshaped to -"<<w<<","<<h<<endl;
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //gluLookAt(cx, cy, cz, vx, vy, vz, ux, uy, uz);
}

void mouseMotionManager(int x, int y) {
}

void displayManager() {

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(Xdir, Ydir, Zdir);

    glTranslatef(0.0, 0.0, -3.2);
    glRotatef(-1 * Xangle, 1, 0.0, 0.0);
    glRotatef(-1 * Yangle, 0.0, 1.0, 0.0);
    glRotatef(-1 * Zangle, 0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-100, 0, 0);
    glVertex3f(100, 0, 0);
    glColor3f(0, 1.0, 0.0);
    glVertex3f(0, -100, 0);
    glVertex3f(0, 100, 0);
    glColor3f(0, 0.0, 1.0);
    glVertex3f(0, 0, 100);
    glVertex3f(0, 0, -100);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    g.display(n,typeWired);
    glutSwapBuffers();
    glFlush();

}

void idleManager() {
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("An Experimentation Window");
    enable();
    glutDisplayFunc(displayManager);
    glutIdleFunc(idleManager);
    glutKeyboardFunc(keyboardManager);
    glutReshapeFunc(reshapeManager);
    glutMouseFunc(mouseManager);
    glutMotionFunc(mouseMotionManager);
    glutMainLoop();
    return 0;

}


