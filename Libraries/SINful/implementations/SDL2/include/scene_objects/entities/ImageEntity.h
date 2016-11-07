#ifndef __SIN_SDL2_IMAGE_ENTITY__
#define __SIN_SDL2_IMAGE_ENTITY__


#include <scene_objects/entities/IEntity.h>
#include <scene_objects/ObjectRotation2D.h>
#include <files/images/data/RawImage.h>  // SPITEful
#include <MINDTypes.h>                  // MINDful
#include <SDL2/SDL.h>
#include <string>

namespace Sin {

    /**
     * @brief   An ImageEntity loads a picture file and stores raw data in
     *          video memory.
     * @author  CB (c) 2016
     * @version 0.1     2016/03/30
     */
    class ImageEntity : public IEntity {
        private:
            /**
             * @brief   Bounds of the texture (width and height) to draw it.
             */
            SDL_Rect m_bounds ;

            /**
             * @brief   Texture used to draw instances of the ImageEntity at
             *          different position on screen.
             */
            SDL_Texture* m_texture ;


        protected:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create an ImageEntity.
             */
            ImageEntity() ;

            /**
             * @brief   Destruction of the ImageEntity.
             */
            virtual ~ImageEntity() ;


        public:
                                                             /*** UTILITIES ***/
            /**
             * @brief   Render the ImageEntity at the given position.
             * @param   x   Position on X axis of the rendered entity.
             * @param   y   Position on Y axis of the rendered entity.
             */
            void renderAt(
                          const Mind::Scalar& x,
                          const Mind::Scalar& y
                         ) ;

            /**
             * @brief   Render the ImageEntity at the given position.
             * @param   x           Position on X axis of the rendered entity.
             * @param   y           Position on Y axis of the rendered entity.
             * @param   rotation    Rotation of the rendered entity.
             * @param   scale       Scale of the rendered entity.
             */
            void renderAt(
                          const Mind::Scalar& x,
                          const Mind::Scalar& y,
                          const ObjectRotation2D& rotation,
                          const Mind::Scalar& scale = 1.f
                         ) ;


        protected:
                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Set the texture of the ImageEntity and its bounds.
             * @param   texture     Texture of the ImageEntity.
             * @param   bounds  Bounds of the texture (width and height).
             */
            void setData(SDL_Texture* texture, const SDL_Rect& bounds) ;
    } ;

} ;


#endif
