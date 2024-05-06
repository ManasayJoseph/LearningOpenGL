#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream> //* File stream
#include <string>
#include <sstream> //* String Stream
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string &filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    }; //* This literally means the there is going to be a new type called shadertype and that has three insider types
    //* None , Vertex , Fragment

    std::stringstream ss[2];
    std::string line;
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    { 

        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {

            ss[(int)type] << line << '\n'; //* This should divide our file into two
        }
    };
    //* So now there is another problem we need to return two variables
    //* There is a way in which we can just return a tuple
    //* To do that we need to include the tuple library built-in
    //* Use this syntax : return {item1 , item2}
    //* To recieve we do : auto [item1, item2] = function(parameter1, param2)

    //* Another way to do this is to return a struct . We follow this method
    return ShaderProgramSource{ss[0].str(), ss[1].str()};
}

static unsigned int CompileShader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //* Error Handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        //* This is only for the two types of shaders
        std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);

    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

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
        ShaderProgramSource source = ParseShader("./res/shaders/BasicShader.txt");
    
        unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
        GLCall(glUseProgram(shader));
    
    
    
        
        //* We need to bind the shader before we can call glUniform4f()
        //* The 4f here means the number of data and datatype
        //* Here it is 4 because RGBA
        
        int location = glGetUniformLocation(shader , "u_Color");
        ASSERT(location != -1);
        GLCall(glUniform4f(location,0.2f,0.3f,0.8f,0.4f));
    
        va.Unbind();
        GLCall(glUseProgram(0));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));
    
    
        float r = 0.0f;
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);
    
            //* Using modern OpenGL to draw a triangle
            //glDrawArrays(GL_TRIANGLES, 0, 4); //* Without using Index buffers
            GLCall(glUseProgram(shader));
            GLCall(glUniform4f(location,r,r,0.8f,0.4f)); //* We are trying to animate the color 
    
            va.Bind();
            ib.Bind();
    
    
            GLCall(glDrawElements(GL_TRIANGLES , 6, GL_UNSIGNED_INT , nullptr));
    
    
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
        
        GLCall(glDeleteProgram(shader));
    }
    glfwTerminate();

    return 0;
}