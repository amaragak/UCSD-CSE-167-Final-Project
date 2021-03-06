//
//  Light.h
//  CSE 167 Project 5
//
//  Created by Alex Maragakis on 20/11/2014.
//  Copyright (c) 2014 Gak Industries. All rights reserved.
//

#ifndef __CSE_167_Project_5__Light__
#define __CSE_167_Project_5__Light__

#include <stdio.h>
#include "Matrix4.h"

#define LIGHT_BUNNY 0
#define LIGHT_BEAR 1
#define LIGHT_DRAGON 2
#define LIGHT_SPOTLIGHT 3
#define LIGHT_POINTLIGHT 4

class Light
{
private:
//Private Variables
    float ambient_colour[4];
    float diffuse_colour[4];
    float specular_colour[4];
    
    float position[4];
    float spot_direction[3];
    
    float spot_exponent;
    float spot_cutoff;
    
    float const_atten;
    float lin_atten;
    float quad_atten;
    
//Private functions for setting premade lights
    void bunny();
    void bear();
    void dragon();
    void spotlight();
    void pointlight();
    
//Private function for setting light matrix
    void setMatrix();
    
public:
//Constructors
    Light();
    Light(int);
    
//Get Functions
    float * getAmbientColour();
    float * getDiffuseColour();
    float * getSpecularColour();
    
    float * getPosition();
    float * getSpotDirection();
    
    float getSpotExponent();
    float getSpotCutoff();
    
    float getConstAtten();
    float getLinAtten();
    float getQuadAtten();
    
    Matrix4 matrix;
    
    Matrix4 getMatrix();
};

#endif /* defined(__CSE_167_Project_5__Light__) */
