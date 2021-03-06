//
//  Matrix4.cpp
//  CSE 167 Project 1
//
//  Created by Alex Maragakis on 15/10/2014.
//  Copyright (c) 2014 Gak Industries. All rights reserved.
//

#include <math.h>
#include "Matrix4.h"

using namespace std;

//****************************************************************
//**
//**   CONSTRUCTORS:
//**
//****************************************************************

Matrix4 :: Matrix4()
{
    for (int i=0; i<16; i++) m[i] = 0;
}

Matrix4 :: Matrix4( double m0, double m1, double m2, double m3, double m4, double m5,
                    double m6, double m7, double m8, double m9, double m10, double m11,
                    double m12,double m13, double m14, double m15 )
{
    m[0] = m0;
    m[1] = m1;
    m[2] = m2;
    m[3] = m3;
    
    m[4] = m4;
    m[5] = m5;
    m[6] = m6;
    m[7] = m7;
    
    m[8] = m8;
    m[9] = m9;
    m[10] = m10;
    m[11] = m11;
    
    m[12] = m12;
    m[13] = m13;
    m[14] = m14;
    m[15] = m15;
    
}

Matrix4 :: Matrix4( double * M)
{
    for (int i=0; i<16; i++) m[i] = M[i];
}

//****************************************************************
//**
//**   INITIALISATION:
//**
//****************************************************************

void Matrix4 :: set(double m0, double m1, double m2, double m3, double m4, double m5,
                    double m6, double m7, double m8, double m9, double m10, double m11,
                    double m12,double m13, double m14, double m15 )
{
    m[0] = m0;
    m[1] = m1;
    m[2] = m2;
    m[3] = m3;
    
    m[4] = m4;
    m[5] = m5;
    m[6] = m6;
    m[7] = m7;
    
    m[8] = m8;
    m[9] = m9;
    m[10] = m10;
    m[11] = m11;
    
    m[12] = m12;
    m[13] = m13;
    m[14] = m14;
    m[15] = m15;
}

//****************************************************************
//**
//**   GET FUNCTIONS:
//**
//****************************************************************

double Matrix4 :: get(int n)
{
    return m[n];
}

double Matrix4 :: get(int r, int c)
{
    return m[r + 4*c];
}

double& Matrix4 :: operator[] ( const int i )
{
    return m[i];
}

double * Matrix4 :: getPointer()
{
    return m;
}

GLdouble * Matrix4 :: getGLPointer()
{
    for(int i=0; i<16; i++)
        mGL[i] = (GLdouble)m[i];
    
    return mGL;
}

GLfloat * Matrix4 :: getGLfloatPointer()
{
    for(int i=0; i<16; i++)
        mGLf[i] = (GLfloat)m[i];
    
    return mGLf;
}

//****************************************************************
//**
//**   MATRIX ARITHMETIC:
//**
//****************************************************************

Vector4 Matrix4 :: mult( Vector4 v )
{
    
    double X = m[0]*v[0] + m[4]*v[1] + m[8]*v[2] + m[12]*v[3];
    double Y = m[1]*v[0] + m[5]*v[1] + m[9]*v[2] + m[13]*v[3];
    double Z = m[2]*v[0] + m[6]*v[1] + m[10]*v[2] + m[14]*v[3];
    double H = m[3]*v[0] + m[7]*v[1] + m[11]*v[2] + m[15]*v[3];

    Vector4 V;
    V.set(X,Y,Z,H);
    
    return V;
}

Vector4 Matrix4 :: operator* ( const Vector4& other )
{
    Vector4 V = other;
    
    double X = m[0]*V[0] + m[4]*V[1] + m[8]*V[2] + m[12]*V[3];
    double Y = m[1]*V[0] + m[5]*V[1] + m[9]*V[2] + m[13]*V[3];
    double Z = m[2]*V[0] + m[6]*V[1] + m[10]*V[2] + m[14]*V[3];
    double H = m[3]*V[0] + m[7]*V[1] + m[11]*V[2] + m[15]*V[3];
    
    V.set(X,Y,Z,H);
    
    return V;
}

