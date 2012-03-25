#include "Matrix.h"
#include <iostream>
#include <math.h>

Matrix::Matrix(int row, int column) : _row(row), _column(column) {
    mat = new double*[_row];
    for (int i = 0; i < _row; i++)
        mat[i] = new double[_column];

    for (int k = 0; k < _row; k++) {
        for (int j = 0; j < _column; j++) {
            if (k == j)
                mat[k][j] = 1;
            else
                mat[k][j] = 0;
        }

    }

}

Matrix::Matrix(int row, int inColumn, double *inMat) : _row(row), _column(inColumn) {
    mat = new double*[_row];
    for (int i = 0; i < _row; i++)
        mat[i] = new double[_column];

    for (int i = 0; i < _row; i++)
        for (int j = 0; j < _column; j++)
            mat[i][j] = *(inMat + i * _column + j);
}

Matrix::Matrix(const Matrix& src) {

    copyFrom(src);
}

Matrix::Matrix() : _row(4), _column(4) {
    for (int i = 0; i < _row; i++)
        mat[i] = new double[_column];

    for (int k = 0; k < _row; k++) {
        for (int j = 0; j < _column; j++) {
            if (k == j)
                mat[k][j] = 1;
            else
                mat[k][j] = 0;
        }
    }

}

Matrix::~Matrix() {
    for (int i = 0; i < _column; i++)
        delete[] mat[i];

    delete[] mat;

}

void Matrix::copyFrom(const Matrix& src) {
    _row = src._row;
    _column = src._column;

    int i, j;
    mat = new double*[_row];
    for (i = 0; i < _row; i++)
        mat[i] = new double[_column];

    for (i = 0; i < _row; i++)
        for (j = 0; j < _column; j++)
            mat[i][j] = src.mat[i][j];

}

void Matrix::multConstant(int k) {
    for (int i = 0; i < _row; i++)
        for (int j = 0; j < _column; j++)
            mat[i][j] = mat[i][j] * k;


}

Matrix& Matrix::operator =(const Matrix& rhs) {
    if (this == &rhs)
        return (*this);


    for (int i = 0; i < _column; i++)
        delete[] mat[i];

    delete[] mat;

    copyFrom(rhs);

    return (*this);
}

const Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
    if ((lhs._row != rhs._row) || (lhs._column != rhs._column)) {
        std::cout << "Incompatible matrices for addition";
        return lhs;
    }

    Matrix a(lhs._row, lhs._column);
    for (int i = 0; i < lhs._row; i++)
        for (int j = 0; j < lhs._column; j++)
            a.mat[i][j] = lhs.mat[i][j] + rhs.mat[i][j];

    return (a);
}

const Matrix operator-(const Matrix& lhs, const Matrix& rhs) {
    if ((lhs._row != rhs._row) || (lhs._column != rhs._column)) {
        std::cout << "Incompatible matrices for addition";
        return lhs;
    }

    Matrix a(lhs._row, lhs._column);
    for (int i = 0; i < lhs._row; i++)
        for (int j = 0; j < lhs._column; j++)
            a.mat[i][j] = lhs.mat[i][j] - rhs.mat[i][j];

    return (a);
}

const Matrix operator*(const Matrix& lhs, const Matrix& rhs) {

    if (lhs._column != rhs._row) {
        std::cout << "Incompatible matrices for addition";
        return lhs;
    }

    Matrix a(lhs._row, rhs._column);
    for (int i = 0; i < lhs._row; i++) {
        for (int j = 0; j < rhs._column; j++) {
            double sum = 0;
            for (int k = 0; k < rhs._column; k++) {
                sum += lhs.mat[i][k] * rhs.mat[k][j];
            }
            a.mat[i][j] = sum;
        }

    }
    return (a);
}

void Matrix::makeIdentity() {
    for (int i = 0; i < _row; i++) {
        for (int j = 0; j < _column; j++) {
            if (i == j)
                mat[i][j] = 1;
            else
                mat[i][j] = 0;

        }
    }

}

