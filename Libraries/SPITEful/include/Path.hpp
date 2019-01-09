#ifndef __SPITE__PATH__
#define __SPITE__PATH__

#include <iostream>
#include <string>
#include <vector>

namespace Spite {

    /**
     * @brief   A Path described the location of a file.
     *          It moreover allows to find in a convenient way its name and
     *          extension.
     *
     * @author  Denis CARLUS
     * @version 1.0     08/11/2015
     */
    class Path final {
        private:
            /** @brief  The absolute file path. */
            std::string m_absolutePath ;

            /** @brief  The name of the file, without its extension. */
            std::string m_filename ;

            /** @brief  The extension of the file, if it exists. */
            std::string m_extension ;


        public:
            /** @brief  Creation a Path. No file path is searched. */
            Path() = default ;

            /**
             * @brief   Creation a Path from a string. The path is converted to
             *          an absolute path if it is relative.
             * @param   filepath        The string to convert to Path.
             */
            Path(const std::string& filepath) ;

            /**
             * @brief   Implicitely convert Path to string.
             * @return  The absolute path.
             */
            operator std::string() const { return m_absolutePath; }

            /**
             * @brief   Get the absolute path to the file.
             * @return  The absolute path of the file.
             */
            const std::string& absolutePath() const ;

            /**
             * @brief   Get the name the file.
             * @return  The name the file.
             */
            const std::string& filename() const ;

            /**
             * @brief   Get the extension of the file.
             * @return  The extension of the file.
             */
            const std::string& extension() const ;

            /**
             * @brief   Get the directory in which the software is running.
             * @param   outCWD  Output result of the current working directory.
             */
            static void CurrentDirectory(std::string& outCWD) ;


        private:
            /**
             * @brief   Convert a relative path to absolute equivalent.
             * @param   filepath    The path to convert.
             */
            void convertToAbsolutePath(const std::string& filepath) ;

            /**
             * @brief   Extract the file name and extension from the path.
             */
            void extractFilenameAndExtension() ;
    } ;

} ;

#endif
