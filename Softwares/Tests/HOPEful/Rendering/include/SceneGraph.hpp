#ifndef __DEMOHOPE__SCENEGRAPH__
#define __DEMOHOPE__SCENEGRAPH__

#include <scene/ogl/textures/environment/EnvironmentMap.hpp>
#include <scene/components/cameras/PerspectiveCameraComponent.hpp>
#include <scene/components/mesh/MeshTreeComponent.hpp>
#include <scene/components/mesh/builtin/CubeGeometryComponent.hpp>
#include <scene/components/materials/EnvironmentMapMaterialComponent.hpp>
#include <scene/components/lights/DirectionalLightComponent.hpp>
#include <scene/components/lights/PointLightComponent.hpp>
#include <memory>

#include "FlyCameraController.hpp"

/**
 * Scene graph elements.
 */
struct SceneGraph {
    public:
        struct EnvironmentMap {
            /**
             * Environment map of the scene.
             */
            std::unique_ptr<Hope::GL::EnvironmentMap> map = nullptr ;

            /**
             * Cube environment map transform.
             */
            std::unique_ptr<Hope::Transform> transform = nullptr ;

            /**
             * Environment map material.    // Should be a shared_ptr!
             */
            std::unique_ptr<Hope::EnvironmentMapMaterialComponent> material = nullptr ;

            /**
             * Environment map material.    // Should be a shared_ptr!
             */
            std::unique_ptr<Hope::CubeGeometryComponent> mesh = nullptr ;
        } envmap ;

        struct Camera {
            /**
             * Camera transform.
             */
            std::unique_ptr<Hope::Transform> transform = nullptr ;

            /**
             * Camera component.            // Should be a shared_ptr!
             */
            std::unique_ptr<Hope::PerspectiveCameraComponent> component = nullptr ;

            /**
             * Camera controller.
             */
            std::unique_ptr<FlyCameraController> controller = nullptr ;
        } camera ;

        struct Mesh {
            /**
             * Mesh transform.
             */
            std::unique_ptr<Hope::Transform> transform = nullptr ;

            /**
             * Mesh tree.                   // Should be a shared_ptr!
             */
            std::unique_ptr<Hope::MeshTreeComponent> tree = nullptr ;
        } mesh ;

        struct SunLight {
            /**
             * Light transform.
             */
            std::unique_ptr<Hope::Transform> transform = nullptr ;

            /**
             * Directional light component. // Should be a shared_ptr!
             */
            std::unique_ptr<Hope::DirectionalLightComponent> component = nullptr ;
        } mainLight ;

        /**
         * Create a SceneGraph.
         * @param root  Root of the scene.
         */
        SceneGraph(Hope::Transform* root) ;

    private:
        /**
         * Setup the envmap.
         */
        void setupEnvmap(Hope::Transform* root) ;

        /**
         * Setup the camera.
         */
        void setupCamera(Hope::Transform* root) ;

        /**
         * Setup the loaded mesh.
         */
        void setupMesh(Hope::Transform* root) ;

        /**
         * Setup the light.
         */
        void setupLight(Hope::Transform* root) ;
} ;

#endif
