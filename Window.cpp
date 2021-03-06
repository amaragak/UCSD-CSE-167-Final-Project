#include "Window.h"
#include "Renderer.h"
#include <cstdlib>
#include <GLUT/glut.h>
#include "main.h"
#include "ICCone.h"
#include <fstream>

#define DEC_FACTOR_MAX 0.85
#define DEC_FACTOR_MIN 0.1

using namespace Globals;

namespace Window
{
//Load/Save Maps
    void saveMap();
    void loadMap1();
    void loadMap2();

//GLUT Windowing:
    void display();
    void displayCallback();
    void idleCallback();
    void reshapeCallback(int,int);
    
//Process UI:
    void processNormalKeys(unsigned char, int, int);
    void processSpecialKeys(int, int, int);
    void processMouseButtons(int, int, int, int);
    void processMouseMotion(int, int);
    void processPassiveMotion(int, int);
    
//Get/Set/Update/Calculate Values:
    void setPatch();
    void setBall();
    
    void setScreenPosition(int,int);
    void setAllScreenPositions();
    void setScreenPositions();
    void setCurrentPoint(int,int);
    void setInfluentialPoints(double);
    
    void calcMesh();
    void calcNormals();
    
    void updateBall();
    
    void getMeshPosition();
    void getConePosition();
    void getConePosition2();
    
//Draw
    void drawCone();
    void drawMesh();
    void drawNormals();
    void drawBorders();
    void drawLines();
    void drawLines2();
    void drawCPs();
    void drawBall();
    void drawMap();
    
//Variables:
    //Booleans:
    bool left_button;
    bool right_button;
    bool point_selected = false;
    bool marker         = false;
    bool lines_on       = false;
    bool drawnormals_on = false;
    bool paused         = true;
    bool above_cone     = false;

    //Ints and int arrays:
    int influential_points[16];
    
    int n_influential_points;
    int mouse_x;
    int mouse_y;
    int curr_row;
    int curr_col;
    int mesh_size = BezierPatch.getMeshSize();
    int point_sep = 5;
    int width     = 1024;
    int height    = 1024;
    
    //Doubles and double arrays:
    double rowcoldist[3];
    double rowcoldist2[3];
    double mouse_distance[7][7];
    
    double FOV          = 60.0;
    double zNear        = 1.0;
    double zFar         = 1000.0;
    double aspect       = double(width)/(double)height;
    double ball_radius  = 0.9;
    double dec_factor   = DEC_FACTOR_MAX;
    double speed_factor = 0.5;
    double cam_ang      = 0.0;
    double thisy        = 0.0;
    double lasty        = 0.0;
    
    //Matrices and vectors:
    Matrix4 WVP;
    Matrix4 projection;
    Matrix4 viewport;
    Matrix4 modelview;
    
    Vector4 cone_pos;
};

//****************************************************************
//**
//**   LOAD/SAVE MAPS:
//**
//****************************************************************

void Window :: saveMap()
{
    std::ofstream map_file;
    map_file.open("map2.txt");
    
    for(int row = 0; row<7; row++)
    {
        for(int col = 0; col<7; col++)
        {
            map_file << BezierPatch.control_points[row][col][1] << "\n";
        }
    }
    
    map_file.close();
}

void Window :: loadMap2()
{
    FILE * fp = fopen("map2.txt", "r");

    for(int row = 0; row<7; row++)
    {
        for(int col = 0; col<7; col++)
        {
            fscanf(fp, "%lf\n", &BezierPatch.control_points[row][col][1]);
            std :: cout << BezierPatch.control_points[row][col][1] << "\n";
        }
    }
    
    setAllScreenPositions();
    fclose(fp);
}

void Window :: loadMap1()
{
    FILE * fp = fopen("map1.txt", "r");

    for(int row = 0; row<7; row++)
    {
        for(int col = 0; col<7; col++)
        {
            fscanf(fp, "%lf\n", &BezierPatch.control_points[row][col][1]);
            std :: cout << BezierPatch.control_points[row][col][1] << "\n";
        }
    }
    
    setAllScreenPositions();
    fclose(fp);
}


//****************************************************************
//**
//**   DRAW FUNCTIONS:
//**
//****************************************************************

void Window :: drawCone()
{
    Matrix4 matrix = camera.getInverseCM();
    matrix = matrix*cone.trans*cone.rot;
    
    Renderer :: camera_modelview = matrix;

    glUniformMatrix4fv(Renderer :: camera_modelview_handle, 1, false, Renderer :: camera_modelview.getGLfloatPointer());
    
    int rowd = cone.getRowDivs();
    int cold = cone.getColDivs();
    
    glBegin(GL_QUADS);
    
    for(int row = 0; row<2*rowd-4; row++)
    {
        for(int col = 0; col<cold; col++)
        {
            if((col == (int)round(rowcoldist2[1])) && (row == (int)round(rowcoldist2[0])) && marker)
                glColor3f(1.0,0.0,0.0);
            else if(row == rowd-1)
                glColor3f(0.5,0.25,0.1);
            else
                glColor3f(1.0,0.7,0.4);
     
            glNormal3f(cone.normals[row][col%cold][0], cone.normals[row][col%cold][1], cone.normals[row][col%cold][2]);
            glVertex3f(cone.mesh[row][col%cold][0], cone.mesh[row][col%cold][1], cone.mesh[row][col%cold][2]);
            glNormal3f(cone.normals[row][(col+1)%cold][0], cone.normals[row][(col+1)%cold][1], cone.normals[row][(col+1)%cold][2]);
            glVertex3f(cone.mesh[row][(col+1)%cold][0], cone.mesh[row][(col+1)%cold][1], cone.mesh[row][(col+1)%cold][2]);
            glNormal3f(cone.normals[(row+1)][(col+1)%cold][0], cone.normals[(row+1)][(col+1)%cold][1], cone.normals[(row+1)][(col+1)%cold][2]);
            glVertex3f(cone.mesh[(row+1)][(col+1)%cold][0], cone.mesh[(row+1)][(col+1)%cold][1], cone.mesh[(row+1)][(col+1)%cold][2]);
            glNormal3f(cone.normals[(row+1)][col%cold][0], cone.normals[(row+1)][col%cold][1], cone.normals[(row+1)][col%cold][2]);
            glVertex3f(cone.mesh[(row+1)][col%cold][0], cone.mesh[(row+1)][col%cold][1], cone.mesh[(row+1)][col%cold][2]);
        }
    }
    
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glColor3f(0.5,0.25,0.1);
    
    int row = rowd+1;
    
    for(int col = 0; col<cold; col++)
    {
        glNormal3f(0.0,1.0,0.0);
        glVertex3f(cone.mesh[row][col][0], cone.mesh[row][col][1], cone.mesh[row][col][2]);
        glNormal3f(0.0,1.0,0.0);
        glVertex3f(cone.mesh[row][(col+1)%cold][0], cone.mesh[row][(col+1)%cold][1], cone.mesh[row][(col+1)%cold][2]);
        glNormal3f(0.0,1.0,0.0);
        glVertex3f(0.0, cone.mesh[row][(col+1)%cold][1], 0.0);
    }
    
    glEnd();
}

