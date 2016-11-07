#include <scene_objects/factories/SoundEntityFactory.h>


namespace Sin {

                                              /** CONSTRUCTION / DESTRUCTION **/
    SoundEntityFactory::SoundEntityFactory() {}

    SoundEntityFactory::~SoundEntityFactory() {
        m_factoryMethods.clear() ;
    }


                                                             /*** UTILITIES ***/
    ISoundEntity* SoundEntityFactory::createEntityFromPath(const Spite::Path& filepath) {
        std::string extension = filepath.getExtension() ;
        if (m_factoryMethods.count(extension) > 0) {
            // Call the corresponding function if referenced.
            return m_factoryMethods[extension](filepath) ;
        }

        return NULL ;
    }

    void SoundEntityFactory::addCreationMethod(
                                               const std::string& extension,
                                               CreateEntityMethod function
                                              ) {
        m_factoryMethods[extension] = function ;
    }

} ;
