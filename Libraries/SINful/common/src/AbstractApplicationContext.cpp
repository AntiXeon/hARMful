#include <AbstractApplicationContext.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    AbstractApplicationContext::AbstractApplicationContext(
                                                           BaseEntitiesManager* BaseEntitiesManager,
                                                           AbstractEntityInstanceFactory* factory
                                                          )
        : m_BaseEntitiesManager(BaseEntitiesManager),
          m_instanceFactory(factory) {}

    AbstractApplicationContext::~AbstractApplicationContext() {}


                                                     /*** SETTERS / GETTERS ***/
    BaseEntitiesManager* AbstractApplicationContext::getBaseEntitiesManager() const {
        return m_BaseEntitiesManager ;
    }

    AbstractEntityInstanceFactory* AbstractApplicationContext::getInstanceFactory() const {
        return m_instanceFactory ;
    }

    const AllInterpolations& AbstractApplicationContext::getInterpolations() const {
        return m_interpolations ;
    }

} ;
