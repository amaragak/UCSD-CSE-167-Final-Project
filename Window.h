//
//  Window.h
//  CSE 167 Final Project
//
//  Created by Alex Maragakis on 09/12/2014.
//  Copyright (c) 2014 Gak Industries. All rights reserved.
//

#ifndef __CSE_167_Final_Project__Window__
#define __CSE_167_Final_Project__Window__

#include <stdio.h>

namespace Window
{
//GLUT Windowing:
    extern void display();
    extern void displayCallback();
    extern void idleCallback();
    extern void reshapeCallback(int,int);
    
//Get/Set/Calculate/Update Values:
    extern void getConePosition();
    
    extern void processNormalKeys(unsigned char, int, int);
    extern void processSpecialKeys(int, int, int);
    extern void processMouseButtons(int, int, int, int);
    extern void processMouseMotion(int, int);
    extern void processPassiveMotion(int, int);
    
    extern void setPatch();
    extern void setBall();
    
    extern void calcMesh();
    extern void updateBall();
    
//Variables:
    extern double FOV;
    extern double aspect;
    extern double zNear;
    extern double zFar;
    
    extern bool sm_on;
    extern bool paused;
    
    extern int width;
    extern int height;
};

#endif /* defined(__CSE_167_Final_Project__Window__) */
