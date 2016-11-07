#include <scene_objects/entities/ImageEntity.h>

namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    ImageEntity::ImageEntity() : m_texture(NULL) {}

    ImageEntity::~ImageEntity() {
        if (m_texture != NULL) {
            SDL_DestroyTexture(m_texture) ;
        }
    }

                                                             /*** UTILITIES ***/
    void ImageEntity::renderAt(
                               const Mind::Scalar&,
                               const Mind::Scalar&
                              ) {
//        int errorCode ;
//        errorCode = SDL_RenderCopy() ;
    }

}
