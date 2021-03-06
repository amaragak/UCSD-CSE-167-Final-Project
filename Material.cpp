//
//  Material.cpp
//  CSE 167 Project 5
//
//  Created by Alex Maragakis on 20/11/2014.
//  Copyright (c) 2014 Gak Industries. All rights reserved.
//

#include "Material.h"

//****************************************************************
//**
//**   CONSTRUCTORS:
//**
//****************************************************************

Material :: Material()
{
    ambient_colour[0] = 0.2;
    ambient_colour[1] = 0.2;
    ambient_colour[2] = 0.2;
    ambient_colour[3] = 1.0;
    
    diffuse_colour[0] = 0.8;
    diffuse_colour[1] = 0.8;
    diffuse_colour[2] = 0.8;
    diffuse_colour[3] = 1.0;
    
    specular_colour[0] = 0.0;
    specular_colour[1] = 0.0;
    specular_colour[2] = 0.0;
    specular_colour[3] = 1.0;
    
    emissive_colour[0] = 0.0;
    emissive_colour[1] = 0.0;
    emissive_colour[2] = 0.0;
    emissive_colour[3] = 1.0;
    
    colour_indices[0] = 0;
    colour_indices[1] = 1;
    colour_indices[2] = 1;
    
    specular_exponent = 0.0;
}

Material :: Material(int type)
{
    switch(type)
    {
        case MAT_BUNNY:
            bunny();
            break;
            
        case MAT_BEAR:
            bear();
            break;
            
        case MAT_DRAGON:
            dragon();
            break;
        
        case MAT_WATER:
            water();
            break;
            
        default:
            Material();
    }
}

//****************************************************************
//**
//**   PREMADE MATERIALS:
//**
//****************************************************************

void Material :: water()
{
    ambient_colour[0] = 0.1;
    ambient_colour[1] = 0.1;
    ambient_colour[2] = 0.1;
    ambient_colour[3] = 1.0;
    
    diffuse_colour[0] = 0.8;
    diffuse_colour[1] = 0.8;
    diffuse_colour[2] = 0.8;
    diffuse_colour[3] = 1.0;
    
    specular_colour[0] = 0.4;
    specular_colour[1] = 0.3;
    specular_colour[2] = 0.3;
    specular_colour[3] = 1.0;
    
    emissive_colour[0] = 0.0;
    emissive_colour[1] = 0.0;
    emissive_colour[2] = 0.0;
    emissive_colour[3] = 1.0;
    
    colour_indices[0] = 0;
    colour_indices[1] = 1;
    colour_indices[2] = 1;
    
    specular_exponent = 32.0;
}

void Material :: bunny()
{
    ambient_colour[0] = 0.1;
    ambient_colour[1] = 0.1;
    ambient_colour[2] = 0.1;
    ambient_colour[3] = 1.0;
    
    diffuse_colour[0] = 0.8;
    diffuse_colour[1] = 0.3;
    diffuse_colour[2] = 0.6;
    diffuse_colour[3] = 1.0;
    
    specular_colour[0] = 0.3;
    specular_colour[1] = 0.0;
    specular_colour[2] = 0.2;
    specular_colour[3] = 1.0;
    
    emissive_colour[0] = 0.0;
    emissive_colour[1] = 0.0;
    emissive_colour[2] = 0.0;
    emissive_colour[3] = 1.0;
    
    colour_indices[0] = 0;
    colour_indices[1] = 1;
    colour_indices[2] = 1;
    
    specular_exponent = 32.0;
}

void Material :: bear()
{
    ambient_colour[0] = 0.2;
    ambient_colour[1] = 0.2;
    ambient_colour[2] = 0.2;
    ambient_colour[3] = 1.0;
    
    diffuse_colour[0] = 1.0;
    diffuse_colour[1] = 0.9;
    diffuse_colour[2] = 0.7;
    diffuse_colour[3] = 1.0;
    
    specular_colour[0] = 0.0;
    specular_colour[1] = 0.0;
    specular_colour[2] = 0.0;
    specular_colour[3] = 1.0;
    
    emissive_colour[0] = 0.0;
    emissive_colour[1] = 0.0;
    emissive_colour[2] = 0.0;
    emissive_colour[3] = 1.0;
    
    colour_indices[0] = 0;
    colour_indices[1] = 1;
    colour_indices[2] = 1;
    
    specular_exponent = 0.0;
}

void Material :: dragon()
{
    ambient_colour[0] = 0.0;
    ambient_colour[1] = 0.0;
    ambient_colour[2] = 0.0;
    ambient_colour[3] = 1.0;
    
    diffuse_colour[0] = 0.0;
    diffuse_colour[1] = 0.8;
    diffuse_colour[2] = 0.0;
    diffuse_colour[3] = 1.0;
    
    specular_colour[0] = 0.9;
    specular_colour[1] = 0.1;
    specular_colour[2] = 0.1;
    specular_colour[3] = 1.0;
    
    emissive_colour[0] = 0.0;
    emissive_colour[1] = 0.2;
    emissive_colour[2] = 0.2;
    emissive_colour[3] = 1.0;
    
    colour_indices[0] = 0;
    colour_indices[1] = 1;
    colour_indices[2] = 1;
    
    specular_exponent = 5.0;
}

//****************************************************************
//**
//**   GET FUNCTIONS:
//**
//****************************************************************

float * Material :: getAmbientColour()
{
    return ambient_colour;
}

float * Material :: getDiffuseColour()
{
    return diffuse_colour;
}

float * Material :: getSpecularColour()
{
    return specular_colour;
}

float * Material :: getEmissiveColour()
{
    return emissive_colour;
}
    
int * Material :: getColourIndices()
{
    return colour_indices;
}
    
float Material :: getSpecularExponent()
{
    return specular_exponent;
}