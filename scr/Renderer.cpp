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
