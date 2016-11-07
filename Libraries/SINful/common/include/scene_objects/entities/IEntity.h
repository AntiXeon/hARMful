#ifndef __SIN_INTERFACE_ENTITY__
#define __SIN_INTERFACE_ENTITY__


#include <string>
#include <MINDTypes.h>


namespace Sin {

    /**
     * @brief   An IEntity contains heavy data to be rendered on screen,
     *          as picture and/or sound for example.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/12
     */
    class IEntity {
        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Destruction of the IEntity.
             */
            virtual ~IEntity() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Load the IEntity data.
             * @param   path    Path to the file to load.
             * @return  TRUE on success, FALSE on fail loading the IEntity.
             */
            virtual bool load(const std::string& path) = 0 ;

            /**
             * @brief   Unload the IEntity data.
             * @return  TRUE on success, FALSE on fail.
             */
            virtual bool unload() = 0 ;
    } ;

} ;


#endif
