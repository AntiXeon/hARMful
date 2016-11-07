#include <scene_objects/factories/ImageEntityFactory.h>


namespace Sin {

                                              /** CONSTRUCTION / DESTRUCTION **/
    ImageEntityFactory::ImageEntityFactory() {}

    ImageEntityFactory::~ImageEntityFactory() {
        m_factoryMethods.clear() ;
    }


                                                             /*** UTILITIES ***/
    IImageEntity* ImageEntityFactory::createEntityFromPath(const Spite::Path& filepath) {
        std::string extension = filepath.getExtension() ;
        if (m_factoryMethods.count(extension) > 0) {
            // Call the corresponding function if referenced.
            return m_factoryMethods[extension](filepath) ;
        }

        return NULL ;
    }

    void ImageEntityFactory::addCreationMethod(
                                               const std::string& extension,
                                               CreateEntityMethod function
                                              ) {
        m_factoryMethods[extension] = function ;
    }

} ;
