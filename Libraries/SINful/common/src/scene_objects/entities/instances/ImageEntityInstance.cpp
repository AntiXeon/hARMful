#include <scene_objects/entities/instances/ImageEntityInstance.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    ImageEntityInstance::ImageEntityInstance(IImageEntity* entity)
        : AbstractEntityInstance(),
          m_entity(entity) {}

    ImageEntityInstance::ImageEntityInstance(
                                             IImageEntity* entity,
                                             const Mind::Point2Df& position
                                            ) : AbstractEntityInstance(position),
                                                m_entity(entity) {}

    ImageEntityInstance::~ImageEntityInstance() {}


                                                             /*** UTILITIES ***/
    void ImageEntityInstance::update() {
        // @TODO: Maybe something to do?
    }

    void ImageEntityInstance::render(const Mind::Point2Df& relative) {
        Mind::Point2Df position = getPosition() + relative ;
        m_entity -> renderAt(
                             position.getX(),
                             position.getY(),
                             m_rotation.getPivot(),
                             m_rotation.getAngle()
                            ) ;
    }


    void ImageEntityInstance::rotate(const Mind::Scalar& angle) {
        m_rotation.addAngle(angle) ;
    }

    void ImageEntityInstance::resize(const Mind::Dimension2Df& size) {
        m_dimension = m_dimension + ((Mind::Dimension2Df&) size) ;
    }

                                                     /*** SETTERS / GETTERS ***/
    const Mind::Dimension2Df& ImageEntityInstance::getDimension() const {
        return m_dimension ;
    }

    void ImageEntityInstance::setDimension(const Mind::Dimension2Df& dimension) {
        m_dimension = dimension ;
    }

    const ObjectRotation2D& ImageEntityInstance::getRotation() const {
        return m_rotation ;
    }

    void ImageEntityInstance::setRotation(const ObjectRotation2D& rotation) {
        m_rotation = rotation ;
    }

    void ImageEntityInstance::setPivot(const Mind::Point2Df& pivot) {
        m_rotation.setPivot(pivot) ;
    }

    void ImageEntityInstance::setRotationAngle(const Mind::Scalar& angle) {
        m_rotation.setAngle(angle) ;
    }


    IImageEntity* ImageEntityInstance::getEntity() const {
        return m_entity ;
    }

} ;
