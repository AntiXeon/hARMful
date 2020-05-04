#ifndef __HOPE__STRINGS__
#define __HOPE__STRINGS__

#include <string>

namespace Hope {
    namespace Texts {
        extern std::string Init_Bad_GLFW ;
        extern std::string Init_Bad_GLEW ;
        extern std::string Init_GL_Window ;
        extern std::string Init_GL_Renderer ;
        extern std::string Init_GL_Vendor ;

        extern std::string Scene_NotPrepared ;

        extern std::string Mesh_NotLoaded ;
        extern std::string Texture_UnknownFormat ;
        extern std::string EnvironmentMap_UnknownAspectRatio ;
        extern std::string EnvironmentMap_UnknownFaceID ;
        extern std::string EnvironmentMap_UnknownFormat ;
        extern std::string EnvironmentMap_Load21 ;
        extern std::string EnvironmentMap_LoadCubemap ;

        extern std::string UBO_BadBindingIndex ;

        extern std::string FBO_Undefined ;
        extern std::string FBO_IncompleteAttachment ;
        extern std::string FBO_IncompleteMissingAttachment ;
        extern std::string FBO_IncompleteDrawBuffer ;
        extern std::string FBO_IncompleteReadBuffer ;
        extern std::string FBO_Unsupported ;
        extern std::string FBO_IncompleteMultisample ;
        extern std::string FBO_IncompleteLayerTargets ;
        extern std::string FBO_UnknownError ;
    }
} ;

#endif
