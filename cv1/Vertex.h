#pragma once
#include <GL/glew.h>


struct Vertex
{
    GLfloat Position[3];
    GLfloat Normal[3];
    GLfloat Texture[2];
    GLfloat Tangent[3];
};