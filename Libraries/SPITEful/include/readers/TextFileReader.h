#ifndef __SPITE_TEXT_FILE_READER__
#define __SPITE_TEXT_FILE_READER__

#include <string>
#include <readers/FileReader.h>

namespace Spite {

    /**
     * @brief   A TextFileReader is used to read text files.
     *
     * @author  Denis CARLUS
     * @version 1.0     08/23/2015
     */
    class TextFileReader : public FileReader {
        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /** @brief  Creation of a TextFileReader. */
            TextFileReader() ;

            /** @brief  Destruction of a TextFileReader. */
            virtual ~TextFileReader() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Read a line into the file.
             * @param   text    The line that is read.
             * @return  The line that is read.
             */
            std::string& readLine(std::string& readLine) ;
    } ;

} ;


#endif
