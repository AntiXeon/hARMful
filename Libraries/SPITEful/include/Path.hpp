#ifndef __SPITE__PATH__
#define __SPITE__PATH__

#include <iostream>
#include <string>
#include <vector>

namespace Spite {

    /**
     * A Path described the location of a file.
     * It moreover allows to find in a convenient way its name and extension.
     *
     * @warning The implementation depends on the platform on which it is
     *          compiled. Look at the src/platform folder for implementation.
     */
    class Path final {
        private:
            /**
             *  The absolute file path.
             */
            std::string m_absolutePath ;

            /**
             * The name of the file, without its extension.
             */
            std::string m_filename ;

            /**
             * The extension of the file, if it exists.
             */
            std::string m_extension ;


        public:
            /**
             * Creation a Path. No file path is searched.
             */
            Path() = default ;

            /**
             * Creation a Path from a string. The path is converted to an
             * absolute path if it is relative.
             * @param   filepath        The string to convert to Path.
             */
            Path(const std::string& filepath) ;

            /**
             * Implicitely convert Path to string.
             * @return  The absolute path.
             */
            operator std::string() const { return m_absolutePath; }

            /**
             * Get the absolute path to the file.
             * @return  The absolute path of the file.
             */
            const std::string& absolutePath() const ;

            /**
             * Get the name the file.
             * @return  The name the file.
             */
            const std::string& filename() const ;

            /**
             * Get the extension of the file.
             * @return  The extension of the file.
             */
            const std::string& extension() const ;

            /**
             * Get the directory in which the software is running.
             * @param   outCWD  Output result of the current working directory.
             */
            static void CurrentDirectory(std::string& outCWD) ;


        private:
            /**
             * Convert a relative path to absolute equivalent.
             * @param   filepath    The path to convert.
             */
            void convertToAbsolutePath(const std::string& filepath) ;

            /**
             * Extract the file name and extension from the path.
             */
            void extractFilenameAndExtension() ;
    } ;

} ;

#endif