void Window :: drawBorders()
{
    Matrix4 matrix = camera.getInverseCM();
    
    
    Renderer :: camera_modelview = matrix;
    glUniformMatrix4fv(Renderer :: camera_modelview_handle, 1, false, Renderer :: camera_modelview.getGLfloatPointer());
    
    

    glBegin(GL_QUADS);
    glColor3f(0.5,0.2,0.2);

    for(int row = 0; row<2*mesh_size; row++)
    {
//Right Border
        glVertex3f(BezierPatch.mesh[row][2*mesh_size][0],
                   BezierPatch.mesh[row][2*mesh_size][1],
                   BezierPatch.mesh[row][2*mesh_size][2]);
        
        glVertex3f(BezierPatch.mesh[row][2*mesh_size][0],
                   BezierPatch.mesh[row][2*mesh_size][1]-1,
                   BezierPatch.mesh[row][2*mesh_size][2]);
        
        glVertex3f(BezierPatch.mesh[row+1][2*mesh_size][0],
                   BezierPatch.mesh[row+1][2*mesh_size][1]-1,
                   BezierPatch.mesh[row+1][2*mesh_size][2]);
        
        glVertex3f(BezierPatch.mesh[row+1][2*mesh_size][0],
                   BezierPatch.mesh[row+1][2*mesh_size][1],
                   BezierPatch.mesh[row+1][2*mesh_size][2]);
        
//Left Border
        glVertex3f(BezierPatch.mesh[row][0][0],
                   BezierPatch.mesh[row][0][1],
                   BezierPatch.mesh[row][0][2]);
        
        glVertex3f(BezierPatch.mesh[row+1][0][0],
                   BezierPatch.mesh[row+1][0][1],
                   BezierPatch.mesh[row+1][0][2]);
        
        glVertex3f(BezierPatch.mesh[row+1][0][0],
                   BezierPatch.mesh[row+1][0][1]-1,
                   BezierPatch.mesh[row+1][0][2]);
        
        glVertex3f(BezierPatch.mesh[row][0][0],
                   BezierPatch.mesh[row][0][1]-1,
                   BezierPatch.mesh[row][0][2]);
    }
    
    for(int col = 0; col<2*mesh_size; col++)
    {
//Top Border
        glVertex3f(BezierPatch.mesh[2*mesh_size][col][0],
                   BezierPatch.mesh[2*mesh_size][col][1],
                   BezierPatch.mesh[2*mesh_size][col][2]);
        
        glVertex3f(BezierPatch.mesh[2*mesh_size][col+1][0],
                   BezierPatch.mesh[2*mesh_size][col+1][1],
                   BezierPatch.mesh[2*mesh_size][col+1][2]);
        
        glVertex3f(BezierPatch.mesh[2*mesh_size][col+1][0],
                   BezierPatch.mesh[2*mesh_size][col+1][1]-1,
                   BezierPatch.mesh[2*mesh_size][col+1][2]);
        
        glVertex3f(BezierPatch.mesh[2*mesh_size][col][0],
                   BezierPatch.mesh[2*mesh_size][col][1]-1,
                   BezierPatch.mesh[2*mesh_size][col][2]);
        
//Bottom Border
        glVertex3f(BezierPatch.mesh[0][col+1][0],
                   BezierPatch.mesh[0][col+1][1],
                   BezierPatch.mesh[0][col+1][2]);
        
        glVertex3f(BezierPatch.mesh[0][col][0],
                   BezierPatch.mesh[0][col][1],
                   BezierPatch.mesh[0][col][2]);
        
        glVertex3f(BezierPatch.mesh[0][col][0],
                   BezierPatch.mesh[0][col][1]-1,
                   BezierPatch.mesh[0][col][2]);
        
        glVertex3f(BezierPatch.mesh[0][col+1][0],
                   BezierPatch.mesh[0][col+1][1]-1,
                   BezierPatch.mesh[0][col+1][2]);
    }
    
    glEnd();
}

void Window :: drawNormals()
{
    Matrix4 matrix = camera.getInverseCM();
    
    Renderer :: camera_modelview = matrix;
    glUniformMatrix4fv(Renderer :: camera_modelview_handle, 1, false, Renderer :: camera_modelview.getGLfloatPointer());
    

    glBegin(GL_LINES);
    glColor3f(0.0,1.0,0.0);
    
    for(int col = 0; col<=2*mesh_size; col++)
    {
        for(int row = 0; row<=2*mesh_size; row++)
        {
            glVertex3f(BezierPatch.mesh[row][col][0],
                       BezierPatch.mesh[row][col][1],
                       BezierPatch.mesh[row][col][2]);
            
            glVertex3f(BezierPatch.mesh[row][col][0] + BezierPatch.mesh_normals[row][col][0],
                       BezierPatch.mesh[row][col][1] + BezierPatch.mesh_normals[row][col][1],
                       BezierPatch.mesh[row][col][2] + BezierPatch.mesh_normals[row][col][2]);
        }
    }
    
    cone_pos.set(0.0,0.0,0.0,1.0);
    cone_pos = cone.trans*cone_pos;
    
    glColor3f(1.0,0.0,0.0);
    
    for(int col = 0; col<cone.getColDivs(); col++)
    {
        for(int row = 0; row<2*cone.getRowDivs()-4; row++)
        {
            glVertex3f(cone.mesh[row][col][0] + cone_pos[0],
                       cone.mesh[row][col][1] + cone_pos[1],
                       cone.mesh[row][col][2] + cone_pos[2]);
            
            glVertex3f(cone.mesh[row][col][0] + cone.normals[row][col][0] + cone_pos[0],
                       cone.mesh[row][col][1] + cone.normals[row][col][1] + cone_pos[1],
                       cone.mesh[row][col][2] + cone.normals[row][col][2] + cone_pos[2]);
        }
    }
    
    glEnd();
}

