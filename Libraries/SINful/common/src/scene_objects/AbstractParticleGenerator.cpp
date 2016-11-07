#include <scene_objects/AbstractParticleGenerator.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    AbstractParticleGenerator::AbstractParticleGenerator(AbstractApplicationContext* context)
        : AbstractSceneObject(),
          m_context(context) {}

    AbstractParticleGenerator::~AbstractParticleGenerator() {
        ParticlesIterator particlesIt = m_particles.begin() ;
        for (; particlesIt != m_particles.end() ; ++particlesIt) {
            AbstractEntityInstance* particle = (*particlesIt) ;

            if (particle != NULL) {
                delete particle ;
            }
        }

        m_particles.clear() ;
    }

                                                             /*** UTILITIES ***/
    void AbstractParticleGenerator::render(const Mind::Point2Df& relative) {
        render(relative.getX(), relative.getY()) ;
    }

    void AbstractParticleGenerator::render(
                                           const Mind::Scalar& relativeX,
                                           const Mind::Scalar& relativeY
                                          ) {
        ParticlesIterator particlesIt = m_particles.begin() ;
        for (; particlesIt != m_particles.end() ; ++particlesIt) {
            AbstractEntityInstance* particle = (*particlesIt) ;
            particle -> render(relativeX, relativeY) ;
        }
    }


    void AbstractParticleGenerator::generateParticles(
                                                      const unsigned int& amount,
                                                      const unsigned int& entityID
                                                     ) {
        AbstractEntityInstanceFactory* factory = getContext() -> getInstanceFactory() ;

        for (unsigned int count = 0 ; count < amount ; ++count) {
            AbstractEntityInstance* particle = factory -> createInstance(entityID) ;
            setParticleParameters(particle) ;
            m_particles.push_back(particle) ;
        }
    }

} ;