void Matrix::show() {
    for (int i = 0; i < _row; i++) {
        for (int j = 0; j < _column; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Matrix::transpose() {
    double temp;
    for (int i = 0; i < _row; i++)
        for (int j = 0; j < _column; j++) {
            temp = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = temp;
        }

}

const Matrix& inverse(const Matrix& lhs) {
    Matrix m(4, 4);
    double a, b, c, d, e, f, det;
    int ri, ci;


    a = lhs.mat[2][2] * lhs.mat[3][3] - lhs.mat[3][2] * lhs.mat[2][3];
    b = lhs.mat[1][2] * lhs.mat[3][3] - lhs.mat[3][2] * lhs.mat[1][3];
    c = lhs.mat[1][2] * lhs.mat[2][3] - lhs.mat[2][2] * lhs.mat[1][3];
    d = lhs.mat[0][2] * lhs.mat[3][3] - lhs.mat[3][2] * lhs.mat[0][3];
    e = lhs.mat[0][2] * lhs.mat[2][3] - lhs.mat[2][2] * lhs.mat[0][3];
    f = lhs.mat[0][2] * lhs.mat[1][3] - lhs.mat[1][2] * lhs.mat[0][3];

    m.mat[0][0] = lhs.mat[1][1] * a - lhs.mat[2][1] * b + lhs.mat[3][1] * c;
    m.mat[1][0] = lhs.mat[2][1] * d - lhs.mat[0][1] * a - lhs.mat[3][1] * e;
    m.mat[2][0] = lhs.mat[0][1] * b - lhs.mat[1][1] * d + lhs.mat[3][1] * f;
    m.mat[3][0] = lhs.mat[1][1] * e - lhs.mat[0][1] * c - lhs.mat[2][1] * f;

    m.mat[0][1] = lhs.mat[2][0] * b - lhs.mat[1][0] * a - lhs.mat[3][0] * c;
    m.mat[1][1] = lhs.mat[0][0] * a - lhs.mat[2][0] * d + lhs.mat[3][0] * e;
    m.mat[2][1] = lhs.mat[1][0] * d - lhs.mat[0][0] * b - lhs.mat[3][0] * f;
    m.mat[3][1] = lhs.mat[0][0] * c - lhs.mat[1][0] * e + lhs.mat[2][0] * f;

    a = lhs.mat[2][1] * lhs.mat[3][3] - lhs.mat[3][1] * lhs.mat[2][3];
    b = lhs.mat[1][1] * lhs.mat[3][3] - lhs.mat[3][1] * lhs.mat[1][3];
    c = lhs.mat[1][1] * lhs.mat[2][3] - lhs.mat[2][1] * lhs.mat[1][3];
    d = lhs.mat[0][1] * lhs.mat[3][3] - lhs.mat[3][1] * lhs.mat[0][3];
    e = lhs.mat[0][1] * lhs.mat[2][3] - lhs.mat[2][1] * lhs.mat[0][3];
    f = lhs.mat[0][1] * lhs.mat[1][3] - lhs.mat[1][1] * lhs.mat[0][3];

    m.mat[0][2] = lhs.mat[1][0] * a - lhs.mat[2][0] * b + lhs.mat[3][0] * c;
    m.mat[1][2] = lhs.mat[2][0] * d - lhs.mat[0][0] * a - lhs.mat[3][0] * e;
    m.mat[2][2] = lhs.mat[0][0] * b - lhs.mat[1][0] * d + lhs.mat[3][0] * f;
    m.mat[3][2] = lhs.mat[1][0] * e - lhs.mat[0][0] * c - lhs.mat[2][0] * f;

    a = lhs.mat[2][1] * lhs.mat[3][2] - lhs.mat[3][1] * lhs.mat[2][2];
    b = lhs.mat[1][1] * lhs.mat[3][2] - lhs.mat[3][1] * lhs.mat[1][2];
    c = lhs.mat[1][1] * lhs.mat[2][2] - lhs.mat[2][1] * lhs.mat[1][2];
    d = lhs.mat[0][1] * lhs.mat[3][2] - lhs.mat[3][1] * lhs.mat[0][2];
    e = lhs.mat[0][1] * lhs.mat[2][2] - lhs.mat[2][1] * lhs.mat[0][2];
    f = lhs.mat[0][1] * lhs.mat[1][2] - lhs.mat[1][1] * lhs.mat[0][2];

    m.mat[0][3] = lhs.mat[2][0] * b - lhs.mat[1][0] * a - lhs.mat[3][0] * c;
    m.mat[1][3] = lhs.mat[0][0] * a - lhs.mat[2][0] * d + lhs.mat[3][0] * e;
    m.mat[2][3] = lhs.mat[1][0] * d - lhs.mat[0][0] * b - lhs.mat[3][0] * f;
    m.mat[3][3] = lhs.mat[0][0] * c - lhs.mat[1][0] * e + lhs.mat[2][0] * f;

    det = lhs.mat[0][0] * m.mat[0][0] + lhs.mat[1][0] * m.mat[1][0] + lhs.mat[2][0] * m.mat[2][0] + lhs.mat[3][0] * m.mat[3][0];
    if (fabs(det) <= 3.4e-45)
        return (lhs);
    for (ri = 0; ri <= 3; ri++)
        for (ci = 0; ci <= 3; ci++)
            lhs.mat[ri][ci] = m.mat[ci][ri] / det;
    return (lhs);
}

double Matrix::det() {

    double a, b, c, det;

    a = mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1];
    b = mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2];
    c = mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0];

    det = mat[0][0] * a - mat[0][1] * b + mat[0][2] * c;
    return (det);
}
