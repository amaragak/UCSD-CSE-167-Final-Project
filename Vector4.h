//
//  Vector4.h
//  CSE 167 Project 1
//
//  Created by Alex Maragakis on 15/10/2014.
//  Copyright (c) 2014 Gak Industries. All rights reserved.
//

#ifndef __CSE_167_Project_1__Vector4__
#define __CSE_167_Project_1__Vector4__

#include <iostream>
#include "math.h"
#include "Vector3.h"

class Vector4
{
private:
//Private Variables:
    double x,y,z,w;
    
public:
//Constructors:
    Vector4();
    Vector4( double X, double Y, double Z);
    Vector4( double X, double Y, double Z, double W );
    
//Initialisation:
    void set( double X, double Y, double Z, double W );
    
//Get Functions:
    double get( int pos );
    double& operator[] ( const int i );
    
//Vector Arithmetic:
    Vector4 add( Vector4 v );
    Vector4 operator+ ( const Vector4& other );
    
    Vector4 subtract( Vector4 v );
    Vector4 operator- ( const Vector4& other );
    
    Vector4 negate();
    
    Vector4 scale( double factor );
    Vector4 scale( double factorx, double factory, double factorz );
    
    double dot( Vector4 v );
    
    Vector4 cross( Vector4 v );
    
    double magnitude();
    
    void normalise();
    
    void dehomogenize();
    
//Print:
    void print(char * comment);
    void print();
};


#endif

