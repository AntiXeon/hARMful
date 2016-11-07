#ifndef __SIN_IMAGE_ENTITY_FACTORY__
#define __SIN_IMAGE_ENTITY_FACTORY__


#include <map>
#include <string>
#include <Path.h>
#include <scene_objects/entities/IImageEntity.h>


namespace Sin {

    /**
     * @brief   An ImageEntityFactory is used to generate an IImageEntity from
     *          the given file type. It can be extended by adding new extensions
     *          and functions.
     * @author  CB (c) 2016
     * @version 0.1    2016/03/31
     */
    class ImageEntityFactory {
        public:
            /**
             * @brief   Definition of the functions used to create new IEntity
             *          objects.
             */
            typedef IImageEntity* (*CreateEntityMethod)(const Spite::Path&) ;

        private:
            /**
             * @brief   Methods used to generate the IImageEntity objects by
             *          their extension. For example, <i>png</i>, <i>jpg</i>,
             *          etc.
             *          All are related to a function that allows the creation
             *          of the corresponding IEntity.
             */
            std::map<std::string, CreateEntityMethod> m_factoryMethods ;

        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create an ImageEntityFactory.
             */
            ImageEntityFactory() ;

            /**
             * @brief Destruction of the ImageEntityFactory.
             */
            virtual ~ImageEntityFactory() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Create a new IImageEntity from its filepath.
             * @param   filepath    Path to the file to load.
             * @return  The created IImageEntity, NULL in the file is not
             *          supported.
             */
            IImageEntity* createEntityFromPath(const Spite::Path& filepath) ;


            /**
             * @brief   Add an extension and the corresponding function used to
             *          generate the IEntity from the given file.
             * @param   extension   Extension of the file to be able to parse in
             *                      order to generate an IEntity.
             * @param   function    Pointer to the function used to generate the
             *                      IEntity.
             * @warning If the extension already exists, the function is
             *          replaced by the new one.
             */
            void addCreationMethod(
                                   const std::string& extension,
                                   CreateEntityMethod function
                                  ) ;
    } ;

} ;


#endif