void Window :: drawMesh()
{
    Matrix4 matrix = camera.getInverseCM();
    
    Renderer :: camera_modelview = matrix;
     glUniformMatrix4fv(Renderer :: camera_modelview_handle, 1, false, Renderer :: camera_modelview.getGLfloatPointer());
    

    glBegin(GL_QUADS);
    
    for(int col = 0; col<2*mesh_size; col++)
    {
        for(int row = 0; row<2*mesh_size; row++)
        {
            if(col < 3 || col > 2*mesh_size-4 || row < 3 || row > 2*mesh_size-3)
                glColor3f(1.0,0.5,0.5);
            else if((col%30 < 1) || (row%30 < 1))
                glColor3f(0.9,0.9,0.9);
            else if((row == (int)round(rowcoldist[0])) && (col == (int)round(rowcoldist[1])) && marker)
                glColor3f(1.0,0.0,0.0);
            else
                glColor3f(1.0,1.0,1.0);
        
            glNormal3f(BezierPatch.mesh_normals[row][col][0],
                       BezierPatch.mesh_normals[row][col][1],
                       BezierPatch.mesh_normals[row][col][2]);
        
            glVertex3f(BezierPatch.mesh[row][col][0],
                       BezierPatch.mesh[row][col][1],
                       BezierPatch.mesh[row][col][2]);

            glNormal3f(BezierPatch.mesh_normals[row][col+1][0],
                       BezierPatch.mesh_normals[row][col+1][1],
                       BezierPatch.mesh_normals[row][col+1][2]);
            
            glVertex3f(BezierPatch.mesh[row][col+1][0],
                       BezierPatch.mesh[row][col+1][1],
                       BezierPatch.mesh[row][col+1][2]);
            
            glNormal3f(BezierPatch.mesh_normals[row+1][col+1][0],
                       BezierPatch.mesh_normals[row+1][col+1][1],
                       BezierPatch.mesh_normals[row+1][col+1][2]);
            
            glVertex3f(BezierPatch.mesh[row+1][col+1][0],
                       BezierPatch.mesh[row+1][col+1][1],
                       BezierPatch.mesh[row+1][col+1][2]);

            glNormal3f(BezierPatch.mesh_normals[row+1][col][0],
                       BezierPatch.mesh_normals[row+1][col][1],
                       BezierPatch.mesh_normals[row+1][col][2]);

            glVertex3f(BezierPatch.mesh[row+1][col][0],
                       BezierPatch.mesh[row+1][col][1],
                       BezierPatch.mesh[row+1][col][2]);
        }
    }
    
    for(int col = 0; col<2*mesh_size; col++)
    {
        for(int row = 0; row<2*mesh_size; row++)
        {
            glColor3f(0.5,0.2,0.2);
        
            glNormal3f(-BezierPatch.mesh_normals[row][col][0],
                       -BezierPatch.mesh_normals[row][col][1],
                       -BezierPatch.mesh_normals[row][col][2]);
        
            glVertex3f(BezierPatch.mesh[row][col][0],
                       BezierPatch.mesh[row][col][1]-1,
                       BezierPatch.mesh[row][col][2]);

            glNormal3f(-BezierPatch.mesh_normals[row][col+1][0],
                       -BezierPatch.mesh_normals[row][col+1][1],
                       -BezierPatch.mesh_normals[row][col+1][2]);
            
            glVertex3f(BezierPatch.mesh[row][col+1][0],
                       BezierPatch.mesh[row][col+1][1]-1,
                       BezierPatch.mesh[row][col+1][2]);
            
            glNormal3f(-BezierPatch.mesh_normals[row+1][col+1][0],
                       -BezierPatch.mesh_normals[row+1][col+1][1],
                       -BezierPatch.mesh_normals[row+1][col+1][2]);
            
            glVertex3f(BezierPatch.mesh[row+1][col+1][0],
                       BezierPatch.mesh[row+1][col+1][1]-1,
                       BezierPatch.mesh[row+1][col+1][2]);

            glNormal3f(-BezierPatch.mesh_normals[row+1][col][0],
                       -BezierPatch.mesh_normals[row+1][col][1],
                       -BezierPatch.mesh_normals[row+1][col][2]);

            glVertex3f(BezierPatch.mesh[row+1][col][0],
                       BezierPatch.mesh[row+1][col][1]-1,
                       BezierPatch.mesh[row+1][col][2]);
        }
    }
    
    glEnd();
}

void Window :: drawLines2()
{
    Matrix4 matrix = camera.getInverseCM();
    
    Renderer :: camera_modelview = matrix;
    glUniformMatrix4fv(Renderer :: camera_modelview_handle, 1, false, Renderer :: camera_modelview.getGLfloatPointer());
    
    
    glBegin(GL_LINES);
    
    glColor3f(1.0, 1.0, 1.0);
    
    for (int row = 0; row < 6; row++)
    {
        for (int col = 0; col < 6; col++)
        {
            glVertex3f((float)BezierPatch.control_points[row][col][0],
                       (float)BezierPatch.control_points[row][col][1],
                       (float)BezierPatch.control_points[row][col][2]);
            
            glVertex3f((float)BezierPatch.control_points[row+1][col][0],
                       (float)BezierPatch.control_points[row+1][col][1],
                       (float)BezierPatch.control_points[row+1][col][2]);
            
            glVertex3f((float)BezierPatch.control_points[row][col][0],
                       (float)BezierPatch.control_points[row][col][1],
                       (float)BezierPatch.control_points[row][col][2]);
            
            glVertex3f((float)BezierPatch.control_points[row][col+1][0],
                       (float)BezierPatch.control_points[row][col+1][1],
                       (float)BezierPatch.control_points[row][col+1][2]);
            
            glVertex3f((float)BezierPatch.control_points[row+1][col+1][0],
                       (float)BezierPatch.control_points[row+1][col+1][1],
                       (float)BezierPatch.control_points[row+1][col+1][2]);
            
            glVertex3f((float)BezierPatch.control_points[row][col+1][0],
                       (float)BezierPatch.control_points[row][col+1][1],
                       (float)BezierPatch.control_points[row][col+1][2]);
            
            glVertex3f((float)BezierPatch.control_points[row+1][col+1][0],
                       (float)BezierPatch.control_points[row+1][col+1][1],
                       (float)BezierPatch.control_points[row+1][col+1][2]);
            
            glVertex3f((float)BezierPatch.control_points[row+1][col][0],
                       (float)BezierPatch.control_points[row+1][col][1],
                       (float)BezierPatch.control_points[row+1][col][2]);
        }
    }
    
    glEnd();
}

void Window :: drawLines()
{
    Matrix4 matrix = camera.getInverseCM();
    
    Renderer :: camera_modelview = matrix;
    glUniformMatrix4fv(Renderer :: camera_modelview_handle, 1, false, Renderer :: camera_modelview.getGLfloatPointer());
    
    
    glBegin(GL_LINES);
    
    for (int row = 0; row < 7; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            glVertex3f((float)BezierPatch.control_points[row][col][0],
                       (float)BezierPatch.control_points[row][col][1],
                       (float)BezierPatch.control_points[row][col][2]);
            
            glVertex3f((float)BezierPatch.control_points[row][col][0],
                       (float)BezierPatch.mesh[row*30][col*30][1],
                       (float)BezierPatch.control_points[row][col][2]);
        }
    }
    
    glEnd();
}

//Translate balls to high position so that they can always be seen
void Window :: drawCPs()
{
    Matrix4 matrix;
    Matrix4 t_mat;
    Vector3 trans;
    
    
    for (int row = 0; row < 7; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            trans.set(BezierPatch.control_points[row][col][0],
                      BezierPatch.control_points[row][col][1],
                      BezierPatch.control_points[row][col][2]);
            
            t_mat.makeTranslation(trans);
                
            matrix = camera.getInverseCM()*t_mat;
            
            Renderer :: camera_modelview = matrix;
            glUniformMatrix4fv(Renderer :: camera_modelview_handle, 1, false, Renderer :: camera_modelview.getGLfloatPointer());
            
            
            if((row == curr_row) && (col == curr_col) && point_selected)
                glColor3f(0.0, 0.0, 1.0);
                
            else if (((row == 0) || (row == 3) || (row == 6)) &&
                     ((col == 0) || (col == 3) || (col == 6)))
                glColor3f(1.0, 1.0, 1.0);
                
            else
                glColor3f(1.0, 1.0, 1.0);
             
            glutSolidSphere(BezierPatch.point_radius, 10, 10);
        }
    }
}

