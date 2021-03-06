//
//  Renderer.h
//  CSE 167 Final Project
//
//  Created by Alex Maragakis on 11/12/2014.
//  Copyright (c) 2014 Gak Industries. All rights reserved.
//

#ifndef __CSE_167_Final_Project__Renderer__
#define __CSE_167_Final_Project__Renderer__

#include <stdio.h>
#include <GLUT/glut.h>
#include "Matrix4.h"
#include "Camera.h"

namespace Renderer
{
//Repeatedly Called Functions:
    extern void startProgram();
    extern void setUniforms();
    
//Initialisation:
    extern void initRenderer();
    
//Variablses:
    extern GLuint shader_program;
    
    extern GLint projection_handle;
    extern GLint camera_modelview_handle;
    
    extern Matrix4 projection;
    extern Matrix4 camera_modelview;
};

#endif /* defined(__CSE_167_Final_Project__Renderer__) */
