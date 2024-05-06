#include "Renderer.h"
#include <iostream>

void GLClearError()
{
    while(glGetError() != GL_NO_ERROR) /*You could write != 0 as well*/;
}

bool GLLogCall(const char* function , const char* file , int line){
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] " << error << " at " << function  << " in " << file << " at : " << line<< std::endl;
        return false;
    }
    return true;
}