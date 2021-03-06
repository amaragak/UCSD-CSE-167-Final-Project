//
//  ICCone.cpp
//  CSE 167 Final Project
//
//  Created by Alex Maragakis on 14/12/2014.
//  Copyright (c) 2014 Gak Industries. All rights reserved.
//

#include "ICCone.h"
#include <cmath>

//****************************************************************
//**
//**   CONSTRUCTOR:
//**
//****************************************************************

ICCone :: ICCone()
{
    double ang;
    double rad;
    
//Outside Layer
    for(int row = 0; row<ROW_DIVS; row++)
    {
        rad = ((double)row)*row_sep*tan(angle*M_PI/180);
        for(int col = 0; col<COL_DIVS; col++)
        {
            ang = (2*M_PI)*((double)col)/((double)COL_DIVS);
            
            mesh[row][col][0] = rad*cos(ang);
            mesh[row][col][1] = row*row_sep;
            mesh[row][col][2] = -rad*sin(ang);
            mesh[row][col][3] = 1.0;
        }
    }
    
//Rim
    rad = ((double)(ROW_DIVS-1))*row_sep*tan(angle*M_PI/180) - thickness;
    for(int col = 0; col<COL_DIVS; col++)
    {
        ang = (2*M_PI)*((double)col)/((double)COL_DIVS);
        mesh[ROW_DIVS][col][0] = rad*cos(ang);
        mesh[ROW_DIVS][col][1] = (ROW_DIVS-1)*row_sep;
        mesh[ROW_DIVS][col][2] = -rad*sin(ang);
        mesh[ROW_DIVS][col][3] = 1.0;
    }
    
    top_radius = ((double)(ROW_DIVS-1))*row_sep*tan(angle*M_PI/180) - thickness;
    top_height = (ROW_DIVS-1)*row_sep;
    
//Inside Layer
    for(int row = ROW_DIVS+1; row<2*ROW_DIVS-2; row++)
    {
        rad = ((double)(2*ROW_DIVS-2-row))*row_sep*tan(angle*M_PI/180) - thickness;
        for(int col = 0; col<COL_DIVS; col++)
        {
            ang = (2*M_PI)*((double)col)/((double)COL_DIVS);
            mesh[row][col][0] = rad*cos(ang);
            mesh[row][col][1] = (2*ROW_DIVS-1-row)*row_sep;
            mesh[row][col][2] = -rad*sin(ang);
            mesh[row][col][3] = 1.0;
        }
    }
    
    trans.makeI();
    Vector3 t;
    t.set(-20,-10,-8);
    trans.makeTranslation(t);
    
    rot.makeI();
    
    calcNormals();
}

//****************************************************************
//**
//**   UTILITY:
//**
//****************************************************************

void ICCone :: calcNormals()
{
    for(int col = 0; col<COL_DIVS; col++)
    {
        normals[0][col][0] = 0;
        normals[0][col][1] = -1;
        normals[0][col][2] = 0;
        normals[0][col][3] = 1;
        
        normals[ROW_DIVS*2-1][col][0] = 0;
        normals[ROW_DIVS*2-1][col][1] = 1;
        normals[ROW_DIVS*2-1][col][2] = 0;
        normals[ROW_DIVS*2-1][col][3] = 1;
    }
    
    Vector4 rowt;
    Vector4 colt;
    
    for(int row = 1; row<2*ROW_DIVS-1; row++)
    {
        for(int col = 0; col<COL_DIVS; col++)
        {
            rowt = mesh[row][(col+1)%COL_DIVS] - mesh[row][(col-1)%COL_DIVS];
            colt = mesh[row+1][col] - mesh[row-1][col];
            
            normals[row][col] = rowt.cross(colt);
            normals[row][col].normalise();
        }
    }
}

//****************************************************************
//**
//**   GET FUNCTIONS:
//**
//****************************************************************

int ICCone :: getRowDivs()
{
    return ROW_DIVS;
}

int ICCone :: getColDivs()
{
    return COL_DIVS;
}