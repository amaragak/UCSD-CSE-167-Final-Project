//
//  Material.h
//  CSE 167 Project 5
//
//  Created by Alex Maragakis on 20/11/2014.
//  Copyright (c) 2014 Gak Industries. All rights reserved.
//

#ifndef __CSE_167_Project_5__Material__
#define __CSE_167_Project_5__Material__

#include <stdio.h>

#define MAT_BUNNY 0
#define MAT_BEAR 1
#define MAT_DRAGON 2
#define MAT_WATER 3

class Material
{
private:
//Private Variables:
    float ambient_colour[4];
    float diffuse_colour[4];
    float specular_colour[4];
    float emissive_colour[4];
    
    int colour_indices[3];
    
    float specular_exponent;
    
//Private functions for setting premade materials
    void bunny();
    void bear();
    void dragon();
    void water();
    
public:
//Constructors:
    Material();
    Material(int);

//Get Functions:
    float * getAmbientColour();
    float * getDiffuseColour();
    float * getSpecularColour();
    float * getEmissiveColour();
    
    int * getColourIndices();
    
    float getSpecularExponent();
};

#endif /* defined(__CSE_167_Project_5__Material__) */