void Window :: drawBall()
{
    Matrix4 matrix;
    Matrix4 t_mat;
    Vector3 trans;
    trans.set(ball.position[0], ball.position[1], ball.position[2]);
    t_mat.makeTranslation(trans);
    matrix = camera.getInverseCM()*t_mat;
    Renderer :: camera_modelview = matrix;
    glUniformMatrix4fv(Renderer :: camera_modelview_handle, 1, false, Renderer :: camera_modelview.getGLfloatPointer());
    
    glColor3f(0.9,0.1,0.6);
    glutSolidSphere(ball_radius, 20, 20);
    
    
    matrix.makeI();
    Renderer :: camera_modelview = matrix;
    glUniformMatrix4fv(Renderer :: camera_modelview_handle, 16, false, Renderer :: camera_modelview.getGLfloatPointer());
    
    
}

//****************************************************************
//**
//**   GLUT WINDOWING:
//**
//****************************************************************


void Window :: displayCallback()
{
    calcMesh();
    
    if(!paused)
        updateBall();
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0,0,width,height);
    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glUseProgram(Renderer :: shader_program);
    
    Renderer :: setUniforms();
    display();
        
    glBindTexture(GL_TEXTURE_2D, 0);

    glutSwapBuffers();
}

void Window :: display()
{
    if(lines_on)
    {
        drawCPs();
        drawLines2();
    }
    
    if(drawnormals_on)
        drawNormals();
    
    drawMesh();
    drawBorders();
    
    drawBall();
    
    drawCone();
}

void Window :: reshapeCallback(int w, int h)
{
    width  = w;
    height = h;
    
    aspect = double(width)/(double)height;
    
    Renderer :: projection.set(1/(aspect*tan(FOV*PI/360.0)), 0.0, 0.0, 0.0,
                                   0.0, 1/tan(FOV*PI/360.0), 0.0, 0.0,
                                   0.0, 0.0, (zNear+zFar)/(zNear-zFar), -1.0,
                                   0.0, 0.0, (2*zNear*zFar)/(zNear-zFar), 0.0);
    
    glUniformMatrix4fv(Renderer :: projection_handle, 1, false, Renderer :: projection.getGLfloatPointer());
    
    setAllScreenPositions();
}

void Window :: idleCallback()
{
    displayCallback();
}

//****************************************************************
//**
//**   GET/SET/UPDATE/CALCULATE VALUES:
//**
//****************************************************************

void Window :: setAllScreenPositions()
{
    for(int row=0; row<7; row++)
    {
        for(int col=0; col<7; col++)
        {
            setScreenPosition(row,col);
        }
    }
}

void Window :: setPatch()
{
    for(int row = 0; row < 7; row++)
    {
        for(int col = 0; col < 7; col++)
        {
            BezierPatch.control_points[row][col].set((double)((col-3)*6), 0.0, (double)(-(row-3)*4), 1.0);
        }
    }
}

void Window :: calcMesh()
{
    double t;
    Vector4 a, b, c, d;
    
    int row_meshoffset;
    int col_meshoffset;
    
    for(int row_offset = 0; row_offset<=3; row_offset += 3)
    {
    for(int col_offset = 0; col_offset<=3; col_offset += 3)
    {
    
    row_meshoffset = (row_offset/3)*mesh_size;
    col_meshoffset = (col_offset/3)*mesh_size;
    
    for(int row = 0; row<4; row++)
    {
        a = BezierPatch.control_points[row+row_offset][3+col_offset] -
            BezierPatch.control_points[row+row_offset][2+col_offset].scale(3) +
            BezierPatch.control_points[row+row_offset][1+col_offset].scale(3) -
            BezierPatch.control_points[row+row_offset][0+col_offset];
        
        b = BezierPatch.control_points[row+row_offset][2+col_offset].scale(3) -
            BezierPatch.control_points[row+row_offset][1+col_offset].scale(6) +
            BezierPatch.control_points[row+row_offset][0+col_offset].scale(3);
        
        c = BezierPatch.control_points[row+row_offset][1+col_offset].scale(3) -
            BezierPatch.control_points[row+row_offset][0+col_offset].scale(3);
        
        d = BezierPatch.control_points[row+row_offset][0+col_offset];
    
        BezierPatch.mesh_control_points[row+row_offset][0+col_meshoffset] = BezierPatch.control_points[row+row_offset][0+col_offset];
        BezierPatch.mesh_control_points[row+row_offset][mesh_size+col_meshoffset] = BezierPatch.control_points[row+row_offset][3+col_offset];
    
        for(int col = 1; col<mesh_size; col++)
        {
            t = col/((double)(mesh_size));
            BezierPatch.mesh_control_points[row+row_offset][col+col_meshoffset] = a.scale(t*t*t) + b.scale(t*t) + c.scale(t) + d;
        }
    }
    
    //Rest of Mesh
    for(int col = 0; col<=mesh_size; col++)
    {
        a = BezierPatch.mesh_control_points[3+row_offset][col+col_meshoffset] -
            BezierPatch.mesh_control_points[2+row_offset][col+col_meshoffset].scale(3) +
            BezierPatch.mesh_control_points[1+row_offset][col+col_meshoffset].scale(3) -
            BezierPatch.mesh_control_points[0+row_offset][col+col_meshoffset];
        
        b = BezierPatch.mesh_control_points[2+row_offset][col+col_meshoffset].scale(3) -
            BezierPatch.mesh_control_points[1+row_offset][col+col_meshoffset].scale(6) +
            BezierPatch.mesh_control_points[0+row_offset][col+col_meshoffset].scale(3);
        
        c = BezierPatch.mesh_control_points[1+row_offset][col+col_meshoffset].scale(3) -
            BezierPatch.mesh_control_points[0+row_offset][col+col_meshoffset].scale(3);
        
        d = BezierPatch.mesh_control_points[0+row_offset][col+col_meshoffset];
        
        for(int row = 0; row<=mesh_size; row++)
        {
            t = row/((double)(mesh_size));
            BezierPatch.mesh[row+row_meshoffset][col+col_meshoffset] = a.scale(t*t*t) + b.scale(t*t) + c.scale(t) + d;
            BezierPatch.mesh[row+row_meshoffset][col+col_meshoffset][1] -= point_sep;
        }
    }
    
    }
    }
    
    calcNormals();
}

