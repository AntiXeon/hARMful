#ifndef __SIN_ABSTRACT_PARTICLE_GENERATOR__
#define __SIN_ABSTRACT_PARTICLE_GENERATOR__


#include <AbstractApplicationContext.h>
#include <scene_objects/AbstractSceneObject.h>
#include <scene_objects/entities/instances/AbstractEntityInstance.h>


namespace Sin {

    /**
     * @brief   AbstractParticleGenerator is the base class to create generators
     *          of particles.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/13
     */
    class AbstractParticleGenerator : public AbstractSceneObject {
        private:
            /**
             * @brief   Context of the application.
             */
            AbstractApplicationContext* m_context ;

            /**
             * @brief   List of the particles.
             */
            std::vector<AbstractEntityInstance*> m_particles ;

        protected:
            typedef std::vector<AbstractEntityInstance*>::iterator ParticlesIterator ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Creation of an AbstractParticleGenerator.
             * @param   context     Context of the application.
             */
            AbstractParticleGenerator(AbstractApplicationContext* context) ;

            /**
             * @brief   Destruction of the AbstractParticleGenerator.
             */
            virtual ~AbstractParticleGenerator() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Render the particles of the AbstractParticleGenerator.
             * @param   relative    Relative position of the generator (used by
             *                      relative particles).
             */
            void render(const Mind::Point2Df& relative) ;

            /**
             * @brief   Render the particles of the AbstractParticleGenerator.
             * @param   relativeX   Relative position on X of the generator
             *                      (used by relative particles).
             * @param   relativeY   Relative position on Y of the generator
             *                      (used by relative particles).
             */
            void render(
                        const Mind::Scalar& relativeX = 0.f,
                        const Mind::Scalar& relativeY = 0.f
                       ) ;


        protected:
            /**
             * @brief   Generate instances of an entity as particles.
             * @param   amount      Amount of particles to generate.
             * @param   entityID    ID of the entity to create instance of.
             */
            void generateParticles(
                                   const unsigned int& amount,
                                   const unsigned int& entityID
                                  ) ;

            /**
             * @brief   Set parameters to particle as position, rotation or
             *          whatever else.
             * @param   particle    The particle to customize.
             */
            virtual void setParticleParameters(AbstractEntityInstance* particle) = 0 ;

            /**
             * @brief   Get iterator on the first particle.
             * @return  Iterator pointing on the first particle of the
             *          AbstractParticleGenerator.
             */
            ParticlesIterator begin() ;

            /**
             * @brief   Get iterator on the last particle.
             * @return  Iterator pointing on the last particle of the
             *          AbstractParticleGenerator.
             */
            ParticlesIterator end() ;


                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Get application context to access some required objects.
             * @return  The application context used by many other classes.
             */
            AbstractApplicationContext* getContext() const ;

    } ;

} ;


#endif
