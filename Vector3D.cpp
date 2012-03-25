#include <math.h>
#include "Vector3D.h"

Vector3D::Vector3D(double x, double y, double z) : _x(x), _y(y), _z(z) {

}

Vector3D::Vector3D(const Vector3D& src) {
    copyFrom(src);
}

Vector3D::Vector3D() : _x(0), _y(0), _z(0) {

}

Vector3D::~Vector3D() {

}

void Vector3D::copyFrom(const Vector3D& src) {
    this->_x = src._x;
    this->_y = src._y;
    this->_z = src._z;
}

Vector3D Vector3D::operator =(const Vector3D& rhs) {
    if (this == &rhs)
        return (*this);
    copyFrom(rhs);
    return (*this);
}

Vector3D Vector3D::operator+=(const Vector3D& rhs) {
    this->_x += rhs._x;
    this->_y += rhs._y;
    this->_z += rhs._z;
    return (*this);
}

Vector3D Vector3D::operator-=(const Vector3D& rhs) {
    this->_x -= rhs._x;
    this->_y -= rhs._y;
    this->_z -= rhs._z;
    return (*this);
}

double& Vector3D::operator [](int index) {
    switch (index) {
        case 0:
            return _x;
            break;
        case 1:
            return _y;
            break;
        case 2:
            return _z;
            break;
    }
    return _x;
}

Vector3D Vector3D::operator-(void) {
    Vector3D negated(-(this->_x), -(this->_y), -(this->_z));
    return (negated);
}

const Vector3D operator+(const Vector3D& lhs, const Vector3D& rhs) {

    Vector3D a;
    a._x = lhs._x + rhs._x;
    a._y = lhs._y + rhs._y;
    a._z = lhs._z + rhs._z;
    return (a);
}

const Vector3D operator-(const Vector3D& lhs, const Vector3D& rhs) {
    Vector3D a;
    a._x = lhs._x - rhs._x;
    a._y = lhs._y - rhs._y;
    a._z = lhs._z - rhs._z;
    return (a);
}

const Vector3D operator*(const Vector3D& lhs, const double rhs) {

    Vector3D a;
    a._x = lhs._x * rhs;
    a._y = lhs._y * rhs;
    a._z = lhs._z * rhs;
    return (a);
}

const Vector3D operator*(const double rhs, const Vector3D& lhs) {

    Vector3D a;
    a._x = lhs._x * rhs;
    a._y = lhs._y * rhs;
    a._z = lhs._z * rhs;
    return (a);
}

const Vector3D operator*(const Matrix& lhs, const Vector3D& rhs) {
    Vector3D a;
    a._x = lhs.mat[0][0] * rhs._x + lhs.mat[0][1] * rhs._y + lhs.mat[0][2] * rhs._z;
    a._y = lhs.mat[1][0] * rhs._x + lhs.mat[1][1] * rhs._y + lhs.mat[1][2] * rhs._z;
    a._z = lhs.mat[2][0] * rhs._x + lhs.mat[2][1] * rhs._y + lhs.mat[2][2] * rhs._z;
    return (a);
}

const Vector3D operator*(const Vector3D& rhs, const Matrix& lhs) {
    Vector3D a;
    a._x = lhs.mat[0][0] * rhs._x + lhs.mat[1][0] * rhs._y + lhs.mat[2][0] * rhs._z;
    a._y = lhs.mat[0][1] * rhs._x + lhs.mat[1][1] * rhs._y + lhs.mat[2][1] * rhs._z;
    a._z = lhs.mat[0][2] * rhs._x + lhs.mat[1][2] * rhs._y + lhs.mat[2][2] * rhs._z;
    return (a);
}

const Vector3D operator/(const Vector3D& lhs, const double rhs) {

    Vector3D a;
    a._x = lhs._x / rhs;
    a._y = lhs._y / rhs;
    a._z = lhs._z / rhs;
    return (a);
}

double dot(const Vector3D& lhs, const Vector3D& rhs) {

    return (lhs._x * rhs._x + lhs._y * rhs._y + lhs._z * rhs._z);
}

const Vector3D cross(const Vector3D& lhs, const Vector3D& rhs) {
    Vector3D a;
    a._x = lhs._y * rhs._z - lhs._z * rhs._y;
    a._y = lhs._z * rhs._x - lhs._x * rhs._z;
    a._z = lhs._x * rhs._y - lhs._y * rhs._x;
    return (a);
}

const Vector3D tripleCrossProduct(const Vector3D& first, const Vector3D& second, const Vector3D& third) {
    Vector3D a = cross(first, second);
    Vector3D b = cross(a, third);
    return (b);
}

double tripleScalarProduct(const Vector3D& first, const Vector3D& second, const Vector3D& third) {
    Vector3D a = cross(first, second);
    double b = dot(a, third);
    return (b);
}

const Vector3D tripleCrossProduct(const Vector3D& first, const Vector3D& second, const Vector3D& third, const Vector3D& fourth) {
    Vector3D a = cross(first, second);
    Vector3D b = cross(third, fourth);
    Vector3D c = cross(a, b);
    return (c);
}

double Vector3D::magnitude() {
    return (sqrt(_x * _x + _y * _y + _z * _z));
}

void Vector3D::normalize() {
    double m;
    m = this->magnitude();
    this->_x /= m;
    this->_y /= m;
    this->_z /= m;
}

Vector3D Vector3D::matrix_column(int index, const Matrix& matrix) {
    Vector3D temp;
    if (matrix._column >= index) {
        temp._x = matrix.mat[0][index];
        temp._y = matrix.mat[1][index];
        temp._z = matrix.mat[2][index];
    } else
        cout << "Fucked" << endl;
    return temp;
}

Vector3D Vector3D::matrix_row(int index, const Matrix& matrix) {
    Vector3D temp;
    if (matrix._row >= index) {
        temp._x = matrix.mat[index][0];
        temp._y = matrix.mat[index][1];
        temp._z = matrix.mat[index][2];
    } else
        cout << "Fucked" << endl;
    return temp;
}
