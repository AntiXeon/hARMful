#ifndef __HOPE_BASE_LIGHT__
#define __HOPE_BASE_LIGHT__

#include <scene/components/Component.hpp>
#include <scene/common/Color.hpp>

namespace Hope {
    /**
     * Base class for lights.
     */
    class Light final : public Component {
        public:
            /**
             * Possible light types.
             */
            enum class Type {
                Directional,
                Point,
                Spot
            } ;

        private:
            /**
             * Type of the light.
             */
            Type m_type ;

            /**
             * Color of the light.
             */
            Color m_color ;

            /**
             * Intensity of the light.
             */
            float m_intensity ;

        public:
            /**
             * Create a new Light.
             */
            Light(const Type type) ;

            /**
             * To know if the component can be shared by several entities.
             * @return  false, the light cannot be shared.
             */
            bool isShareable() const override ;

            /**
             * Set the light color.
             */
            void setColor(const Color& color) ;

            /**
             * Set the light color.
             */
            void setColor(const int color) ;

            /**
             * Set the light color.
             */
            void setColor(
                const uint8_t red,
                const uint8_t green,
                const uint8_t blue
            ) ;

                        /**
             * Set the light intensity.
             */
            void setIntensity(const float intensity) ;

            /**
             * Get the color of the light.
             */
            Color color() const ;

            /**
             * Get the intensity of the light.
             */
            float intensity() const ;

            /**
             * Get the type of the light.
             */
            Type type() const ;

        protected:
            /**
             * Action to performed when the component is attached to an
             * entity.
             * @param   entity  Entity to attach the component to.
             */
            void onAttach(Entity* entity) override ;

            /**
             * Action to perform when the component is detached from its entity.
             * @param   entity  Entity to detach the component from.
             */
            void onDetach(Entity* entity) override ;
    }
}

#endif
