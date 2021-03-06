//
//  main.h
//  CSE 167 Final Project
//
//  Created by Alex Maragakis on 09/12/2014.
//  Copyright (c) 2014 Gak Industries. All rights reserved.
//

#ifndef __CSE_167_Final_Project__main__
#define __CSE_167_Final_Project__main__

#include <stdio.h>
#include "BP.h"
#include "Camera.h"
#include "Material.h"
#include "Light.h"
#include "Ball.h"
#include "ICCone.h"

namespace Globals
{
//Global Variables:
    extern BP BezierPatch;
    extern Camera camera;
    extern Material material;
    extern Light light;
    extern Ball ball;
    extern ICCone cone;
    
    extern GLuint vs_program;
    extern GLuint fs_program;
};


#endif /* defined(__CSE_167_Final_Project__main__) */
