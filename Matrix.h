/* 
 * File:   Matrix.h
 * Author: nero
 *
 * Created on October 19, 2010, 8:46 PM
 */

#ifndef Matrix_H
#define Matrix_H

#include<iostream>

using namespace std;

class Matrix {
public:
    int _row;
    int _column;
    double **mat;
    void multConstant(int k);
    void makeIdentity();
    //ctors and dtors
    Matrix(int, int);
    Matrix(int, int, double*);
    Matrix(const Matrix&);
    Matrix();

    ~Matrix();

    void copyFrom(const Matrix&);
    double det();
    void show();
    void transpose();
    Matrix & operator=(const Matrix&);
    friend const Matrix operator+(const Matrix&, const Matrix&);
    friend const Matrix operator-(const Matrix&, const Matrix&);
    friend const Matrix operator*(const Matrix&, const Matrix&);
    friend const Matrix& inverse(const Matrix&);
};

#endif //Matrix_H

