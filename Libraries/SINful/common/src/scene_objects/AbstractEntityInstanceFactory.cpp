#include <scene_objects/AbstractEntityInstanceFactory.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    AbstractEntityInstanceFactory::AbstractEntityInstanceFactory(AllEntities* allEntities)
        : m_allEntities(allEntities) {}

    AbstractEntityInstanceFactory::~AbstractEntityInstanceFactory() {}


                                                     /*** SETTERS / GETTERS ***/
    AllEntities* AbstractEntityInstanceFactory::getAllEntities() const {
        return m_allEntities ;
    }

} ;
