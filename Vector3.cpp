//
//  Vector3.cpp
//  CSE 167 Project 1
//
//  Created by Alex Maragakis on 15/10/2014.
//  Copyright (c) 2014 Gak Industries. All rights reserved.
//

#include "Vector3.h"

using namespace std;

//****************************************************************
//**
//**   CONSTRUCTORS:
//**
//****************************************************************

Vector3 :: Vector3()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector3 :: Vector3( double X, double Y, double Z )
{
    x = X;
    y = Y;
    z = Z;
}

//****************************************************************
//**
//**   INITIALISATION:
//**
//****************************************************************

void Vector3 :: set( double X, double Y, double Z )
{
    x = X;
    y = Y;
    z = Z;
}

//****************************************************************
//**
//**   GET FUNCTIONS:
//**
//****************************************************************

double Vector3 ::  get( int pos )
{
    switch(pos)
    {
        case 0:  return x;
        case 1:  return y;
        case 2:  return z;
            
        default: cerr << "Vector index out of bounds.";
                 return 0;
    }
}

double& Vector3 :: operator[] ( const int i )
{
    switch(i)
    {
        case 0:  return x;
        case 1:  return y;
        case 2:  return z;
            
        default: cerr << "Vector index out of bounds.";
                 return x;
    }
}

//****************************************************************
//**
//**   VECTOR ARITHMETIC:
//**
//****************************************************************

Vector3 Vector3 :: add( Vector3 v )
{
    double X = x + v.x;
    double Y = y + v.y;
    double Z = z + v.z;
    
    Vector3 result;
    
     result.set(X,Y,Z);
    
    return result;
}

Vector3 Vector3 :: operator+ ( const Vector3& other )
{
    double X = x + other.x;
    double Y = y + other.y;
    double Z = z + other.z;
    
    Vector3 result;
    
    result.set(X,Y,Z);
    
    return result;
    
}

Vector3 Vector3 :: subtract( Vector3 v )
{
    double X = x - v.x;
    double Y = y - v.y;
    double Z = z - v.z;
    
    Vector3 result;
    
    result.set(X,Y,Z);
    
    return result;
}

Vector3 Vector3 :: operator- ( const Vector3& other )
{
    double X = x - other.x;
    double Y = y - other.y;
    double Z = z - other.z;
    
    Vector3 result;
    
    result.set(X,Y,Z);
    
    return result;
}

Vector3 Vector3 :: negate()
{
    double X = -x;
    double Y = -y;
    double Z = -z;
    
    Vector3 result;
    
    result.set(X,Y,Z);
    
    return result;
}

Vector3 Vector3 :: scale( double factor )
{
    double X = x*factor;
    double Y = y*factor;
    double Z = z*factor;
    
    Vector3 result;
    
    result.set(X,Y,Z);
    
    return result;
}

double Vector3 :: dot( Vector3 v )
{
    double X = x*v.x;
    double Y = y*v.y;
    double Z = z*v.z;
    
    return X+Y+Z;
}

Vector3 Vector3 :: cross( Vector3 v )
{
    double X = y*v.z - z*v.y;
    double Y = z*v.x - x*v.z;
    double Z = x*v.y - y*v.x;
    
    Vector3 result;
    result.set(X,Y,Z);
    
    return result;
}

double Vector3 :: magnitude()
{
    return sqrt(x*x + y*y + z*z);
}

Vector3 Vector3 :: normalise()
{
    double mag = magnitude();
    
    double X;
    double Y;
    double Z;
    
    if(mag==0)
    {
        X = 0;
        Y = 0;
        Z = 0;
    }
    
    else
    {
        X = x/mag;
        Y = y/mag;
        Z = z/mag;
    }
    
    Vector3 result;
    result.set(X,Y,Z);
    
    return result;
}

//****************************************************************
//**
//**   PRINT:
//**
//****************************************************************

void Vector3 :: print(char * comment)
{
    cout << comment << "\n";
    cout << "x = " << x;
    cout << "\ny = " << y;
    cout << "\nz = " << z;
    cout << "\n";
}

