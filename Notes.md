# Learning OpenGL
In this course we are going to learn some basics in opengl

If you have any doubt about anything search [docs.gl](https://docs.gl) or just google it

**Setting Up in readme.md**
## 1. GLFW
GLFW is a library that creates a window for us . This just simplifies the process of creating a window for opengl with each and every operating system with its rescpective api.

## 2. GLEW
GLEW is another library that allows us to use the functions built-in for each graphics drivers. It also just simplifies the process nothing much.  

So opengl is state based: meaning we need to select the element to do anything to it 

### Shader
Shaders are the programs that run on the GPU. They run like any other program and the only difference is they run on the GPU.

There are main two shader types vertex shaders and fragment shaders also known as pixel shaders
There are other shader types as well : many I am not going to list them here.


## Dealing with OpenGL errors
You can use glGetError and glDebugMessageCallback to fix errors in opengl 
Check the docs to learn more

## Uniforms 
Uniforms are ways of sending data from cpu to gpu 
One way is to use Uniforms and VertexBuffers
everything that starts with u_ is a uniform

