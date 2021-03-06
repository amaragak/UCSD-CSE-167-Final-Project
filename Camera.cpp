//
//  Camera.cpp
//  Computer Graphics Project 2
//
//  Created by Alex Maragakis on 23/08/2014.
//  Copyright (c) 2014 Gak Industries. All rights reserved.
//

#include <iostream>
#include "Camera.h"

//****************************************************************
//**
//**   CONSTRUCTORS:
//**
//****************************************************************

Camera :: Camera()
{
    center_of_projection = *new Vector3();
    look_at_point        = *new Vector3();
    up_vector            = *new Vector3();
    
    camera_matrix = *new Matrix4();
    camera_matrix.makeI();
    
    inverse_camera_matrix.makeI();
}

Camera :: Camera(int i)
{
    if(i == 0)
        Camera();
    
    else if(i == 1)
    {
        Vector3 cop = *new Vector3(0,20,25);
        Vector3 lap = *new Vector3(0,0,0);
        Vector3 uv  = *new Vector3(0,1,0);
        
        set(cop,lap,uv);
    }
    
    else if(i == 2)
    {
        Vector3 cop = *new Vector3(-15,5,10);
        Vector3 lap = *new Vector3(-5,0,0);
        Vector3 uv  = *new Vector3(0,1,0.5);
        
        set(cop,lap,uv);
    }
    
    else
        std::cerr << "Camera constructor undefined for given argument\n";
}

Camera :: Camera(Vector3 cop, Vector3 lap, Vector3 uv)
{
    set(cop,lap,uv);
}

//****************************************************************
//**
//**   INITIALISATION:
//**
//****************************************************************

void Camera :: set(Vector3 cop, Vector3 lap, Vector3 uv)
{
    center_of_projection = cop;
    look_at_point        = lap;
    up_vector            = uv;
    
//Calculate the axis of the camera 
    Vector3 zc = center_of_projection - look_at_point;
    zc         = zc.normalise();
    
    Vector3 xc = up_vector.cross(zc);
    xc         = xc.normalise();
    
    Vector3 yc = zc.cross(xc);
    
    camera_matrix = *new Matrix4(xc[0],xc[1],xc[2],0,
                                 yc[0],yc[1],yc[2],0,
                                 zc[0],zc[1],zc[2],0,
                                 center_of_projection[0],
                                 center_of_projection[1],
                                 center_of_projection[2],
                                 1);
    
   
    
    Matrix4 R = *new Matrix4(camera_matrix[0],camera_matrix[1],camera_matrix[2],0,
                             camera_matrix[4],camera_matrix[5],camera_matrix[6],0,
                             camera_matrix[8],camera_matrix[9],camera_matrix[10],0,
                             0,0,0,1);
   
    
    Vector4 v = *new Vector4(camera_matrix[12],camera_matrix[13],camera_matrix[14],1);
    
    
    Matrix4 R_transp = R.transpose();
    
    Vector4 T = R_transp*v;
    
    inverse_camera_matrix = *new Matrix4(R_transp[0],R_transp[1],R_transp[2],0,
                                         R_transp[4],R_transp[5],R_transp[6],0,
                                         R_transp[8],R_transp[9],R_transp[10],0,
                                         -T[0],-T[1],-T[2],1);
}

//****************************************************************
//**
//**   GET FUNCTIONS:
//**
//****************************************************************

Vector3 Camera :: getXc()
{
    Vector3 xc = *new Vector3(camera_matrix[0],
                              camera_matrix[1],
                              camera_matrix[2]);
    
    return xc;
}

Vector3 Camera :: getYc()
{
    Vector3 yc = *new Vector3(camera_matrix[4],
                              camera_matrix[5],
                              camera_matrix[6]);
    
    return yc;
}

Vector3 Camera :: getZc()
{
    Vector3 zc = *new Vector3(camera_matrix[8],
                              camera_matrix[9],
                              camera_matrix[10]);
    
    return zc;
}

Vector3 Camera :: getCOP()
{
    return center_of_projection;
}

Vector3 Camera :: getLAP()
{
    return look_at_point;
}

Vector3 Camera :: getUV()
{
    return up_vector;
}

Matrix4 Camera :: getCM()
{
    return camera_matrix;
}

double * Camera :: getCMPointer()
{
    return camera_matrix.getPointer();
}

GLdouble * Camera :: getCMGLPointer()
{
    return camera_matrix.getGLPointer();
}

Matrix4 Camera :: getInverseCM()
{
    return inverse_camera_matrix;
}

double * Camera :: getInverseCMPointer()
{
    return inverse_camera_matrix.getPointer();
}

GLdouble * Camera :: getInverseCMGLPointer()
{
    return inverse_camera_matrix.getGLPointer();
}
