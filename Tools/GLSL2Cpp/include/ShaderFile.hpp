#ifndef __GLSL2CPP__SHADER_FILE__
#define __GLSL2CPP__SHADER_FILE__

#include <string>

/**
 * Shader file.
 */
struct ShaderFile final {
    /**
     * File name without extension.
     */
    std::string stem ;

    /**
     * Extension of the file.
     */
    std::string extension ;
} ;

#endif
