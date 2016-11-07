#include <scene_objects/entities/instances/AbstractEntityInstance.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    AbstractEntityInstance::AbstractEntityInstance() : AbstractSceneObject() {}

    AbstractEntityInstance::AbstractEntityInstance(const Mind::Point2Df& position)
        : AbstractSceneObject(position) {}

    AbstractEntityInstance::~AbstractEntityInstance() {}

} ;
