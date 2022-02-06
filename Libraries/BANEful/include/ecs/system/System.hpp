#ifndef __BANE_SYSTEM__
#define __BANE_SYSTEM__

#include "ecs/entity/Entity.hpp"
#include "ecs/system/SystemProcessing.hpp"
#include <list>
#include <map>
#include <memory>
#include <string>

namespace Bane {

    /**
     * Base class for defining a System of the ECS architecture.
     */
    class System {
        private:
            /**
             * Name of the System.
             */
            std::string m_name ;

            /**
             * true if the System can be run in a multithreaded way; false if
             * not possible.
             */
            bool m_isMultithreaded = true ;

            /**
             * List of the Systems the current one needs to be processed.
             */
            std::map<std::string, System*> m_linkedSystems ;

            /**
             * Dedicated class for processing Components.
             */
            std::unique_ptr<SystemProcessing> m_processing ;

        public:
            /**
             * Create a new System instance.
             */
            System(
                const std::string& name,
                const bool multithreaded
            ) : m_name(name),
                m_isMultithreaded(multithreaded) {}

            /**
             * Run the Components processing.
             * @return A list of Entity to be removed by the World.
             */
            std::list<Entity> process(
                const int fromIndex,
                 const int toIndex
             ) {
                return m_processing -> run(
                    m_linkedSystems,
                    fromIndex,
                    toIndex
                ) ;
            }

            /**
             * Link another System to the current one.
             */
            void link(System* system) ;

            /**
             * Unlink another System by its name from the current one.
             */
            void unlink(const std::string& systemName) ;

            /**
             * Unlink another System from the current one.
             */
            void unlink(const System* system) ;

            /**
             * Get the name of the System.
             */
            const std::string& name() const {
                return m_name ;
            }

            /**
             * Get the multithread state of the System: true if the System can
             * be run in a multithreaded way; false if not possible.
             */
            bool isMultithreaded() const {
                return m_isMultithreaded ;
            }

            /**
             * Get the amount of Components managed by the current System.
             */
            virtual size_t amountComponents() const = 0 ;
    } ;
}

#endif
