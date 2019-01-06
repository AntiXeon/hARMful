#include <scene/ogl/Options.hpp>
#include <GLFW/glfw3.h>

using namespace Hope::GL ;

void Options::SetGLVersion(
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

void Options::SetSamplingFactor(const Options::Sampling sampling) {
    glfwWindowHint(GLFW_SAMPLES, (int)sampling);
}
