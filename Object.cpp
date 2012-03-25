
#include "Object.h"
#include "Vector3D.h"
#include <cmath>
#include <iostream>

using namespace std;

void quadraticSolver(double coeff[3], double out[2], int &length) {
    double temp = coeff[1] * coeff[1] - 4 * coeff[0] * coeff[2];
    if (temp < 0) {
        length = 0;
        return;
    }

    if (temp == 0) {
        length = 1;
        out[0] = -coeff[1] / (2 * coeff[0]);
        out[1] = -coeff[1] / (2 * coeff[0]);
        return;
    } else {
        length = 2;
        out[0] = (-coeff[1] + sqrt(temp)) / (2 * coeff[0]);
        out[1] = (-coeff[1] - sqrt(temp)) / (2 * coeff[0]);
        return;
    }

}

Triangle::Triangle(void) {

}

Triangle::Triangle(Vertex _a, Vertex _b, Vertex _c) : a(_a), b(_b), c(_c), hUpper(0), hLower(0) {
    Vector3D zero(0, 0, 0);
    this->ab = b.position_vector - a.position_vector;
    this->bc = c.position_vector - b.position_vector;
    this->ca = a.position_vector - c.position_vector;
    this->Normal = cross(ab, bc);
    this->abNormal = b.normal - a.normal;
    this->acNormal = c.normal - a.normal;
    this->beta1 = tripleScalarProduct(-(a.normal), ab, -(ca));
    this->gamma1 = tripleScalarProduct(-(a.normal), b.normal, -(ca));
    this->gamma3 = tripleScalarProduct(-(a.normal), ab, c.normal);
    this->delta1 = tripleScalarProduct(-(a.normal), b.normal, c.normal);

    Vector3D nab(cross(a.normal, b.normal));
    Vector3D nac(cross(a.normal, c.normal));
    if ((nab.magnitude() <= 0.001) && (nab.magnitude() >= -0.001) && (nac.magnitude() <= 0.001) && (nac.magnitude() >= -0.001)) {
        upperBound = false;
        lowerBound = false;
    } else {
        double A, B, C, D, E, F, G;
        A = tripleScalarProduct(-(ab), -(bc), c.normal);
        B = tripleScalarProduct(ca, -(bc), -(acNormal));
        C = tripleScalarProduct(ca, -(bc), b.normal - c.normal);
        D = tripleScalarProduct(ca, -(bc), c.normal) + tripleScalarProduct(-(acNormal), -(bc), c.normal);
        E = tripleScalarProduct(-(acNormal), b.normal - c.normal, c.normal);
        F = tripleScalarProduct(ca, -(bc), -(acNormal));
        G = tripleScalarProduct(-(abNormal), -(bc), b.normal - c.normal);
        // t0,t1 = 0,0
        double h[2];
        double coeff[3] = {E, D, A};
        int l = 0;

        if (E == 0) {
            h[0] = -A / D;
            h[1] = h[0];
        } else {
            quadraticSolver(coeff, h, l);
        }

        int l1 = 0;
        double h1[2];
        double coeff1[3] = {E, (D + F), (A + B)};

        if (E == 0) {
            h1[0] = -(A + B) / (D + F);
            h1[1] = h1[0];
        } else {
            quadraticSolver(coeff1, h1, l1);
        }

        int l2 = 0;
        double h2[2];
        double coeff2[3] = {E, (D + G), (A + C)};

        if (E == 0) {
            h2[0] = -(A + C) / (D + G);
            h2[1] = h2[0];
        } else {
            quadraticSolver(coeff2, h2, l2);
        }

        vector<double> minPositive, minNegative;

        for (int i = 0; i < 2; i++) {
            if (h[i] <= 0.0)
                minNegative.push_back(h[i]);
            else
                minPositive.push_back(h[i]);

            if (h1[i] <= 0.0)
                minNegative.push_back(h1[i]);
            else
                minPositive.push_back(h1[i]);

            if (h2[i] <= 0.0)
                minNegative.push_back(h2[i]);
            else
                minPositive.push_back(h2[i]);

        }


        if (minNegative.size() == 0)lowerBound = false;
        else {
            lowerBound = true;
            hLower = minNegative[0];
            for (unsigned int i = 1; i < minNegative.size(); i++) {
                if (minNegative[i] > hLower)
                    hLower = minNegative[i];
            }
        }

        if (minPositive.size() == 0)upperBound = false;
        else {
            upperBound = true;
            hUpper = minPositive[0];
            for (unsigned int i = 1; i < minPositive.size(); i++) {
                if (minPositive[i] < hUpper)
                    hUpper = minPositive[i];
            }
        }

        if (lowerBound) {
            lowerOne = 1 * a.position_vector + 0.97 * hLower * a.normal;
            lowerTwo = 1 * b.position_vector + 0.97 * hLower * b.normal;
            lowerThree = 1 * c.position_vector + 0.97 * hLower * c.normal;
        }
        if (upperBound) {
            upperOne = 1 * a.position_vector + 0.97 * hUpper * a.normal;
            upperTwo = 1 * b.position_vector + 0.97 * hUpper * b.normal;
            upperThree = 1 * c.position_vector + 0.97 * hUpper * c.normal;

        }
    }
    //cout<<"UpperBound : "<<hUpper<<upperBound<<endl;
    //cout<<"LowerBound : "<<hLower<<lowerBound<<endl;

}

