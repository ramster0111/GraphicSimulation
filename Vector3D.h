/* 
 * File:   Vector3D.h
 * Author: nero
 *
 * Created on October 19, 2010, 8:44 PM
 */

#ifndef VECTOR3D_H
#define VECTOR3D_H
#include <iostream>
#include "Matrix.h"

using namespace std;

class Vector3D {
public:
    double _x;
    double _y;
    double _z;

    //ctors and dtors
    Vector3D(double, double, double);
    Vector3D(const Vector3D&);
    Vector3D();
    ~Vector3D();

    void copyFrom(const Vector3D&);
    double magnitude();
    void normalize();
    double& operator[](int);
    Vector3D operator=(const Vector3D&);
    Vector3D operator+=(const Vector3D&);
    Vector3D operator-=(const Vector3D&);
    Vector3D operator-(void);
    Vector3D matrix_column(int, const Matrix&);
    Vector3D matrix_row(int, const Matrix&);
    friend const Vector3D tripleCrossProduct(const Vector3D&, const Vector3D&, const Vector3D&);
    friend double tripleScalarProduct(const Vector3D&, const Vector3D&, const Vector3D&);
    friend const Vector3D tripleCrossProduct(const Vector3D&, const Vector3D&, const Vector3D&, const Vector3D&);
    friend const Vector3D operator+(const Vector3D&, const Vector3D&);
    friend const Vector3D operator-(const Vector3D&, const Vector3D&);
    friend const Vector3D operator*(const Vector3D&, const double);
    friend const Vector3D operator*(const double, const Vector3D&);
    friend const Vector3D operator*(const Matrix&, const Vector3D&);
    friend const Vector3D operator*(const Vector3D&, const Matrix&);
    friend const Vector3D operator/(const Vector3D&, const double);
    friend double dot(const Vector3D&, const Vector3D&);
    friend const Vector3D cross(const Vector3D&, const Vector3D&);

    friend ostream & operator<<(ostream& ostr, const Vector3D& lhs) {
        ostr << lhs._x << "i + " << lhs._y << "j + " << lhs._z << "k";
        return (ostr);
    }
};

#endif // VECTORS_H
