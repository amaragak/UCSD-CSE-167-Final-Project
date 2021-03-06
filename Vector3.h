//
//  Vector3.h
//  CSE 167 Project 1
//
//  Created by Alex Maragakis on 15/10/2014.
//  Copyright (c) 2014 Gak Industries. All rights reserved.
//

#ifndef __CSE_167_Project_1__Vector3__
#define __CSE_167_Project_1__Vector3__

#include <iostream>
#include "math.h"
#include "Vector4.h"

class Vector3
{
private:
//Private Variables:
    double x,y,z;
    
public:
//Constructors:
    Vector3();
    Vector3( double X, double Y, double Z );
    
//Initialisation:
    void set( double X, double Y, double Z );
    
//Get Functions:
    double get( int pos );
    double& operator[] ( const int i );
    
//Vector Arithmetic
    Vector3 add( Vector3 v );
    Vector3 operator+ ( const Vector3& other );
    
    Vector3 subtract( Vector3 v );
    Vector3 operator- ( const Vector3& other );
    
    Vector3 negate();
    
    Vector3 scale( double factor );
    
    double dot( Vector3 v );
    
    Vector3 cross( Vector3 v );
    
    double magnitude();
    
    Vector3 normalise();
    
//Print
    void print(char * comment);
    
};

#endif
