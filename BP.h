//
//  BP.h
//  CSE 167 Final Project
//
//  Created by Alex Maragakis on 10/12/2014.
//  Copyright (c) 2014 Gak Industries. All rights reserved.
//

#ifndef __CSE_167_Final_Project__BP__
#define __CSE_167_Final_Project__BP__

#include <stdio.h>
#include "Vector4.h"

#define MESH_SIZE 90

class BP
{
private:

public:
//Variables
    double point_radius = 0.25;
    
    Vector4 control_points[7][7];
    Vector4 screen_positions[7][7];
    Vector4 mesh_control_points[7][2*MESH_SIZE + 1];
    Vector4 mesh[2*MESH_SIZE + 1][2*MESH_SIZE + 1];
    Vector4 mesh_tangents[2*MESH_SIZE +1][2*MESH_SIZE + 1];
    Vector4 mesh_normals[2*MESH_SIZE +1][2*MESH_SIZE + 1];
    
    int npatchx;
    int npatchy;
    
    double on_screen_radius[7][7];
    
//Constructor:
    BP();

//Get Functions:
    int getMeshSize();
};


#endif /* defined(__CSE_167_Final_Project__BP__) */