Matrix4 Matrix4 :: mult( Matrix4 mat )
{
    Matrix4 result;
    
    result[0] = m[0]*mat[0] + m[4]*mat[1] + m[8]*mat[2] + m[12]*mat[3];
    result[1] = m[1]*mat[0] + m[5]*mat[1] + m[9]*mat[2] + m[13]*mat[3];
    result[2] = m[2]*mat[0] + m[6]*mat[1] + m[10]*mat[2] + m[14]*mat[3];
    result[3] = m[3]*mat[0] + m[7]*mat[1] + m[11]*mat[2] + m[15]*mat[3];
    
    result[4] = m[0]*mat[4] + m[4]*mat[5] + m[8]*mat[6] + m[12]*mat[7];
    result[5] = m[1]*mat[4] + m[5]*mat[5] + m[9]*mat[6] + m[13]*mat[7];
    result[6] = m[2]*mat[4] + m[6]*mat[5] + m[10]*mat[6] + m[14]*mat[7];
    result[7] = m[3]*mat[4] + m[7]*mat[5] + m[11]*mat[6] + m[15]*mat[7];
    
    result[8] = m[0]*mat[8] + m[4]*mat[9] + m[8]*mat[10] + m[12]*mat[11];
    result[9] = m[1]*mat[8] + m[5]*mat[9] + m[9]*mat[10] + m[13]*mat[11];
    result[10] = m[2]*mat[8] + m[6]*mat[9] + m[10]*mat[10] + m[14]*mat[11];
    result[11] = m[3]*mat[8] + m[7]*mat[9] + m[11]*mat[10] + m[15]*mat[11];
    
    result[12] = m[0]*mat[12] + m[4]*mat[13] + m[8]*mat[14] + m[12]*mat[15];
    result[13] = m[1]*mat[12] + m[5]*mat[13] + m[9]*mat[14] + m[13]*mat[15];
    result[14] = m[2]*mat[12] + m[6]*mat[13] + m[10]*mat[14] + m[14]*mat[15];
    result[15] = m[3]*mat[12] + m[7]*mat[13] + m[11]*mat[14] + m[15]*mat[15];
    
    return result;
}

Matrix4 Matrix4 :: operator* ( const Matrix4& other )
{
    Matrix4 mat = other;
    Matrix4 result;
    
    result[0] = m[0]*mat[0] + m[4]*mat[1] + m[8]*mat[2] + m[12]*mat[3];
    result[1] = m[1]*mat[0] + m[5]*mat[1] + m[9]*mat[2] + m[13]*mat[3];
    result[2] = m[2]*mat[0] + m[6]*mat[1] + m[10]*mat[2] + m[14]*mat[3];
    result[3] = m[3]*mat[0] + m[7]*mat[1] + m[11]*mat[2] + m[15]*mat[3];
    
    result[4] = m[0]*mat[4] + m[4]*mat[5] + m[8]*mat[6] + m[12]*mat[7];
    result[5] = m[1]*mat[4] + m[5]*mat[5] + m[9]*mat[6] + m[13]*mat[7];
    result[6] = m[2]*mat[4] + m[6]*mat[5] + m[10]*mat[6] + m[14]*mat[7];
    result[7] = m[3]*mat[4] + m[7]*mat[5] + m[11]*mat[6] + m[15]*mat[7];
    
    result[8] = m[0]*mat[8] + m[4]*mat[9] + m[8]*mat[10] + m[12]*mat[11];
    result[9] = m[1]*mat[8] + m[5]*mat[9] + m[9]*mat[10] + m[13]*mat[11];
    result[10] = m[2]*mat[8] + m[6]*mat[9] + m[10]*mat[10] + m[14]*mat[11];
    result[11] = m[3]*mat[8] + m[7]*mat[9] + m[11]*mat[10] + m[15]*mat[11];
    
    result[12] = m[0]*mat[12] + m[4]*mat[13] + m[8]*mat[14] + m[12]*mat[15];
    result[13] = m[1]*mat[12] + m[5]*mat[13] + m[9]*mat[14] + m[13]*mat[15];
    result[14] = m[2]*mat[12] + m[6]*mat[13] + m[10]*mat[14] + m[14]*mat[15];
    result[15] = m[3]*mat[12] + m[7]*mat[13] + m[11]*mat[14] + m[15]*mat[15];
    
    return result;
}

Matrix4 Matrix4 :: transpose()
{
    Matrix4 result;
    result.set(m[0],m[4],m[8],m[12],
               m[1],m[5],m[9],m[13],
               m[2],m[6],m[10],m[14],
               m[3],m[7],m[11],m[15]);
    
    return result;
}

