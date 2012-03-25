/* 
 * File:   Triangle.h
 * Author: nero
 *
 * Created on October 19, 2010, 8:44 PM
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "Vector3D.h"

using namespace std;

class Vertex {
public:
    Vector3D normal;
    Vector3D position_vector;
    double textureCoordinates[2];

    //ctors and dtors
    Vertex();
    Vertex(Vertex&);
    Vertex(float x, float y, float z);
    Vertex(Vector3D&, Vector3D&);
    Vertex(Vector3D&, Vector3D&, double, double);
    ~Vertex();
    Vertex & operator=(const Vertex& rhs);

};

class Triangle {
public:
    Vertex a;
    Vertex b;
    Vertex c;
    Vector3D ab;
    Vector3D bc;
    Vector3D ca;

    bool upperBound;
    bool lowerBound;

    Vector3D abNormal;
    Vector3D acNormal;
    Vector3D Normal;

    double beta1, gamma1, gamma3, delta1;
    double hUpper, hLower;
    Vector3D lowerOne, lowerTwo, lowerThree;
    Vector3D upperOne, upperTwo, upperThree;

    Triangle(void);
    Triangle(Vertex _a, Vertex _b, Vertex _c);
    Triangle & operator=(const Triangle&);
    Triangle(const Triangle&);
    ~Triangle(void);
    bool isValidPoint(Vector3D&);
    void draw();
    void move(Vector3D, double);
};

class Object {
public:
    vector<Triangle> memberTriangles; //temporary structure to hold the triangular mesh.
    //to be replaced by a structure similiar to box structure
    //used in 3D-Boolean Project.

    void copyFrom(const Object&);
    void draw();
    Object();
    ~Object(void);
    Object(const Object&);
    Object & operator=(const Object&);
};

#endif // OBJECT_H

