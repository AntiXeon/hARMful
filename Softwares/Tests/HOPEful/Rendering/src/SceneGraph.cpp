#include <SceneGraph.hpp>
#include <scene/Entity.hpp>

SceneGraph::SceneGraph(Hope::Transform* root) {
    setupEnvmap(root) ;
    setupCamera(root) ;
    setupMesh(root) ;
    setupLight(root) ;
}

void SceneGraph::setupEnvmap(Hope::Transform* root) {
    envmap.map = std::make_unique<Hope::GL::EnvironmentMap>("sunflowers_4k.hem") ;

    envmap.transform = std::make_unique<Hope::Transform>(root) ;
    envmap.material = std::make_unique<Hope::EnvironmentMapMaterialComponent>(envmap.map.get()) ;
    envmap.mesh = std::make_unique<Hope::CubeGeometryComponent>() ;
    envmap.transform -> entity() -> addComponent(envmap.material.get()) ;
    envmap.transform -> entity() -> addComponent(envmap.mesh.get()) ;

    envmap.transform -> entity() -> setLocked(true) ;
}

void SceneGraph::setupCamera(Hope::Transform* root) {
    camera.transform = std::make_unique<Hope::Transform>(root) ;
    camera.component = std::make_unique<Hope::PerspectiveCameraComponent>() ;

    camera.component -> setFOV(50.f);
    camera.component -> setFarPlaneDistance(500.f);
    camera.component -> lookAt(Mind::Vector3f(1.f, 0.f, 0.f)) ;

    camera.transform -> entity() -> addComponent(camera.component.get()) ;
    camera.transform -> entity() -> setLocked(true) ;

    camera.controller = std::make_unique<FlyCameraController>(camera.component.get()) ;
}

void SceneGraph::setupMesh(Hope::Transform* root) {
    mesh.transform = std::make_unique<Hope::Transform>(root) ;
    mesh.transform -> setScale(5.f) ;

    mesh.tree = std::make_unique<Hope::MeshTreeComponent>("../data/meshes/Landscape.dae") ;
    mesh.transform -> entity() -> addComponent(mesh.tree.get()) ;
}

void SceneGraph::setupLight(Hope::Transform* root) {
    mainLight.component = std::make_unique<Hope::DirectionalLightComponent>() ;
    mainLight.component -> setDirection(Mind::Vector3f(-0.5f, -0.8f, 0.5f)) ;
    mainLight.component -> setColor(Hope::Color(1.f, 0.95f, 0.95f, 1.f)) ;
    mainLight.component -> setPower(1.f) ;
    mainLight.component -> setSpecularGenerated(true) ;

    mainLight.transform = std::make_unique<Hope::Transform>(root) ;
    mainLight.transform -> entity() -> addComponent(mainLight.component.get()) ;
    mainLight.transform -> entity() -> setLocked(true) ;
}
