#ifndef __BANE_COMPONENT__
#define __BANE_COMPONENT__

#include <utils/IDObject.hpp>
#include "ecs/component/ComponentData.hpp"
#include "ecs/entity/Entity.hpp"

namespace Bane {
    /**
     * Base class for defining a Component of the ECS architecture.
     */
    class Component final : public Doom::IDObject {
        friend class ComponentFactory ;

        private:
            /**
             * Entity to which the Component is attached to.
             */
            Entity m_entity ;

            /**
             * Specific data of the Component.
             */
            std::unique_ptr<ComponentData> m_data ;

        public:
            /**
             * Create a new Component instance.
             */
            Component(const Entity& entity):
                Doom::IDObject(Doom::IDObject::Generate()),
                m_entity(entity) { }

            /**
             * Get the quantity of the Component type a single Entity can bear.
             */
            ComponentData::Quantity quantity() const {
                return m_data -> quantity() ;
            }

            /**
             * Get the Entity to which the current Component is attached to.
             */
            const Entity& entity() const {
                return m_entity ;
            }

            /**
             * Get the Component data.
             */
            ComponentData* data() const {
                return m_data.get() ;
            }

            /**
             * Get the ID of the Entity to which the current Component is
             * attached to.
             */
            uint32_t entityValue() const {
                return m_entity.id() ;
            }

            /**
             * Check if the Entity owning the Component is valid.
             */
            bool hasValidEntity() const {
                return m_entity.isValid()  ;
            }

        private:
            /**
             * Set the Component data.
             */
            void setData(std::unique_ptr<ComponentData>& data) {
                m_data = std::move(data) ;
            }
    } ;
}

#endif
