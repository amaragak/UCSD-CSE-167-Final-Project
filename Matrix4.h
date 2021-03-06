//
//  Matrix4.h
//  CSE 167 Project 1
//
//  Created by Alex Maragakis on 15/10/2014.
//  Copyright (c) 2014 Gak Industries. All rights reserved.
//

#ifndef __CSE_167_Project_1__Matrix4__
#define __CSE_167_Project_1__Matrix4__

#include <iostream>
#include "Vector3.h"
#include "Vector4.h"
#include "math.h"
#include <GLUT/glut.h>

const double PI = 4.0*atan(1.0);

class Matrix4
{
//Private Variables:
    double m[16];
    GLdouble mGL[16];
    GLfloat mGLf[16];
    
public:
//Constructors
    Matrix4();
    Matrix4( double m0, double m1, double m2, double m3, double m4, double m5,
             double m6, double m7, double m8, double m9, double m10, double m11,
             double m12,double m13, double m14, double m15 );
    Matrix4( double * M);
    
//Initialisation:
    void set(double m0, double m1, double m2, double m3, double m4, double m5,
             double m6, double m7, double m8, double m9, double m10, double m11,
             double m12,double m13, double m14, double m15 );
    
    
//Get Functions:
    double get(int n);
    double get(int r, int c);
    double& operator[] ( const int i );
    
    double * getPointer();
    GLdouble * getGLPointer();
    GLfloat * getGLfloatPointer();
    
//Matrix Arithmetic
    Vector4 mult( Vector4 v );
    Vector4 operator* ( const Vector4& other );
    
    Matrix4 mult( Matrix4 mat );
    Matrix4 operator* ( const Matrix4& other );
    
    Matrix4 transpose();
    
//Make Transformation Matrices:
    void makeXRot(double angle);
    void makeYRot(double angle);
    void makeZRot(double angle);
    void makeAxisRot(Vector3 axis, double angle);

    void makeScale(double scale);
    void makeScale(Vector3 scale);
    void makeScale(Vector4 scale);
    
    void makeTranslation(Vector3 trans);
    
    void makeI();
    
//Print
    void print(char * comment);
};

#endif /* defined(__Computer_Graphics_Project_1__Matrix4__) */