Triangle::~Triangle(void) {

}

void Triangle::move(Vector3D force, double magnitude) {
    this->a.position_vector = this->a.position_vector - magnitude*force;
    this->b.position_vector = this->b.position_vector - magnitude*force;
    this->c.position_vector = this->c.position_vector - magnitude*force;
}

Triangle& Triangle::operator =(const Triangle& rhs) {
    this->a = rhs.a;
    this->b = rhs.b;
    this->c = rhs.c;
    this->ab = rhs.ab;
    this->bc = rhs.bc;
    this->ca = rhs.ca;
    this->Normal = rhs.Normal;
    this->abNormal = rhs.abNormal;
    this->beta1 = rhs.beta1;
    this->acNormal = rhs.acNormal;
    this->delta1 = rhs.delta1;
    this->gamma1 = rhs.gamma1;
    this->gamma3 = rhs.gamma3;
    this->hLower = rhs.hLower;
    this->hUpper = rhs.hUpper;
    this->lowerOne = rhs.lowerOne;
    this->lowerTwo = rhs.lowerTwo;
    this->lowerThree = rhs.lowerThree;
    this->upperOne = rhs.upperOne;
    this->upperTwo = rhs.upperTwo;
    this->upperThree = rhs.upperThree;

    this->upperBound = rhs.upperBound;
    this->lowerBound = rhs.lowerBound;
    return (*this);
}

Triangle::Triangle(const Triangle& rhs) {
    this->a = rhs.a;
    this->b = rhs.b;
    this->c = rhs.c;
    this->ab = rhs.ab;
    this->bc = rhs.bc;
    this->ca = rhs.ca;
    this->Normal = rhs.Normal;
    this->abNormal = rhs.abNormal;
    this->beta1 = rhs.beta1;
    this->acNormal = rhs.acNormal;
    this->delta1 = rhs.delta1;
    this->gamma1 = rhs.gamma1;
    this->gamma3 = rhs.gamma3;
    this->hLower = rhs.hLower;
    this->hUpper = rhs.hUpper;
    this->lowerOne = rhs.lowerOne;
    this->lowerTwo = rhs.lowerTwo;
    this->lowerThree = rhs.lowerThree;
    this->upperOne = rhs.upperOne;
    this->upperTwo = rhs.upperTwo;
    this->upperThree = rhs.upperThree;
    this->upperBound = rhs.upperBound;
    this->lowerBound = rhs.lowerBound;
}