void Window :: calcNormals()
{
    Vector4 row_tangent;
    Vector4 col_tangent;

    for(int row = 1; row<2*mesh_size; row++)
    {
        for(int col = 1; col<2*mesh_size; col++)
        {
            row_tangent = BezierPatch.mesh[row][col+1] - BezierPatch.mesh[row][col-1];
            col_tangent = BezierPatch.mesh[row+1][col] - BezierPatch.mesh[row-1][col];
            
            row_tangent.normalise();
            col_tangent.normalise();
            
            BezierPatch.mesh_normals[row][col] = row_tangent.cross(col_tangent);
            BezierPatch.mesh_normals[row][col].normalise();
        }
    }
    
    for(int row = 1; row<2*mesh_size; row++)
    {
        BezierPatch.mesh_normals[row][0] = BezierPatch.mesh_normals[row][1];
        BezierPatch.mesh_normals[row][2*mesh_size] = BezierPatch.mesh_normals[row][2*mesh_size-1];
    }
    
    for(int col = 1; col<2*mesh_size; col++)
    {
        BezierPatch.mesh_normals[0][col] = BezierPatch.mesh_normals[1][col];
        BezierPatch.mesh_normals[2*mesh_size][col] = BezierPatch.mesh_normals[2*mesh_size-1][col];
    }
    
    BezierPatch.mesh_normals[0][0] =
        BezierPatch.mesh_normals[0][1]+BezierPatch.mesh_normals[1][0];
    BezierPatch.mesh_normals[0][0].normalise();
    
    BezierPatch.mesh_normals[0][2*mesh_size] =
        BezierPatch.mesh_normals[0][2*mesh_size-1]+BezierPatch.mesh_normals[1][2*mesh_size];
    BezierPatch.mesh_normals[0][2*mesh_size].normalise();
    
    BezierPatch.mesh_normals[2*mesh_size][0] =
        BezierPatch.mesh_normals[2*mesh_size][1]+BezierPatch.mesh_normals[2*mesh_size-1][0];
    BezierPatch.mesh_normals[2*mesh_size][0].normalise();
    
    BezierPatch.mesh_normals[2*mesh_size][2*mesh_size] =
        BezierPatch.mesh_normals[2*mesh_size][2*mesh_size-1]+BezierPatch.mesh_normals[2*mesh_size-1][2*mesh_size];
    BezierPatch.mesh_normals[2*mesh_size][2*mesh_size].normalise();
}

void Window :: getMeshPosition()
{
    Vector4 mesh_bl = BezierPatch.mesh[0][0];
    Vector4 mesh_tr = BezierPatch.mesh[2*mesh_size][2*mesh_size];

    double col_ratio = (ball.position[0]-mesh_bl[0])/(mesh_tr[0]-mesh_bl[0]);
    double row_ratio = (ball.position[2]-mesh_bl[2])/(mesh_tr[2]-mesh_bl[2]);
    
    if(!((col_ratio < 0) || (row_ratio < 0)))
    {
    
        double col = col_ratio*2*mesh_size;
        double row = row_ratio*2*mesh_size;
        
        //we now have the col/row positions that are nearest
        //now check surrounding boxes
        
        int col_direct = round(col);
        int row_direct = round(row);
        
        double mesh_dist[5][5];
        double lowest_dist;
        
        for(int r=0; r<5; r++)
        {
            for(int c=0; c<5; c++)
            {
                mesh_dist[r][c] = (ball.position - BezierPatch.mesh[row_direct-2+r][col_direct-2+c]).magnitude();
            }
        }
        
        lowest_dist = mesh_dist[0][0];
        
        for(int r=0; r<5; r++)
        {
            for(int c=0; c<5; c++)
            {
                if(mesh_dist[r][c] < lowest_dist)
                {
                    lowest_dist = mesh_dist[r][c];
                    row = (double)(row_direct-2+r);
                    col = (double)(col_direct-2+c);
                }
            }
        }
        
        row = row_ratio*2*mesh_size;
        col = col_ratio*2*mesh_size;
        
        rowcoldist[0] = row;
        rowcoldist[1] = col;
        rowcoldist[2] = lowest_dist;
    
        if(ball.position[1] < BezierPatch.mesh[(int)round(row)][(int)round(col)][1])
            lowest_dist *= -1;
    }
    else
    {
        rowcoldist[0] = 0;
        rowcoldist[1] = 0;
        rowcoldist[2] = 200;
    }
    
}

void Window :: getConePosition()
{
    //Cone tip coordinates
    cone_pos.set(0.0,0.0,0.0,1.0);
    cone_pos = cone.trans*cone_pos;
    
    //Angle between ball and x axis with cone as pivot
    double angle = atan2(-(ball.position[2]-cone_pos[2]),ball.position[0]-cone_pos[0]);
    
    //Diffence in height between ball centre and corresponding point on cone
    double height_diff = ball_radius*sin(cone.angle*PI/180);
    
    //Difference in height between ball centre and bottom of cone
    double height_disp = ball.position[1] - cone_pos[1];
    
    double rowdouble = (height_disp + height_diff)/cone.row_sep;
    rowcoldist2[0] = round(rowdouble);
    
    double coldouble = COL_DIVS*angle/(2*PI);
    rowcoldist2[1] = round(coldouble);
    
    double dx = ball.position[0] - (cone.mesh[(int)rowcoldist2[0]][(int)rowcoldist2[1]][0] + cone_pos[0]);
    double dy = ball.position[1] - (cone.mesh[(int)rowcoldist2[0]][(int)rowcoldist2[1]][1] + cone_pos[1]);
    double dz = ball.position[2] - (cone.mesh[(int)rowcoldist2[0]][(int)rowcoldist2[1]][2] + cone_pos[2]);
    
    rowcoldist2[2] = sqrt(dx*dx + dy*dy + dz*dz);
    
    //std :: cout << rowcoldist[2] << "\n";
    
}

void Window :: getConePosition2()
{
    //Cone tip coordinates
    cone_pos.set(0.0,0.0,0.0,1.0);
    cone_pos = cone.trans*cone_pos;
    
    //Angle between ball and x axis with cone as pivot
    double angle = atan2(-(ball.position[2]-cone_pos[2]),ball.position[0]-cone_pos[0]);
    
    //Diffence in height between ball centre and corresponding point on cone
    double height_diff = ball_radius*sin(cone.angle*PI/180);
    
    //Difference in height between ball centre and bottom of cone
    double height_disp = ball.position[1] - cone_pos[1];
    
    double rowdouble = (height_disp + height_diff)/cone.row_sep;
    rowcoldist2[0] = round(rowdouble);
    
    double coldouble = COL_DIVS*angle/(2*PI);
    rowcoldist2[1] = round(coldouble);
    
    double dx = ball.position[0] - (cone.mesh[(int)rowcoldist2[0]][(int)rowcoldist2[1]][0] + cone_pos[0]);
    double dy = ball.position[1] - (cone.mesh[(int)rowcoldist2[0]][(int)rowcoldist2[1]][1] + cone_pos[1]);
    double dz = ball.position[2] - (cone.mesh[(int)rowcoldist2[0]][(int)rowcoldist2[1]][2] + cone_pos[2]);
    
    rowcoldist2[2] = sqrt(dx*dx + dy*dy + dz*dz);
    
    std :: cout << rowcoldist2[2] << "\n";
    
}

