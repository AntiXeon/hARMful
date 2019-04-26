#ifndef __HOPE__SCENE_CACHE__
#define __HOPE__SCENE_CACHE__

#include <set>
#include <scene/components/materials/PhongMaterialComponent.hpp>

namespace Hope {
    class MaterialComponent ;
    class LightComponent ;
    class DirectionalLightComponent ;
    class PointLightComponent ;

    /**
     * Cache some elements of the scene to access them faster while rendering.
     */
    class SceneCache final {
        private:
            /**
             * Default material when trying to render a mesh without material.
             */
            PhongMaterialComponent m_defaultMaterial ;

            /**
             * To know if there is a change in the directional lights since the
             * last render.
             */
            bool m_directionalLightsChanged = true ;

            /**
             * List of the directional lights in the scene.
             */
            std::set<DirectionalLightComponent*> m_directionalLights ;

            /**
             * To know if there is a change in the point lights since the last
             * render.
             */
            bool m_pointLightsChanged = true ;

            /**
             * List of the point lights in the scene.
             */
            std::set<PointLightComponent*> m_pointLights ;

        public:
            /**
             * Get the default material component.
             */
            const PhongMaterialComponent* defaultMaterial() const {
                return &m_defaultMaterial ;
            }

            /**
             * Register a light.
             */
            void registerLight(LightComponent* light) ;

            /**
             * Deregister a light.
             */
            void deregisterLight(LightComponent* light) ;

            /**
             * Get the list of lights.
             */
            const std::set<DirectionalLightComponent*>& directionalLights() const {
                return m_directionalLights ;
            }

            /**
             * Get the list of lights.
             */
            const std::set<PointLightComponent*>& pointLights() const {
                return m_pointLights ;
            }

            /**
             * To know if there is a change in the directional lights since the
             * last render.
             */
            bool hasDirectionalLightsChanged() const {
                return m_directionalLightsChanged ;
            }

            /**
             * To know if there is a change in the point lights since the last
             * render.
             */
            bool hasPointLightsChanged() const {
                return m_pointLightsChanged ;
            }

            /**
             * Clear any change.
             */
            void clearChanges() {
                m_directionalLightsChanged = false ;
                m_pointLightsChanged = false ;
            }
    } ;
}

#endif
