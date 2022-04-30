#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include"vertexBuffer.h"
#include "vertexBufferLayout.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "Tests/TestClearColor.h"
#include "Tests/TestObjectColor.h"


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
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
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
        -50.0f, -50.0f,0.0f,0.0f, // vertex 0
        50.0f, -50.0f,1.0f,0.0f, // vertex 1
        50.0f, 50.0f,1.0,1.0,// vertex 2
        -50.0f, 50.0f,0.0,1.0// vertex 3

    };

    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    //Vao
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //buffer vertex
    vertexArray va;
    vertexBuffer vb(position, 4 * 4 * sizeof(float));
    vertexBufferLayout vbl;

    vbl.Push<float>(2);
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

    glm::mat4 projection = glm::ortho(0.0f, 960.0f, 0.0f,540.0f, -1.0f, 1.0f);

    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    //glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));
    //glm::mat4 mpv = projection * view * model;

    Shader shader("res/Shader/Shader.shader");
    shader.Bind();
    
    
    float r = 0.5f;
    float increment = 0.1f;
    shader.SetUniform4f("u_Color", 0.8f, 0.2f, 0.2f, 1.0f);
    //shader.SetUniformMat4f("MVP", mpv);

    Texture texture("res/Textures/Pacman.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);
    

   // int location = glGetUniformLocation(shader, "u_Color");
    //glUniform4f(location, r, 0.2f, 0.2f, 1.0f);

    va.unBind();
    vb.unBind();
    ib.unBind();
    shader.UnBind();

    Renderer render;
    
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    glm::vec3  trans(200, 200, 0);
    glm::vec3  trans2(400, 200, 0);
    float c_Color[4] = { 1.0f,1.0f ,1.0f,1.0f };
    float c_Color2[4] = { 1.0f,1.0f ,1.0f,1.0f };
    test::TestClearColor test;
    

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        //glClear(GL_COLOR_BUFFER_BIT);
        render.Clean();
        test.OnUpdate(0.0f);
        test.OnRender();
     
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        ImGui_ImplGlfwGL3_NewFrame();
        test.OnImGui();
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), trans);
            glm::mat4 mpv = projection * view * model;
            
            shader.Bind();
            shader.SetUniform4f("u_Color", c_Color[0], c_Color[1], c_Color[2], c_Color[3]);
            shader.SetUniformMat4f("MVP", mpv);
            ImGui::ColorEdit4("Color Edit 1", c_Color);
            render.Draw(va, ib, shader);
        }
        //shader.SetUniform4f("u_Color", 0.0f, 0.2f, 0.2f, 1.0f);
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), trans2);
            glm::mat4 mpv = projection * view * model;
            shader.Bind();
            shader.SetUniform4f("u_Color", c_Color2[0], c_Color2[1], c_Color2[2], c_Color2[3]);
            shader.SetUniformMat4f("MVP", mpv);
            ImGui::ColorEdit4("Color Edit 2", c_Color2);
            render.Draw(va, ib, shader);
        }
        //glBindVertexArray(vao);
        //va.Bind();
        //ib.Bind();


        //dive 
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        if (r > 1) {
            increment = -0.1f;
        }
        if (r < 0) {
            increment = 0.1;
        }
        r += increment;
        {
            static float f = 0.0f;
                              // Display some text (you can use a format string too)
            ImGui::SliderFloat3("Translation A", &trans.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
            ImGui::SliderFloat3("Translatio B", &trans2.x, 0.0f, 960.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
   
}
ImGui_ImplGlfwGL3_Shutdown();
ImGui::DestroyContext();
    
    glfwTerminate();
    return 0;
}