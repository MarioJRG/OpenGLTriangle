#include "Renderer.h"

void glClearError() {
    while (glGetError() != GL_NO_ERROR);
}
bool GlLogCall(const char* funtion, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error](" << error << ")" << "[funtion](" << funtion << ")"
            << "[file](" << file << ")"
            << "[line](" << line << ")"
            << std::endl;
        return false;
    }
    return true;
}

void Renderer::Draw(const vertexArray& va, const indexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
 



    //glBindVertexArray(vao);
    va.Bind();
    ib.Bind();


    //dive 
    glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clean() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}