void Window :: updateBall()
{
    lasty = thisy;

    ball.velocity = ball.velocity + ball.acceleration.scale(speed_factor);
    ball.position = ball.position + ball.velocity;
    thisy = ball.velocity[1];

    getMeshPosition();
    
    double rowf = rowcoldist[0] - (double)((int)rowcoldist[0]);
    double colf = rowcoldist[1] - (double)((int)rowcoldist[1]);
    
    int row = (int)round(rowcoldist[0]);
    int col = (int)round(rowcoldist[1]);
    
    bool towards_patch = BezierPatch.mesh_normals[row][col].dot(ball.velocity) < 0;
    
    if(towards_patch && (rowcoldist[2] < ball_radius))
    {
        Vector4 incidence  = ball.velocity;
        Vector4 normal     = BezierPatch.mesh_normals[row][col];
        Vector4 reflection = incidence - normal.scale(2*(normal.dot(incidence)));
        
        double incident_mag = incidence.magnitude();
        double reflection_mag = reflection.magnitude();
        
        ball.velocity = reflection.scale(dec_factor*incident_mag/reflection_mag);
        thisy = ball.velocity[1];
        
        Vector4 up;
        up.set(0.0,1.0,0.0,1.0);
        
        double zxmag = sqrt(ball.velocity[0]*ball.velocity[0] + ball.velocity[2]*ball.velocity[2]);
        
        if(zxmag < 0.001)
        {
            ball.position[0] = ball.position[0];
            ball.position[1] = BezierPatch.mesh[row][col][1] + ball.velocity[1] + ball_radius;
            ball.position[2] = ball.position[2];
        }
        
    }
    
    bool towards_cone = false;
    
    bool cone_bounce = ball.position[1] < cone_pos[1] + cone.top_height;
    
    if(cone_bounce)
    {
        getConePosition();
    
        row = (int)round(rowcoldist2[0]);
        col = (int)round(rowcoldist2[1]);
    
        towards_cone = cone.normals[row][col].dot(ball.velocity) < 0;
    
        if(towards_cone && (rowcoldist2[2] < ball_radius))
        {
            Vector4 incidence  = ball.velocity;
            Vector4 normal     = cone.normals[row][col];
            Vector4 reflection = incidence - normal.scale(2*(normal.dot(incidence)));
        
            double incident_mag = incidence.magnitude();
            double reflection_mag = reflection.magnitude();
        
            ball.velocity = reflection.scale(1.0,dec_factor*incident_mag/reflection_mag,1.0);
            thisy = ball.velocity[1];
        
            std :: cerr <<"COLLISION\n";
        }
    }
    
    double xzdist, dx, dz;
    dx = ball.position[0] - cone_pos[0];
    dz = ball.position[2] - cone_pos[2];
    xzdist = sqrt(dx*dx + dz*dz);
    
    above_cone = ((xzdist < cone.top_radius) && (ball.position[1] > cone_pos[1] + cone.top_height));
    
    //i.e. was above cone at last pass
    if(above_cone)
    {
        dec_factor = DEC_FACTOR_MIN;
    
        double ydist = ball.position[1] - (cone_pos[1] + cone.mesh[cone.getRowDivs()+1][0][1]);
        
        if(ydist < ball_radius)
        {
            Vector4 incidence  = ball.velocity;
            Vector4 normal;
            normal.set(0.0,1.0,0.0,1.0);
            Vector4 reflection = incidence - normal.scale(2*(normal.dot(incidence)));
        
            double incident_mag = incidence.magnitude();
            double reflection_mag = reflection.magnitude();
        
            ball.velocity = reflection.scale(dec_factor*incident_mag/reflection_mag);
            thisy = ball.velocity[1];
            
            ball.position[0] = ball.position[0];
            ball.position[1] = cone_pos[1] + cone.mesh[cone.getRowDivs()+1][0][1] + ball_radius;
            ball.position[2] = ball.position[2];
        }
    }
    else
        dec_factor = DEC_FACTOR_MAX;
}

void Window :: setScreenPosition(int row, int col)
{
    int elements = 0;
    int positions[18];
    
    positions[0] = row;
    positions[1] = col;
    elements += 1;
    
    double x0 = 0.0;
    double y0 = 0.0;
    double x1 = (double)width;
    double y1 = (double)height;
    
    viewport.set((x1-x0)/2.0, 0.0, 0.0, 0.0,
                 0.0, (y1-y0)/2.0, 0.0, 0.0,
                 0.0, 0.0, 0.5, 0.0,
                 (x0+x1)/2.0, (y0+y1)/2.0, 0.5, 1.0);
    
    projection.set(1/(aspect*tan(FOV*PI/360.0)), 0.0, 0.0, 0.0,
                   0.0, 1/tan(FOV*PI/360.0), 0.0, 0.0,
                   0.0, 0.0, (zNear+zFar)/(zNear-zFar), -1.0,
                   0.0, 0.0, (2*zNear*zFar)/(zNear-zFar), 0.0);
    
    modelview = camera.getInverseCM();
    
    Vector4 ori_vec;
    Vector4 rad_vec;
    Vector4 res_vec;

    BezierPatch.screen_positions[row][col] =
            projection*(modelview*BezierPatch.control_points[row][col]);
    BezierPatch.screen_positions[row][col].dehomogenize();
    BezierPatch.screen_positions[row][col] =
        viewport*BezierPatch.screen_positions[row][col];
    
    rad_vec.set(BezierPatch.point_radius + BezierPatch.screen_positions[row][col][0],
                BezierPatch.screen_positions[row][col][1],
                BezierPatch.screen_positions[row][col][2],
                1.0);
    
    rad_vec = projection*(modelview*rad_vec);
    rad_vec.dehomogenize();
    rad_vec = viewport*rad_vec;
    
    ori_vec.set(BezierPatch.screen_positions[row][col][0],
                BezierPatch.screen_positions[row][col][1],
                BezierPatch.screen_positions[row][col][2],
                1.0);
    
    ori_vec = projection*(modelview*ori_vec);
    ori_vec.dehomogenize();
    ori_vec = viewport*ori_vec;

    res_vec = rad_vec - ori_vec;

    BezierPatch.on_screen_radius[row][col] = res_vec.magnitude();
}

void Window :: setCurrentPoint(int x, int y)
{
    y = height - y;

    mouse_x = x;
    mouse_y = y;

    for(int row = 0; row<7; row++)
    {
        for(int col = 0; col<7; col++)
        {
            if(mouse_distance[row][col] < 4*BezierPatch.on_screen_radius[row][col])
            {
                curr_row = row;
                curr_col = col;
                
                point_selected = true;
                return;
            }
            
            else
            {
                point_selected = false;
            }
        }
    }
}

void Window :: setScreenPositions()
{
    setScreenPosition(curr_row, curr_col);
    
    for(int i = 0; i<n_influential_points; i++)
        setScreenPosition(influential_points[2*i],influential_points[2*i+1]);
}

