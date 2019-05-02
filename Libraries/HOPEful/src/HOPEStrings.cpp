#include <HOPEStrings.hpp>

/**
 * Tag to be detected when using xgettext on this file.
 * @param  str The string to be detected by xgettext.
 * @return     The same string as input.
 */
#define i18n(str) str

namespace Hope {
    namespace Texts {
        /* GLFW is the name of a third-party library. */
        std::string Init_Bad_GLFW =         i18n("Could not initialize GLFW.") ;
        /* GLEW is the name of a third-party library. Keep the final whitespace. */
        std::string Init_Bad_GLEW =         i18n("Failed to initialize GLEW: ") ;
        std::string Init_GL_Window =        i18n("Failed to create the window using OpenGL.") ;
        std::string Init_GL_Renderer =      i18n("Renderer: ") ;
        std::string Init_GL_Vendor =        i18n("OpenGL version: ") ;

        /* Keep the final whitespace. */
        std::string Mesh_NotLoaded =        i18n("The mesh could not be loaded at: ") ;
        /* Keep the final whitespace. */
        std::string Texture_UnknownFormat = i18n("Unknown file format: ") ;

        /* "binding index" is a technical expression. */
        std::string UBO_BadBindingIndex =   i18n("The provided binding index is too high for this GPU!") ;
    }
} ;
