#ifndef __SPITE_IMAGE_FILE__
#define __SPITE_IMAGE_FILE__


#include <File.h>
#include <interfaces/IFileData.h>


namespace Spite {
    /**
     * @brief   Base class for a file containing an image.
     *
     * @author  Denis CARLUS
     * @version 1.0     03/09/2016
     */
    class ImageFile : public File {
        private:
            /**
             * @brief   File descriptor.
             */
            FILE* m_file ;

            /**
             * @brief   Position of the data to read/write in the data buffer.
             */
            unsigned int m_dataPosition ;


        protected:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a new ImageFile.
             * @param   path    Path of the file to open.
             * @param   format  Color format used by the image file.
             */
            ImageFile(const std::string& path) ;

            /**
             * @brief   Destruction of the ImageFile.
             */
            virtual ~ImageFile() ;


                                                             /*** UTILITIES ***/
        public:
            /**
             * @brief   Load a data at a given place on disk.
             * @param   filedata    File data to store data in.
             */
            bool load(IFileData* filedata) throw(Doom::IOException) ;

            /**
             * @brief   Save a data at a given place on disk.
             * @param   output      Raw data to write on disk. They can be
             *                      processed before saving.
             * @param   path        Path to the location on filesystem.
             */
            bool save(
                      IFileData* output,
                      const std::string& path
                     ) throw(Doom::IOException) ;


        protected:
            /**
             * @brief   Open the JPEGFile in the given mode.
             * @param   mode    Mode to access BaseFile and perform some
             *                  operations on it.
             */
            void open(OpenMode mode) ;

            /** @brief  Close the JPEGFile. */
            void close() ;

            /**
             * @brief   Parse the image file and store raw data in the @a output
             *          data.
             * @param   output  Output the raw data from the image file.
             */
            virtual bool parse(IFileData* output) = 0 ;


        protected:
            /**
             * @brief   Get the file descriptor.
             * @return  The descriptor of the file.
             */
            FILE* getDescriptor() const ;
    } ;
} ;

#endif
