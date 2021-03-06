//
//  Camera.h
//  Computer Graphics Project 2
//
//  Created by Alex Maragakis on 23/08/2014.
//  Copyright (c) 2014 Gak Industries. All rights reserved.
//

#ifndef __Computer_Graphics_Project_2__Camera__
#define __Computer_Graphics_Project_2__Camera__

#include <iostream>
#include "Matrix4.h"

class Camera
{
private:
//Private Variablies
    Vector3 center_of_projection;
    Vector3 look_at_point;
    Vector3 up_vector;
    
    Matrix4 camera_matrix;
    Matrix4 inverse_camera_matrix;
    
public:
//Constructors
    Camera();
    Camera(Vector3 COP, Vector3 LAP, Vector3 UV);
    Camera(int);
    
//Initialisation:
    void set(Vector3 COP, Vector3 LAP, Vector3 UV);
    
//Get Functions:
    Vector3 getXc();
    Vector3 getYc();
    Vector3 getZc();
    
    Vector3 getCOP();
    Vector3 getLAP();
    Vector3 getUV();
    
    Matrix4 getCM();
    double * getCMPointer();
    GLdouble * getCMGLPointer();
    
    Matrix4 getInverseCM();
    double * getInverseCMPointer();
    GLdouble * getInverseCMGLPointer();
};

#endif /* defined(__Computer_Graphics_Project_2__Camera__) */
