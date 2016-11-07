#ifndef __SIN_ABSTRACT_SCENE_OBJECT__
#define __SIN_ABSTRACT_SCENE_OBJECT__


#include <MINDTypes.h>
#include <geometry/points/Point2Df.h>


namespace Sin {

    /**
     * @brief   An AbstractSceneObject can be inherited in many object that are
     *          found in the scene hierarchy. Each AbstractSceneObject is
     *          attached to a Node.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/11
     */
    class AbstractSceneObject {
        private:
            /**
             * @brief   Position of the AbstractSceneObject in the scene.
             */
            Mind::Point2Df m_position ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create an AbstractSceneObject at position (0,0).
             */
            AbstractSceneObject() ;

            /**
             * @brief   Create an AbstractSceneObject at the given position.
             * @param   position    Position of the AbstractSceneObject when
             *                      created.
             */
            AbstractSceneObject(const Mind::Point2Df& position) ;

            /**
             * @brief   Create an AbstractSceneObject at the given position.
             * @param   positionX   Position on X axis.
             * @param   positionY   Position on Y axis.
             */
            AbstractSceneObject(
                                const Mind::Scalar& positionX,
                                const Mind::Scalar& positionY
                               ) ;

            /**
             * @brief   Destruction of the AbstractSceneObject.
             */
            virtual ~AbstractSceneObject() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Update the AbstractSceneObject.
             */
            virtual void update() = 0 ;

            /**
             * @brief   Render the AbstractSceneObject at its position,
             *          relatively to the given position.
             * @param   relative    Relative position from which the rendering
             *                      must be done.
             */
            virtual void render(const Mind::Point2Df& relative) = 0 ;

            /**
             * @brief   Render the AbstractSceneObject at its position,
             *          relatively to the given position.
             * @param   relativeX   Relative position on X from which the
             *                      rendering must be done.
             * @param   relativeY   Relative position on Y from which the
             *                      rendering must be done.
             */
            void render(
                        const Mind::Scalar& relativeX = 0.f,
                        const Mind::Scalar& relativeY = 0.f
                       ) ;


            /**
             * @brief   Set the position of the AbstractSceneObject relatively
             *          to its current position.
             * @param   relative    Translation of the AbstractSceneObject.
             */
            void translate(const Mind::Point2Df& relative) ;

            /**
             * @brief   Set the position of the AbstractSceneObject relatively
             *          to its current position.
             * @param   relativeX   Translation of the AbstractSceneObject on X
             *                      axis.
             * @param   relativeY   Translation of the AbstractSceneObject on Y
             *                      axis.
             */
            void translate(
                           const Mind::Scalar& relativeX,
                           const Mind::Scalar& relativeY
                          ) ;


                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Set the absolute position of the AbstractSceneObject.
             * @param   position    New position of the AbstractSceneObject.
             */
            void setPosition(const Mind::Point2Df& position) ;

            /**
             * @brief   Set the absolute position of the AbstractSceneObject.
             * @param   positionX   New position on X of the
             *                      AbstractSceneObject.
             * @param   positionY   New position on Y of the
             *                      AbstractSceneObject.
             */
            void setPosition(
                             const Mind::Scalar& positionX,
                             const Mind::Scalar& positionY
                            ) ;

            /**
             * @brief   Get the position of the AbstractSceneObject.
             * @return  The position of the current AbstractSceneObject.
             */
            const Mind::Point2Df& getPosition() const ;

    } ;

} ;


 #endif
