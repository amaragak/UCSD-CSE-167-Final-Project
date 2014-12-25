//
//  Ball.h
//  CSE 167 Final Project
//
//  Created by Alex Maragakis on 10/12/2014.
//  Copyright (c) 2014 Gak Industries. All rights reserved.
//

#ifndef __CSE_167_Final_Project__Ball__
#define __CSE_167_Final_Project__Ball__

#include <stdio.h>
#include "Vector4.h"

class Ball
{
public:
//Variables:
    Vector4 position;
    Vector4 velocity;
    Vector4 acceleration;

//Constructor:
    Ball();
};

#endif /* defined(__CSE_167_Final_Project__Ball__) */