void Triangle::draw() {
    /*
        glBegin(GL_TRIANGLES);
        glVertex3f(a.position_vector._x,a.position_vector._y,a.position_vector._z);
        glVertex3f(b.position_vector._x,b.position_vector._y,b.position_vector._z);
        glVertex3f(c.position_vector._x,c.position_vector._y,c.position_vector._z);
        glEnd();
     */
}

bool Triangle::isValidPoint(Vector3D& p) {
    if (!(lowerBound) && !(upperBound)) {
        return true;
    } else if (lowerBound && upperBound) {

        Vector3D normalLower(cross((lowerOne - lowerTwo), (lowerTwo - lowerThree)));
        normalLower.normalize();
        double chkA = dot(normalLower, (a.position_vector - lowerOne));
        int signALower = (chkA / fabs(chkA));

        double chkP = dot(normalLower, (p - lowerOne));
        int signPLower = (chkP / fabs(chkP));

        Vector3D normalUpper(cross((upperOne - upperTwo), (upperTwo - upperThree)));
        normalUpper.normalize();
        chkA = dot(normalUpper, (a.position_vector - upperOne));
        int signAUpper = (chkA / fabs(chkA));

        chkP = dot(normalUpper, (p - upperOne));
        int signPUpper = (chkP / fabs(chkP));

        return ( ((signALower == signPLower) && (signAUpper == signPUpper)) ? true : false);

    } else if (lowerBound) {
        Vector3D normal(cross((lowerOne - lowerTwo), (lowerTwo - lowerThree)));

        normal.normalize();
        double chkA = dot(normal, (a.position_vector - lowerOne));
        int signA = (chkA / fabs(chkA));

        double chkP = dot(normal, (p - lowerOne));
        int signP = (chkP / fabs(chkP));
        return ( (signA == signP) ? true : false);
    } else {
        Vector3D normal(cross((upperOne - upperTwo), (upperTwo - upperThree)));
        normal.normalize();
        double chkA = dot(normal, (a.position_vector - upperOne));
        int signA = (chkA / fabs(chkA));

        double chkP = dot(normal, (p - upperOne));
        int signP = (chkP / fabs(chkP));

        return ( (signA == signP) ? true : false);

    }
}

Vertex::Vertex() {

}

Vertex::Vertex(Vertex& src) {
    this->normal = src.normal;
    this->position_vector = src.position_vector;
    this->textureCoordinates[0] = src.textureCoordinates[0];
    this->textureCoordinates[1] = src.textureCoordinates[1];
}

Vertex::Vertex(float x, float y, float z) {
    position_vector = *(new Vector3D(x, y, z));
}

Vertex::Vertex(Vector3D& _normal, Vector3D& positionVector, double xTexture, double yTexture)
: normal(_normal)
, position_vector(positionVector) {
    textureCoordinates[0] = xTexture;
    textureCoordinates[1] = yTexture;
}

Vertex::Vertex(Vector3D& _normal, Vector3D& positionVector)
: normal(_normal)
, position_vector(positionVector) {

}

Vertex::~Vertex() {
}

Vertex& Vertex::operator =(const Vertex& rhs) {
    this->normal = rhs.normal;
    this->position_vector = rhs.position_vector;
    this->textureCoordinates[0] = rhs.textureCoordinates[0];
    this->textureCoordinates[1] = rhs.textureCoordinates[1];
    return (*this);
}

void Object::copyFrom(const Object& src) {
    this->memberTriangles = src.memberTriangles;

}

void Object::draw() {
    for (unsigned int i = 0; i < memberTriangles.size(); i++) {
        memberTriangles[i].draw();
    }
}

Object::Object() {

}

Object::~Object(void) {

}

Object::Object(const Object& src) {
    copyFrom(src);
}

Object& Object::operator=(const Object& src) {
    copyFrom(src);
    return (*this);
}
