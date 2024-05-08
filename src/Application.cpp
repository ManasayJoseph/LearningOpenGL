#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream> //* File stream
#include <string>
#include <sstream> //* String Stream
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"


int main(void)
{
    std::cout << "reached main" << std::endl;
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    //* Initializing glew

    //* Window Hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE , GLFW_OPENGL_CORE_PROFILE);



    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(400, 400, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSwapInterval(1); //* This sets the window to be sync with v-sync so it will become our frame rate


    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "error with glewinit" << std::endl;
    }
    else
    {
        std::cout << "glew ok" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl; //* Shows opengl version

    {
        //* Attributes //* Vertex 1 //* here there are 2 attributes in 1 vertex
        float positions[] = {
            -0.5f , -0.5f, 
             0.5f , -0.5f,
             0.5f ,  0.5f,
            -0.5f ,  0.5f,
        };
    
    
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };
    
    
    
        // unsigned int vao;
        // GLCall(glGenVertexArrays(1, &vao));
        // GLCall(glBindVertexArray(vao));
    
        VertexArray va;
        VertexBuffer vb(positions , 4 * 2 * sizeof(float));

        VertexBufferLayout layout;
        layout.PushFloat(2);
        va.AddBuffer(vb, layout);


        vb.Bind();
        // GLCall(glEnableVertexAttribArray(0));                                          //* We need to enable the vertex attrib pointer to make it work
        // GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0)); //* Stride is no. of bytes between 2 vertices
    
        IndexBuffer ib(indices , 6); //* IBO stands for index-buffer-object
    
        //* Using a shader
        Shader shader("./res/shaders/BasicShader.txt");
        shader.Bind();
        shader.SetUniform4f("u_Color",0.8f,0.3f,0.8f,1.0f );
    
    
        
        //* We need to bind the shader before we can call glUniform4f()
        //* The 4f here means the number of data and datatype
        //* Here it is 4 because RGBA
        
    
        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;
    

    
        float r = 0.0f;
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();
    
            //* Using modern OpenGL to draw a triangle
            //glDrawArrays(GL_TRIANGLES, 0, 4); //* Without using Index buffers

    
            va.Bind();
            ib.Bind();
    
            shader.Bind();
            shader.SetUniform4f("u_Color",r,0.3f,0.8f,1.0f);

            renderer.Draw(va,ib,shader);
    
    
            if (r > 1.0f)increment = -0.05f;
            else if (r < 0.0f)increment = 0.05f;
            r += increment;
            //* Error handling :
            //* Here we are using GL_INT instead of GL_UNSIGNED_INT
            //GLCall(glDrawElements(GL_TRIANGLES , 6, GL_INT , nullptr)); 
    
    
            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window));
    
            /* Poll for and process events */
            GLCall(glfwPollEvents());
        }
        

    }
    glfwTerminate();

    return 0;
}