//****************************************************************
//**
//**   MAKE TRANSFORMATION MATRICES:
//**
//****************************************************************

void Matrix4 :: makeXRot(double angle)
{
    angle = angle*(PI/180);
    
    m[0] = 1;
    m[1] = 0;
    m[2] = 0;
    m[3] = 0;
    
    m[4] = 0;
    m[5] = cos(angle);
    m[6] = sin(angle);
    m[7] = 0;
    
    m[8] = 0;
    m[9] = -sin(angle);
    m[10] = cos(angle);
    m[11] = 0;
    
    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
}


void Matrix4 :: makeYRot(double angle)
{
    angle = angle*(PI/180);
    
    m[0] = cos(angle);
    m[1] = 0;
    m[2] = -sin(angle);
    m[3] = 0;
    
    m[4] = 0;
    m[5] = 1;
    m[6] = 0;
    m[7] = 0;
    
    m[8] = sin(angle);
    m[9] = 0;
    m[10] = cos(angle);
    m[11] = 0;
    
    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
}

void Matrix4 :: makeZRot(double angle)
{
    angle = angle*(PI/180);
    
    m[0] = cos(angle);
    m[1] = sin(angle);
    m[2] = 0;
    m[3] = 0;
    
    m[4] = -sin(angle);
    m[5] = cos(angle);
    m[6] = 0;
    m[7] = 0;
    
    m[8] = 0;
    m[9] = 0;
    m[10] = 1;
    m[11] = 0;
    
    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
}

void Matrix4 :: makeAxisRot(Vector3 axis, double angle)
{
    Vector3 unit = axis.normalise();
    
    angle = angle*(PI/180);
    
    double c = cos(angle);
    double s = sin(angle);
    
    m[0] = unit[0]*unit[0] + c*(1-unit[0]*unit[0]);
    m[1] = unit[0]*unit[1]*(1-c) + unit[2]*s;
    m[2] = unit[0]*unit[2]*(1-c) - unit[1]*s;
    m[3] = 0;
    
    m[4] = unit[0]*unit[1]*(1-c) - unit[2]*s;
    m[5] = unit[1]*unit[1] + c*(1-unit[1]*unit[1]);
    m[6] = unit[1]*unit[2]*(1-c) + unit[0]*s;
    m[7] = 0;
    
    m[8] = unit[0]*unit[2]*(1-c) + unit[1]*s;
    m[9] = unit[1]*unit[2]*(1-c) - unit[0]*s;
    m[10] = unit[2]*unit[2] + c*(1-unit[2]*unit[2]);
    m[11] = 0;
    
    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
}

void Matrix4 :: makeScale(double scale)
{
    for(int i = 0; i<16; i++) m[i] = 0;
    
    m[0] = scale;
    m[5] = scale;
    m[10] = scale;
    m[15] = 1;
}

void Matrix4 :: makeScale(Vector3 scale)
{
    for(int i = 0; i<16; i++) m[i] = 0;
    
    m[0] = scale[0];
    m[5] = scale[1];
    m[10] = scale[2];
    m[15] = 1;
}

void Matrix4 :: makeScale(Vector4 scale)
{
    for(int i = 0; i<16; i++) m[i] = 0;
    
    m[0] = scale[0];
    m[5] = scale[1];
    m[10] = scale[2];
    m[15] = scale[3];
}

void Matrix4 :: makeTranslation(Vector3 trans)
{
    for(int i = 0; i<12; i++) m[i] = 0;
    
    m[0] = 1;
    m[5] = 1;
    m[10] = 1;
    m[15] = 1;
    
    m[12] = trans[0];
    m[13] = trans[1];
    m[14] = trans[2];
}

void Matrix4 :: makeI()
{
    for(int i = 0; i<16; i++) m[i] = 0;
    
    m[0] = 1;
    m[5] = 1;
    m[10] = 1;
    m[15] = 1;
}

//****************************************************************
//**
//**   PRINT:
//**
//****************************************************************

void Matrix4 :: print(char * comment)
{
    cout << comment << "\n";
    cout << m[0] << " " << m[4] << " " << m[8] << " " << m[12] << '\n';
    cout << m[1] << " " << m[5] << " " << m[9] << " " << m[13] << '\n';
    cout << m[2] << " " << m[6] << " " << m[10] << " " << m[14] << '\n';
    cout << m[3] << " " << m[7] << " " << m[11] << " " << m[15] << '\n';
}
