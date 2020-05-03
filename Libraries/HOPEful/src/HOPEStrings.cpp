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

        std::string Scene_NotPrepared =     i18n("The scene is not prepared for rendering.") ;

        /* Keep the final whitespace. */
        std::string Mesh_NotLoaded =        i18n("The mesh could not be loaded at: ") ;
        /* Keep the final whitespace. */
        std::string Texture_UnknownFormat = i18n("Unknown file format: ") ;
        /* Keep the final whitespace. */
        std::string EnvironmentMap_UnknownAspectRatio = i18n("The environment map type cannot be determined...") ;
        std::string EnvironmentMap_UnknownFaceID = i18n("Unknown cubemap face ID") ;
        /* Keep the final whitespace. */
        std::string EnvironmentMap_Load21 =      i18n("Load environment map (2:1 equirectangular): ") ;
        /* Keep the final whitespace. */
        std::string EnvironmentMap_LoadCubemap = i18n("Load environment map (cubemap): ") ;

        /* "binding index" is a technical expression. */
        std::string UBO_BadBindingIndex =   i18n("The provided binding index is too high for this GPU!") ;

        std::string FBO_Undefined =                 i18n("The specified framebuffer is the default read or draw framebuffer, but the default framebuffer does not exist.") ;
        std::string FBO_IncompleteAttachment =      i18n("Any of the framebuffer attachment points are framebuffer incomplete.") ;
        std::string FBO_IncompleteMissingAttachment = i18n("The framebuffer does not have at least one image attached to it.") ;
        std::string FBO_IncompleteDrawBuffer =      i18n("The value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAW_BUFFERi.") ;
        std::string FBO_IncompleteReadBuffer =      i18n("GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER.") ;
        std::string FBO_Unsupported =               i18n("The combination of internal formats of the attached images violates an implementation-dependent set of restrictions.") ;
        std::string FBO_IncompleteMultisample =     i18n("The value of GL_RENDERBUFFER_SAMPLES is not the same for all attached targets.") ;
        std::string FBO_IncompleteLayerTargets =    i18n("Any framebuffer attachment is layered, and any populated attachment is not layered, or if all populated color attachments are not from textures of the same target.") ;
        std::string FBO_UnknownError =              i18n("An unknown error occured in framebuffer construction.") ;
    }
} ;
