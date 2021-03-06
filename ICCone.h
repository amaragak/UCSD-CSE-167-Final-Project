//
//  ICCone.h
//  CSE 167 Final Project
//
//  Created by Alex Maragakis on 14/12/2014.
//  Copyright (c) 2014 Gak Industries. All rights reserved.
//

#ifndef __CSE_167_Final_Project__ICCone__
#define __CSE_167_Final_Project__ICCone__

#include <stdio.h>
#include "Vector4.h"
#include "Matrix4.h"

#define C_PI 3.14159265359
#define ROW_DIVS 10
#define COL_DIVS 20

class ICCone
{
private:
//Private utility funcitons:
    void calcNormals();

public:
//Constructor:
    ICCone();
    
//Get Functions:
    int getRowDivs();
    int getColDivs();
    
//Public Variables
    double angle = 18.0;
    double row_sep = 0.8;
    double thickness = 0.5;
    
    double top_radius;
    double top_height;
    
    Vector4 mesh[ROW_DIVS*2][COL_DIVS];
    Vector4 normals[ROW_DIVS*2][COL_DIVS];
    
    Matrix4 rot;
    Matrix4 trans;
};

#endif /* defined(__CSE_167_Final_Project__ICCone__) */
