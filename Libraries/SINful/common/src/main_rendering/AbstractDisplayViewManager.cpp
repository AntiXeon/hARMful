#include <main_rendering/AbstractDisplayViewManager.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    AbstractDisplayViewManager::AbstractDisplayViewManager(AbstractApplicationContext* context)
        : m_context(context) {}

    AbstractDisplayViewManager::~AbstractDisplayViewManager() {}

                                                             /*** UTILITIES ***/
    void AbstractDisplayViewManager::removeView(const unsigned int& id) {
        if (id < m_viewsList.size()) {
            if (m_viewsList[id] != NULL) {
                delete m_viewsList[id] ;
                m_viewsList[id] = NULL ;
            }
        }
    }

    void AbstractDisplayViewManager::removeAllViews() {
        for (unsigned int viewIndex = 0 ; viewIndex < m_viewsList.size() ; ++viewIndex) {
            removeView(viewIndex) ;
        }
        m_viewsList.clear() ;
        freeResources() ;
    }


    void AbstractDisplayViewManager::pushView(const unsigned int& id) {
        if (id < m_viewsList.size()) {
            if (m_viewsList[id] != NULL) {
                m_viewsStack.push(m_viewsList[id]) ;
            }
        }
    }

    void AbstractDisplayViewManager::popView() {
        m_viewsStack.pop() ;
    }

    void AbstractDisplayViewManager::freeResources() {
        BaseEntitiesManager* manager = m_context -> getBaseEntitiesManager() ;
        AllEntities* entities = manager -> getAllEntities() ;
        entities -> clear() ;
    }

    unsigned int AbstractDisplayViewManager::storeView(AbstractDisplayView* view) {
        if (view != NULL) {
            m_viewsList.push_back(view) ;
            return (m_viewsList.size() - 1) ;
        }
        else {
            return 0 ;
        }
    }

                                                     /*** SETTERS / GETTERS ***/
    AbstractApplicationContext* AbstractDisplayViewManager::getApplicationContext() const {
        return m_context ;
    }

    AbstractDisplayView* AbstractDisplayViewManager::getCurrentView() {
        return m_viewsStack.top() ;
    }

} ;