void Window :: setInfluentialPoints(double dy)
{
//C1: Continuity
        
    //If central point, all surrounding points are influenced
        if(curr_row == 3 && curr_col == 3)
        {
            BezierPatch.control_points[2][2][1] += dy;
            BezierPatch.control_points[2][3][1] += dy;
            BezierPatch.control_points[2][4][1] += dy;
            BezierPatch.control_points[3][2][1] += dy;
            BezierPatch.control_points[3][4][1] += dy;
            BezierPatch.control_points[4][2][1] += dy;
            BezierPatch.control_points[4][3][1] += dy;
            BezierPatch.control_points[4][4][1] += dy;
            
            influential_points[0] = 2;
            influential_points[1] = 2;
            
            influential_points[2] = 2;
            influential_points[3] = 3;
            
            influential_points[4] = 2;
            influential_points[5] = 4;
            
            influential_points[6] = 3;
            influential_points[7] = 2;
            
            influential_points[8]  = 3;
            influential_points[9]  = 4;
            
            influential_points[10] = 4;
            influential_points[11] = 2;
            
            influential_points[12] = 4;
            influential_points[13] = 3;
            
            influential_points[14] = 4;
            influential_points[15] = 4;
            
            n_influential_points = 8;
        }
        
    //If 'edge' point of inside square, opposite edge and corners influenced
        else if(curr_row == 3 && curr_col == 2)
        {
            //Opposite edge
            BezierPatch.control_points[3][4][1] -= dy;
        
            //Corners
            BezierPatch.control_points[2][2][1] += dy;
            BezierPatch.control_points[4][2][1] += dy;
            BezierPatch.control_points[4][4][1] -= dy;
            BezierPatch.control_points[2][4][1] -= dy;
            
            influential_points[0] = 3;
            influential_points[1] = 4;
            
            influential_points[2] = 2;
            influential_points[3] = 2;
            
            influential_points[4] = 4;
            influential_points[5] = 2;
            
            influential_points[6] = 4;
            influential_points[7] = 4;
            
            influential_points[8]  = 2;
            influential_points[9]  = 4;
            
            n_influential_points = 5;
        }
        else if(curr_row == 3 && curr_col == 4)
        {
            //Opposite edge
            BezierPatch.control_points[3][2][1] -= dy;
        
            //Corners
            BezierPatch.control_points[2][4][1] += dy;
            BezierPatch.control_points[4][4][1] += dy;
            BezierPatch.control_points[4][2][1] -= dy;
            BezierPatch.control_points[2][2][1] -= dy;
            
            influential_points[0] = 3;
            influential_points[1] = 2;
            
            influential_points[2] = 2;
            influential_points[3] = 4;
            
            influential_points[4] = 4;
            influential_points[5] = 4;
            
            influential_points[6] = 4;
            influential_points[7] = 2;
            
            influential_points[8]  = 2;
            influential_points[9]  = 2;
            
            n_influential_points = 5;
        }
        else if(curr_row == 2 && curr_col == 3)
        {
            //Opposite edge
            BezierPatch.control_points[4][3][1] -= dy;
            
            //Corners
            BezierPatch.control_points[2][2][1] += dy;
            BezierPatch.control_points[2][4][1] += dy;
            BezierPatch.control_points[4][4][1] -= dy;
            BezierPatch.control_points[4][2][1] -= dy;
            
            influential_points[0] = 4;
            influential_points[1] = 3;
            
            influential_points[2] = 2;
            influential_points[3] = 2;
            
            influential_points[4] = 2;
            influential_points[5] = 4;
            
            influential_points[6] = 4;
            influential_points[7] = 4;
            
            influential_points[8]  = 4;
            influential_points[9]  = 2;
            
            n_influential_points = 5;
        }
        else if(curr_row == 4 && curr_col == 3)
        {
            //Opposite edge
            BezierPatch.control_points[2][3][1] -= dy;
            
            //Corners
            BezierPatch.control_points[4][2][1] += dy;
            BezierPatch.control_points[4][4][1] += dy;
            BezierPatch.control_points[2][4][1] -= dy;
            BezierPatch.control_points[2][2][1] -= dy;
            
            influential_points[0] = 2;
            influential_points[1] = 3;
            
            influential_points[2] = 4;
            influential_points[3] = 2;
            
            influential_points[4] = 4;
            influential_points[5] = 4;
            
            influential_points[6] = 2;
            influential_points[7] = 4;
            
            influential_points[8]  = 2;
            influential_points[9]  = 2;
            
            n_influential_points = 5;
        }
        
    //If 'corner' point of inside square, all corners influenced
        else if(curr_row == 2 && curr_col == 2)
        {
            //Other corners:
            BezierPatch.control_points[2][4][1] -= dy;
            BezierPatch.control_points[4][2][1] -= dy;
            BezierPatch.control_points[4][4][1] += dy;
            
            influential_points[0] = 2;
            influential_points[1] = 4;
            
            influential_points[2] = 4;
            influential_points[3] = 2;
            
            influential_points[4] = 4;
            influential_points[5] = 4;
            
            n_influential_points = 3;
        }
        
        else if(curr_row == 2 && curr_col == 4)
        {
            //Other corners:
            BezierPatch.control_points[2][2][1] -= dy;
            BezierPatch.control_points[4][4][1] -= dy;
            BezierPatch.control_points[4][2][1] += dy;
            
            influential_points[0] = 2;
            influential_points[1] = 2;
            
            influential_points[2] = 4;
            influential_points[3] = 4;
            
            influential_points[4] = 4;
            influential_points[5] = 2;
            
            n_influential_points = 3;
        }
        
        else if(curr_row == 4 && curr_col == 2)
        {
            //Other corners:
            BezierPatch.control_points[2][2][1] -= dy;
            BezierPatch.control_points[4][4][1] -= dy;
            BezierPatch.control_points[2][4][1] += dy;
            
            influential_points[0] = 2;
            influential_points[1] = 2;
            
            influential_points[2] = 4;
            influential_points[3] = 4;
            
            influential_points[4] = 2;
            influential_points[5] = 4;
            
            n_influential_points = 3;
        }
        
        else if(curr_row == 4 && curr_col == 4)
        {
            //Other corners:
            BezierPatch.control_points[4][2][1] -= dy;
            BezierPatch.control_points[2][4][1] -= dy;
            BezierPatch.control_points[2][2][1] += dy;
            
            influential_points[0] = 4;
            influential_points[1] = 2;
            
            influential_points[2] = 2;
            influential_points[3] = 4;
            
            influential_points[4] = 2;
            influential_points[5] = 2;
            
            n_influential_points = 3;
        }
    
    //If on central row
        else if(curr_row == 3)
        {
            BezierPatch.control_points[2][curr_col][1] += dy;
            BezierPatch.control_points[4][curr_col][1] += dy;
            
            influential_points[0] = 2;
            influential_points[1] = curr_col;
            
            influential_points[2] = 4;
            influential_points[3] = curr_col;
            
            n_influential_points = 2;
        }
    
    //If on row above central
        else if(curr_row == 4)
        {
            BezierPatch.control_points[2][curr_col][1] -= dy;
            
            influential_points[0] = 2;
            influential_points[1] = curr_col;
            
            n_influential_points = 1;
        }
    
    //If on row below central
        else if(curr_row == 2)
        {
            BezierPatch.control_points[4][curr_col][1] -= dy;
            
            influential_points[0] = 4;
            influential_points[1] = curr_col;
            
            n_influential_points = 1;
        }
    
    //If on central col
        else if(curr_col == 3)
        {
            BezierPatch.control_points[curr_row][2][1] += dy;
            BezierPatch.control_points[curr_row][4][1] += dy;
            
            influential_points[0] = curr_row;
            influential_points[1] = 2;
            
            influential_points[2] = curr_row;
            influential_points[3] = 4;
            
            n_influential_points = 2;
        }
    
    //If on col left of central
        else if(curr_col == 4)
        {
            BezierPatch.control_points[curr_row][2][1] -= dy;
            
            influential_points[0] = curr_row;
            influential_points[1] = 2;
            
            n_influential_points = 1;
        }
    
    //If on col left of central
        else if(curr_col == 2)
        {
            BezierPatch.control_points[curr_row][4][1] -= dy;
            
            influential_points[0] = curr_row;
            influential_points[1] = 4;
            
            n_influential_points = 1;
        }
}


