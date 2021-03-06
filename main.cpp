//
//  main.cpp
//  CSE 167 Final Project
//
//  Created by Alex Maragakis on 09/12/2014.
//  Copyright (c) 2014 Gak Industries. All rights reserved.
//

#include "main.h"
#include <GLUT/glut.h>
#include "Window.h"
#include "main.h"
#include "Renderer.h"

using namespace Globals;

namespace Globals
{
//Global Variables:
    BP BezierPatch;
    Camera camera = * new Camera(1);
    Material material = * new Material(MAT_WATER);
    Light light = * new Light(LIGHT_SPOTLIGHT);
    Ball ball;
    ICCone cone = *new ICCone();
    
    GLuint vs_program;
    GLuint fs_program;
};

//****************************************************************
//**
//**   SET FUNCTIONS:
//**
//****************************************************************

void setLight()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light.getAmbientColour());
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light.getDiffuseColour());
    glLightfv(GL_LIGHT0, GL_SPECULAR, light.getSpecularColour());
    glLightfv(GL_LIGHT0, GL_POSITION, light.getPosition());
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light.getSpotDirection());
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, light.getSpotExponent());
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, light.getSpotCutoff());
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, light.getConstAtten());
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, light.getLinAtten());
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, light.getQuadAtten());
}

void setMaterial()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material.getAmbientColour());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material.getDiffuseColour());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.getSpecularColour());
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material.getEmissiveColour());
    glMaterialiv(GL_FRONT_AND_BACK, GL_COLOR_INDEXES, material.getColourIndices());
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.getSpecularExponent());
}

//****************************************************************
//**
//**   PROGRAM MAIN:
//**
//****************************************************************

int main(int argc, char *argv[])
{
    Window :: setPatch();
    Window :: setBall();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(Window :: width, Window :: height);
    glutCreateWindow("ICSE CREAM");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    
    glutDisplayFunc(Window :: displayCallback);
    glutReshapeFunc(Window :: reshapeCallback);
    glutIdleFunc(Window :: idleCallback);
    
    glutKeyboardFunc(Window :: processNormalKeys);
    glutSpecialFunc(Window :: processSpecialKeys);
    glutMouseFunc(Window :: processMouseButtons);
    glutMotionFunc(Window :: processMouseMotion);
    glutPassiveMotionFunc(Window :: processPassiveMotion);
    
    setMaterial();
    setLight();
    
    Window :: getConePosition();
    Renderer :: initRenderer();
    
    glutMainLoop();
    
    return 0;
}