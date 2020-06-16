#include <FrameGraph.hpp>

FrameGraph::FrameGraph(
    const Mind::Dimension2Di& windowSize,
    const SceneGraph* scenegraph
) {
    activeCameraNode = std::make_unique<Hope::ActiveCameraNode>() ;
    activeCameraNode -> setCamera(scenegraph -> camera.component.get()) ;

    root = std::make_unique<Hope::FrameGraphNode>() ;

    // -- Shadow mapping pass --
    const uint32_t ShadowResolution = 2048 ;
    float maxDistance = 100.f ;
    uint8_t amountCascades = 3 ;
    dirLightShadowNode = std::make_unique<Hope::DirectionalLightShadowNode>(
        scenegraph -> mainLight.component.get(),
        activeCameraNode.get(),
        ShadowResolution,
        maxDistance,
        amountCascades,
        root.get()
    ) ;

    // -- Rendering pass --
    viewportNode = std::make_unique<Hope::ViewportNode>(root.get()) ;
    viewportNode -> setPosition(Mind::Point2Df(0.f, 0.f)) ;
    viewportNode -> setDimension(Mind::Dimension2Df(1.f, 1.f)) ;

    // G-Buffer branch of the framegraph.
    activeCameraNode -> setParent(viewportNode.get()) ;

    cubemapCapabilitiesNode = std::make_unique<Hope::RenderCapabilityNode>(activeCameraNode.get()) ;
    seamlessCubemapCapability = std::make_unique<Hope::GL::SeamlessCubemap>() ;
    cubemapCapabilitiesNode -> addCapability(seamlessCubemapCapability.get()) ;

    gBufferNode = std::make_unique<Hope::GBufferRenderNode>(
        windowSize,
        cubemapCapabilitiesNode.get()
    ) ;

    clearBuffersNode = std::make_unique<Hope::ClearBuffersNode>(
        Hope::GL::BufferClearer::Buffer::ColorDepth,
        gBufferNode.get()
    ) ;

    renderPassNode = std::make_unique<Hope::RenderPassSelectorNode>(
        DeferredPassID,
        clearBuffersNode.get()
    ) ;

    deferredRenderingNode = std::make_unique<Hope::DeferredRenderingNode>(
        gBufferNode.get(),
        scenegraph -> envmap.map.get(),
        viewportNode.get()
    ) ;
}
