#include <OGL/GLOptions.hpp>
#include <GLFW/glfw3.h>

namespace Hope {
    void GLOptions::SetGLVersion(
      const int major,
      const int minor
    ) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);

        if (major > 3) {
            // Do not support old OpenGL versions.
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }
    }

    void GLOptions::SetSamplingFactor(const GLOptions::Sampling sampling) {
        glfwWindowHint(GLFW_SAMPLES, (int)sampling);
    }
}
