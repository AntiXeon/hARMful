#ifndef __HOPE__GL_DEFINES__
#define __HOPE__GL_DEFINES__

#include <HopeAPI.hpp>

#ifdef OGL
    #define INVALID_VALUE 0xffffffff
    #define INVALID_MATERIAL 0xffffffff
    #define INVALID_UNIFORM_LOCATION 0xffffffff


    #define BASE_DATA_UBO_BINDING_INDEX 0
    #define MODEL_DATA_UBO_BINDING_INDEX 1

    #define BASE_DATA_UBO_BLOCK_NAME    "BaseData"
    #define MODEL_DATA_UBO_BLOCK_NAME    "ModelData"
#endif

#endif
