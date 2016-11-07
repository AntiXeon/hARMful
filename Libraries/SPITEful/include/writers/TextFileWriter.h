#ifndef __SPITE_TEXT_FILE_WRITER__
#define __SPITE_TEXT_FILE_WRITER__


#include <string>
#include <writers/FileWriter.h>


namespace Spite {

    /**
     * @brief   A TextFileWriter is used to write text files.
     *
     * @author  Denis CARLUS
     * @version 1.0     08/23/2015
     */
    class TextFileWriter : public FileWriter {
        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /** @brief  Creation of a TextFileWriter. */
            TextFileWriter() ;

            /** @brief  Destruction of a TextFileWriter. */
            virtual ~TextFileWriter() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Read a line from the file.
             * @param   text    The text to write.
             */
            void write(const std::string& text) ;
    } ;

} ;


#endif
