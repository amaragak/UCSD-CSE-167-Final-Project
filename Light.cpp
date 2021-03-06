//
//  Light.cpp
//  CSE 167 Project 5
//
//  Created by Alex Maragakis on 20/11/2014.
//  Copyright (c) 2014 Gak Industries. All rights reserved.
//

#include "Light.h"

//****************************************************************
//**
//**   CONSTRUCTORS:
//**
//****************************************************************

Light :: Light()
{
    ambient_colour[0] = 0.0;
    ambient_colour[1] = 0.0;
    ambient_colour[2] = 0.0;
    ambient_colour[3] = 1.0;
    
    diffuse_colour[0] = 1.0;
    diffuse_colour[1] = 1.0;
    diffuse_colour[2] = 1.0;
    diffuse_colour[3] = 1.0;
    
    specular_colour[0] = 1.0;
    specular_colour[1] = 1.0;
    specular_colour[2] = 1.0;
    specular_colour[3] = 1.0;
    
    position[0] = 0.0;
    position[1] = 0.0;
    position[2] = 1.0;
    position[3] = 0.0;
    
    spot_direction[0] = 0.0;
    spot_direction[1] = 0.0;
    spot_direction[2] = -1.0;
    
    spot_exponent = 0.0;
    spot_cutoff   = 180.0;
    
    const_atten = 1.0;
    lin_atten   = 0.0;
    quad_atten  = 0.0;
    
    setMatrix();
}

Light :: Light(int type)
{
    switch(type)
    {
        case LIGHT_BUNNY:
            bunny();
            break;
            
        case LIGHT_BEAR:
            bear();
            break;
            
        case LIGHT_DRAGON:
            dragon();
            break;
            
        case LIGHT_SPOTLIGHT:
            spotlight();
            break;
            
        case LIGHT_POINTLIGHT:
            pointlight();
            break;
            
        default:
            Light();
            break;
    }
}

//****************************************************************
//**
//**   PREMADE LIGHTS:
//**
//****************************************************************

void Light :: bunny()
{
    ambient_colour[0] = 0.0;
    ambient_colour[1] = 0.0;
    ambient_colour[2] = 0.0;
    ambient_colour[3] = 1.0;
    
    diffuse_colour[0] = 1.0;
    diffuse_colour[1] = 1.0;
    diffuse_colour[2] = 1.0;
    diffuse_colour[3] = 1.0;
    
    specular_colour[0] = 1.0;
    specular_colour[1] = 1.0;
    specular_colour[2] = 1.0;
    specular_colour[3] = 1.0;
    
    position[0] = 0.0;
    position[1] = 0.0;
    position[2] = 1.0;
    position[3] = 0.0;
    
    spot_direction[0] = 0.0;
    spot_direction[1] = 0.0;
    spot_direction[2] = -1.0;
    
    spot_exponent = 0.0;
    spot_cutoff   = 180.0;
    
    const_atten = 1.0;
    lin_atten   = 0.0;
    quad_atten  = 0.0;
    
    setMatrix();
}

void Light :: bear()
{
    ambient_colour[0] = 0.2;
    ambient_colour[1] = 0.2;
    ambient_colour[2] = 0.2;
    ambient_colour[3] = 1.0;
    
    diffuse_colour[0] = 1.0;
    diffuse_colour[1] = 1.0;
    diffuse_colour[2] = 1.0;
    diffuse_colour[3] = 1.0;
    
    specular_colour[0] = 0.0;
    specular_colour[1] = 0.0;
    specular_colour[2] = 0.0;
    specular_colour[3] = 1.0;
    
    position[0] = 0.0;
    position[1] = 0.0;
    position[2] = 20.0;
    position[3] = 0.0;
    
    spot_direction[0] = 0.0;
    spot_direction[1] = 0.0;
    spot_direction[2] = -1.0;
    
    spot_exponent = 4.0;
    spot_cutoff   = 110.0;
    
    const_atten = 0.0;
    lin_atten   = 0.0;
    quad_atten  = 1.0;
    
    setMatrix();
}

void Light :: dragon()
{
    ambient_colour[0] = 0.0;
    ambient_colour[1] = 0.0;
    ambient_colour[2] = 0.0;
    ambient_colour[3] = 1.0;
    
    diffuse_colour[0] = 1.0;
    diffuse_colour[1] = 1.0;
    diffuse_colour[2] = 1.0;
    diffuse_colour[3] = 1.0;
    
    specular_colour[0] = 1.0;
    specular_colour[1] = 1.0;
    specular_colour[2] = 1.0;
    specular_colour[3] = 1.0;
    
    position[0] = 0.0;
    position[1] = 0.0;
    position[2] = 1.0;
    position[3] = 0.0;
    
    spot_direction[0] = 0.0;
    spot_direction[1] = 0.0;
    spot_direction[2] = -1.0;
    
    spot_exponent = 0.0;
    spot_cutoff   = 180.0;
    
    const_atten = 1.0;
    lin_atten   = 0.0;
    quad_atten  = 0.0;
    
    setMatrix();
}

