#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.h"


Shader::Shader(const std::string& filePath): m_filepath(filePath), m_RenderID(0)
{
    ShaderSources source = ParseShader(filePath);

    m_RenderID = createShader(source.VertexShader, source.FragmentShader);
}
Shader::~Shader()
{
    glDeleteProgram(m_RenderID);
}

void Shader::Bind() const
{
    glUseProgram(m_RenderID);
}

void Shader::UnBind() const
{
    glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& projection)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &projection[0][0]);
}

void Shader::SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4)
{
    glUniform4f(GetUniformLocation(name), v1, v2, v3, v4);
}

unsigned int Shader::GetUniformLocation(const std::string& location)
{

    if (m_UniformLocationCache.find(location) != m_UniformLocationCache.end()) {
        return m_UniformLocationCache[location];
    }
   int direccion =  glGetUniformLocation(m_RenderID, location.c_str());
   if (direccion == -1) {
       std::cout << "Warning" << location << " does not exist" << std::endl;
   }
   m_UniformLocationCache[location] = direccion;
   return direccion;
}


ShaderSources Shader::ParseShader(const std::string& filePath) {
    std::ifstream stream(filePath);
    std::string line;

    std::stringstream ss[2];
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#Shader") != std::string::npos) {
            if (line.find("Vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("Fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(),ss[1].str() };
}
 unsigned int Shader::compilerShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* scr = source.c_str();
    glShaderSource(id, 1, &scr, nullptr);
    glCompileShader(id);

    //Error
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int lengt;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lengt);
        char* message = (char*)alloca(lengt * sizeof(char));
        glGetShaderInfoLog(id, lengt, &lengt, message);
        std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertx" : "fragmen") << "sheader" << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}
unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmenShader) {
     unsigned int program = glCreateProgram();
     unsigned int vs = compilerShader(GL_VERTEX_SHADER, vertexShader);
     unsigned int fs = compilerShader(GL_FRAGMENT_SHADER, fragmenShader);
     glAttachShader(program, vs);
     glAttachShader(program, fs);
     glLinkProgram(program);
     glValidateProgram(program);

     glDeleteShader(vs);
     glDeleteShader(fs);

     return program;
 }