void Window :: setBall()
{
    ball.position[0] = 15;
    ball.position[1] = 10.0;
    ball.position[2] = 0.0;
    ball.position[3] = 1.0;
    
    ball.velocity[0] = 0.0;
    ball.velocity[1] = 0.0;
    ball.velocity[2] = 0.0;
    ball.velocity[3] = 1.0;
    
    ball.acceleration[0] = 0.0;
    ball.acceleration[1] = -0.005;
    ball.acceleration[2] = 0.0;
    ball.acceleration[3] = 1.0;
}

//****************************************************************
//**
//**   PROCESS UI:
//**
//****************************************************************


void Window :: processNormalKeys(unsigned char key, int x, int y)
{
    Vector3 cop, lap, lap2cop;

    switch(key)
    {
        case 27:
            exit(0);
            break;
            
        case 32:
            paused = !paused;
            break;
            
        case 'R':
            above_cone = false;
            dec_factor = DEC_FACTOR_MAX;
            setPatch();
            setBall();
            reshapeCallback(width,height);
            camera = * new Camera(1);
            setAllScreenPositions();
            break;
            
        case 'r':
            above_cone = false;
            dec_factor = DEC_FACTOR_MAX;
            setBall();
            break;
            
        case 'm':
            marker = !marker;
            break;
            
        case 'n':
            drawnormals_on = !drawnormals_on;
            break;
            
        case 'p':
            lines_on = !lines_on;
            break;
            
        case '+':
            cop = camera.getCOP();
            lap = camera.getLAP();
            lap2cop = (cop - lap).scale(1/1.1);
            cop = lap2cop + lap;
            camera.set(cop,lap,camera.getUV());
            setAllScreenPositions();
            break;
            
        case '_':
            cop = camera.getCOP();
            lap = camera.getLAP();
            lap2cop = (cop - lap).scale(1.1);
            cop = lap2cop + lap;
            camera.set(cop,lap,camera.getUV());
            setAllScreenPositions();
            break;
            
        case 'x':
            cone.trans[12] = cone.trans[12] - 1;
            break;
            
        case 'X':
            cone.trans[12] = cone.trans[12] + 1;
            break;
            
        case 'y':
            cone.trans[13] = cone.trans[13] - 1;
            break;
            
        case 'Y':
            cone.trans[13] = cone.trans[13] + 1;
            break;
            
        case 'z':
            cone.trans[14] = cone.trans[14] - 1;
            break;
            
        case 'Z':
            cone.trans[14] = cone.trans[14] + 1;
            break;
            
        case 's':
            saveMap();
            break;
            
        case 'l':
            loadMap1();
            break;
            
        case 'L':
            loadMap2();
            break;
    }
}

void Window :: processSpecialKeys(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_DOWN:
        {
            Vector3 cop;
            cop.set(camera.getCOP()[0], camera.getCOP()[1]-1.0, camera.getCOP()[2]);
            camera.set(cop, camera.getLAP(), camera.getUV());
            setAllScreenPositions();
            break;
        }
        case GLUT_KEY_UP:
        {
            Vector3 cop;
            cop.set(camera.getCOP()[0], camera.getCOP()[1]+1.0, camera.getCOP()[2]);
            camera.set(cop, camera.getLAP(), camera.getUV());
            setAllScreenPositions();
            break;
        }
        case GLUT_KEY_LEFT:
        {
            cam_ang -= 10.0;
        
            Vector3 cop = camera.getCOP();
            Vector3 lap = camera.getLAP();
            
            double xzmag = sqrt((cop-lap)[0]*(cop-lap)[0] + (cop-lap)[2]*(cop-lap)[2]);
            Vector3 v;
            v.set(sin(cam_ang*PI/180.0), 0.0, cos(cam_ang*PI/180.0));
            v = v.normalise();
            v = v.scale(xzmag);
            
            cop.set(v[0], cop[1], v[2]);
            
            camera.set(cop,lap,camera.getUV());
            
            setAllScreenPositions();
            break;
        }
        case GLUT_KEY_RIGHT:
        {
            cam_ang += 10.0;
        
            Vector3 cop = camera.getCOP();
            Vector3 lap = camera.getLAP();
            
            double xzmag = sqrt((cop-lap)[0]*(cop-lap)[0] + (cop-lap)[2]*(cop-lap)[2]);
            Vector3 v;
            v.set(sin(cam_ang*PI/180.0), 0.0, cos(cam_ang*PI/180.0));
            v = v.normalise();
            v = v.scale(xzmag);
            
            cop.set(v[0], cop[1], v[2]);
            
            camera.set(cop,lap,camera.getUV());
            
            setAllScreenPositions();
            break;
        }
    }
}



void Window :: processMouseButtons(int button, int state, int x, int y)
{
    switch(button)
    {
        case GLUT_LEFT_BUTTON:
            left_button = !left_button;
            
            if(state == GLUT_UP)
            {
                if(point_selected)
                {
                    setScreenPositions();
                    point_selected = false;
                }
            }
            
            if(left_button && (state == GLUT_DOWN))
                setCurrentPoint(x,y);
            break;
            
        case GLUT_RIGHT_BUTTON:
            right_button = !right_button;
            break;
    }
    
}

void Window :: processMouseMotion(int x, int y)
{
    if(point_selected)
    {
        y = height - y;
        double dy = 0.05*(y - mouse_y);

        BezierPatch.control_points[curr_row][curr_col][1] += dy;
        
        n_influential_points = 0;
        setInfluentialPoints(dy);
    
        mouse_x = x;
        mouse_y = y;
    }
}

void Window :: processPassiveMotion(int x, int y)
{

    double dx;
    double dy;
    
    y = height - y;
    
    mouse_x = x;
    mouse_y = y;

    for(int row = 0; row<7; row++)
    {
        for(int col = 0; col<7; col++)
        {
            dx = x - BezierPatch.screen_positions[row][col][0];
            dy = y - BezierPatch.screen_positions[row][col][1];
            mouse_distance[row][col] = sqrt(dx*dx + dy*dy);
        }
    }
}

