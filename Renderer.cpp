//
//  Renderer.cpp
//  CSE 167 Final Project
//
//  Created by Alex Maragakis on 11/12/2014.
//  Copyright (c) 2014 Gak Industries. All rights reserved.
//

#include "Renderer.h"
#include "Window.h"
#include "main.h"

using namespace Window;

namespace Renderer
{
//Repeatedly called Functions:
    void setUniforms();
    void startProgram();
    
//Initialisation
    void initRenderer();
    void initShaders();
    
//Variables
    GLuint shader_program;
    
    GLint projection_handle;
    GLint camera_modelview_handle;
    
    Matrix4 projection;
    Matrix4 camera_modelview;
};

//****************************************************************
//**
//**   REPEATEDLY CALLED FUNCTIONS:
//**
//****************************************************************

void Renderer :: setUniforms()
{
    projection_handle       = glGetUniformLocation(shader_program, "_projectionMatrix");
    camera_modelview_handle = glGetUniformLocation(shader_program, "_cameraModelViewMatrix");
    
    projection.set(1/(aspect*tan(FOV*PI/360.0)), 0.0, 0.0, 0.0,
                   0.0, 1/tan(FOV*PI/360.0), 0.0, 0.0,
                   0.0, 0.0, (zNear+zFar)/(zNear-zFar), -1.0,
                   0.0, 0.0, (2*zNear*zFar)/(zNear-zFar), 0.0);
    
    camera_modelview = Globals :: camera.getInverseCM();
    
    glUniformMatrix4fv(projection_handle, 1, false, projection.getGLfloatPointer());
    glUniformMatrix4fv(camera_modelview_handle, 1, false, camera_modelview.getGLfloatPointer());}


void Renderer :: startProgram()
{
    glLinkProgram(shader_program);
    glUseProgram(shader_program);
    
    setUniforms();
}


//****************************************************************
//**
//**   SHADER SOURCE COMPILATION:
//**
//****************************************************************

GLchar * getSource(const char * filename)
{
    FILE * fp = fopen(filename, "r");
    
    if(fp == NULL)
    {
        std :: cerr << "Error. Unable to open file: " << filename << "\n";
        exit(0);
    }
    
    GLchar c;
    int num_chars = 0;
    
    while((c = (GLchar)fgetc(fp)) != EOF)
        num_chars++;
    
    rewind(fp);
    
    GLchar * source = (GLchar *) calloc(num_chars, sizeof(GLchar));
    
    int i = 0;
    while((c = (GLchar)fgetc(fp)) != EOF)
    {
        source[i] = c;
        i++;
    }
    
    return source;
}

void compileShader(GLuint shader)
{
    glCompileShader(shader);
    
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    
    if(success == GL_FALSE)
    {
        std :: cerr << "Shader Compilation Error:\n\n";
        
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        
        GLchar errorLog[maxLength];
        glGetShaderInfoLog(shader, maxLength, &maxLength, errorLog);
        
        std :: cerr << errorLog << "\n";
        
        glDeleteShader(shader);
        
        exit(0);
    }
}

//****************************************************************
//**
//**   INITIALISATION:
//**
//****************************************************************

void Renderer :: initShaders()
{
    GLuint vertex_shader   = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    
    const char *fs_filename = { "FragShaderPass2.fs" };
    const char *vs_filename = { "VertShaderPass2.vs" };

    GLchar * fs_source = getSource(fs_filename);
    GLchar * vs_source = getSource(vs_filename);
    
    std :: cout << "Fragment Shader Source: \n" << fs_source;
    std :: cout << "Vertex Shader Source: \n" << vs_source;
    
    const char * fs_source_const = fs_source;
    const char * vs_source_const = vs_source;
    
    glShaderSource(fragment_shader, 1, &fs_source_const, NULL);
    glShaderSource(vertex_shader, 1, &vs_source_const, NULL);
    
    
    compileShader(fragment_shader);
    compileShader(vertex_shader);

    shader_program = glCreateProgram();
    
    glAttachShader(shader_program, fragment_shader);
    glAttachShader(shader_program, vertex_shader);
    
    glLinkProgram(shader_program);
    
}

void Renderer :: initRenderer()
{
    projection.set(1/(aspect*tan(FOV*PI/360.0)), 0.0, 0.0, 0.0,
                   0.0, 1/tan(FOV*PI/360.0), 0.0, 0.0,
                   0.0, 0.0, (zNear+zFar)/(zNear-zFar), -1.0,
                   0.0, 0.0, (2*zNear*zFar)/(zNear-zFar), 0.0);
    
    camera_modelview.makeI();
    initShaders();
}