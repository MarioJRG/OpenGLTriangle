#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.h"
#include "indexBuffer.h"
#include"vertexBuffer.h"
#include "vertexArray.h"
#include "vertexBufferLayout.h"
#include "Shader.h"
//struct ShaderSources
//{
//    std::string VertexShader;
//    std::string FragmentShader;
//};
//static ShaderSources ParseShader(const std::string& filePath) {
//    std::ifstream stream(filePath);
//    std::string line;
//
//    std::stringstream ss[2];
//    enum class ShaderType
//    {
//        NONE= -1, VERTEX = 0, FRAGMENT = 1
//    };
//
//    ShaderType type = ShaderType::NONE;
//    while (getline(stream,line)) {
//        if (line.find("#Shader") != std::string::npos) {
//            if (line.find("Vertex") != std::string::npos) {
//                type = ShaderType::VERTEX;
//            }
//            else if (line.find("Fragment") != std::string::npos) {
//                type = ShaderType::FRAGMENT;
//            }
//        }
//        else
//        {
//            ss[(int)type] << line << '\n';
//        }
//    }
//    return {ss[0].str(),ss[1].str()};
//}
//
//static unsigned int compilerShader(unsigned int type,const std::string& source ) {
//   unsigned int id =  glCreateShader(type);
//   const char* scr = source.c_str();
//   glShaderSource(id, 1, &scr, nullptr);
//   glCompileShader(id);
//   
//   //Error
//   int result;
//   glGetShaderiv(id,GL_COMPILE_STATUS,&result);
//   if (result == GL_FALSE) {
//       int lengt;
//       glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lengt);
//       char* message = (char*) alloca(lengt * sizeof(char));
//       glGetShaderInfoLog(id, lengt, &lengt, message);
//       std::cout << "Failed to compile" << (type==GL_VERTEX_SHADER ?"vertx": "fragmen") << "sheader" << std::endl;
//       glDeleteShader(id);
//       return 0;
//   }
//
//   return id;
//}
//static unsigned int createShader(const std::string& vertexShader, const std::string& fragmenShader ) {
//    unsigned int program =  glCreateProgram();
//    unsigned int vs = compilerShader(GL_VERTEX_SHADER,vertexShader);
//    unsigned int fs = compilerShader(GL_FRAGMENT_SHADER, fragmenShader);
//    glAttachShader(program, vs);
//    glAttachShader(program, fs);
//    glLinkProgram(program);
//    glValidateProgram(program);
//
//    glDeleteShader(vs);
//    glDeleteShader(fs);
//
//    return program;
//}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error¡" << std::endl;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;
    {
    /* Loop until the user closes the window */
    float position[] = {
        -0.5f, -0.5f, // vertex 0
        0.5f, -0.5f, // vertex 1
        0.5f, 0.5f,// vertex 2
        -0.5f, 0.5f// vertex 3

    };

    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    //Vao
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


    //buffer vertex
    vertexArray va;
    vertexBuffer vb(position, 4 * 2 * sizeof(float));
    vertexBufferLayout vbl;

    vbl.Push<float>(2);
    va.addBuffer(vb, vbl);

    //unsigned int buffer;
    //glGenBuffers(1, &buffer);
    //glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //glBufferData(GL_ARRAY_BUFFER, 4 *2* sizeof(float),position, GL_STATIC_DRAW);
    


    
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    indexBuffer ib(indices, 6);
    //unsigned int idb;
    //glGenBuffers(1,&idb);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idb );
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER,6*sizeof(unsigned int),indices,GL_STATIC_DRAW);

    Shader shader("res/Shader/Shader.shader");
    shader.Bind();
    

    float r = 0.5f;
    float increment = 0.1f;
    shader.SetUniform4f("u_Color", 0.8f, 0.2f, 0.2f, 1.0f);
   // int location = glGetUniformLocation(shader, "u_Color");
    //glUniform4f(location, r, 0.2f, 0.2f, 1.0f);

    va.unBind();
    vb.unBind();
    ib.unBind();
    shader.UnBind();

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //glDrawArrays(GL_TRIANGLES, 0, 6);

        shader.Bind();
        shader.SetUniform4f("u_Color", r, 0.2f, 0.2f, 1.0f);



        //glBindVertexArray(vao);
        va.Bind();
        ib.Bind();


        //dive 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        if (r > 1) {
            increment = -0.1f;
        }
        if (r < 0) {
            increment = 0.1;
        }
        r += increment;
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
   
}
    glfwTerminate();
    return 0;
}