void Light :: pointlight()
{
    ambient_colour[0] = 0.0;
    ambient_colour[1] = 0.0;
    ambient_colour[2] = 0.0;
    ambient_colour[3] = 1.0;
    
    diffuse_colour[0] = 1.0;
    diffuse_colour[1] = 0.9;
    diffuse_colour[2] = 0.7;
    diffuse_colour[3] = 1.0;
    
    specular_colour[0] = 0.0;
    specular_colour[1] = 0.0;
    specular_colour[2] = 0.0;
    specular_colour[3] = 1.0;
    
    position[0] = 0.0;
    position[1] = 20.0;
    position[2] = 0.0;
    position[3] = 0.0;
    
    spot_direction[0] = 0.0;
    spot_direction[1] = -1.0;
    spot_direction[2] = 0.0;
    
    spot_exponent = 0.0;
    spot_cutoff   = 180.0;
    
    const_atten = 0.0;
    lin_atten   = 0.0;
    quad_atten  = 10.0;
    
    setMatrix();
}

void Light :: spotlight()
{
    ambient_colour[0] = 0.0;
    ambient_colour[1] = 0.0;
    ambient_colour[2] = 0.0;
    ambient_colour[3] = 1.0;
    
    diffuse_colour[0] = 0.8;
    diffuse_colour[1] = 0.8;
    diffuse_colour[2] = 0.8;
    diffuse_colour[3] = 1.0;
    
    specular_colour[0] = 0.2;
    specular_colour[1] = 0.2;
    specular_colour[2] = 0.2;
    specular_colour[3] = 1.0;
    
    position[0] = 30.0;
    position[1] = 30.0;
    position[2] = 0.0;
    position[3] = 0.0;
    
    spot_direction[0] = -1.0;
    spot_direction[1] = -1.0;
    spot_direction[2] = 0.0;
    
    spot_exponent = 0.0;
    spot_cutoff   = 5.0;
    
    const_atten = 0.0;
    lin_atten   = 0.0;
    quad_atten  = 1.0;
    
    setMatrix();
}

//****************************************************************
//**
//**   SET LIGHT MATRIX:
//**
//****************************************************************

void Light :: setMatrix()
{
    Matrix4 translation  = *new Matrix4();
    Vector3 trans_vector = *new Vector3((double)position[0],
                                        (double)position[1],
                                        (double)position[2]);
    
    translation.makeTranslation(trans_vector);
    
    Vector3 initial_direction = *new Vector3((double)0.0, (double)0.0, (double)-1.0);
    Vector3 direction         = *new Vector3((double)spot_direction[0],
                                             (double)spot_direction[1],
                                             (double)spot_direction[2]);
    direction.normalise();
    
    Vector3 axis = direction.cross(initial_direction);
    axis.normalise();
    
    double angle;
    
    initial_direction.print("ID");
    direction.print("D");
    
    if((double)spot_direction[0] == initial_direction[0] &&
       (double)spot_direction[1] == initial_direction[1] &&
       (double)spot_direction[2] == initial_direction[2])
        angle = 0.0;
    
    else if((double)spot_direction[0] == -initial_direction[0] &&
           (double)spot_direction[1] == -initial_direction[1] &&
           (double)spot_direction[2] == -initial_direction[2])
        angle = 180.0;
    
    else
        angle = (180.0/PI) * acos(direction.dot(initial_direction));
    
    Matrix4 rotation = *new Matrix4();
    rotation.makeAxisRot(axis, angle);
    
    matrix = translation*rotation;
}

//****************************************************************
//**
//**   GET FUNCTIONS:
//**
//****************************************************************

float * Light :: getAmbientColour()
{
    return ambient_colour;
}

float * Light :: getDiffuseColour()
{
    return diffuse_colour;
}

float * Light :: getSpecularColour()
{
    return specular_colour;
}
    
float * Light :: getPosition()
{
    return position;
}

float * Light :: getSpotDirection()
{
    return spot_direction;
}

float Light :: getSpotExponent()
{
    return spot_exponent;
}

float Light :: getSpotCutoff()
{
    return spot_cutoff;
}
    
float Light :: getConstAtten()
{
    return const_atten;
}

float Light :: getLinAtten()
{
    return lin_atten;
}

float Light :: getQuadAtten()
{
    return quad_atten;
}