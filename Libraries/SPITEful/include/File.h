#ifndef __SPITE_FILE__
#define __SPITE_FILE__


#include <Path.h>
#include <interfaces/ILoadable.h>
#include <interfaces/ISavable.h>


namespace Spite {

    /**
     * @brief   A File is the representation of a file in file system.
     *          A File can be saved and loaded.
     *
     * @author  Denis CARLUS
     * @version 1.0     08/13/2015
     */
    class File : public ILoadable, public ISavable {
        public:
            /**
             * @brief   Mode in which the BaseFile can be opened.
             */
            enum OpenMode {
                           Open_None        = 0,
                           Open_ReadOnly    = 1,
                           Open_Append      = 2,
                           Open_WriteOnly   = 4,
                           Open_ReadWrite   = Open_ReadOnly | Open_WriteOnly,
                           Open_ReadAppend  = Open_ReadOnly | Open_Append
                          } ;


        protected:
            /** @brief  Path to the file. */
            Path m_path ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Creation a File from a string.
             * @param   filepath    Path to the file to open.
             */
            File(const std::string& filepath) ;

            /** @brief  Destroy the File. */
            virtual ~File() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Open the File in the given mode.
             * @param   mode    Mode to access File and perform some
             *                  operations on it.
             */
            virtual void open(OpenMode mode) = 0 ;

            /** @brief  Close the File. */
            virtual void close() = 0 ;


        protected:
            /** @brief  Create the tree of folders to the File. */
            void createTreeToFile() ;


        public:
                                                               /*** GETTERS ***/
            /**
             * @brief   Get the path to the File.
             * @return  The path of the File.
             */
            const Path& getPath() const ;
    } ;

} ;


#endif
