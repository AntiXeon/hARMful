#ifndef __GLSL2CPP__SHADER_FILE_AGGREGATOR__
#define __GLSL2CPP__SHADER_FILE_AGGREGATOR__

#include <ShaderFile.hpp>
#include <string>
#include <vector>

/**
 * Aggregation of shader files in a same shader directory.
 */
class ShaderFileAggregator final {
    private:
        /**
         * Relative path of the shader directory (from the shader directory).
         */
        std::string m_relativeDirectoryPath ;

        /**
         * Parent directory path.
         */
        std::string m_parentDirectoryPath ;

        /**
         * Name of the shader.
         */
        std::string m_shaderName ;

        /**
         * List of files in the directory.
         */
        std::vector<ShaderFile> m_files ;

    public:
        /**
         * Create a ShaderFileAggregator instance.
         */
        ShaderFileAggregator() = default ;

        /**
         * Create a ShaderFileAggregator instance.
         */
        ShaderFileAggregator(
            const std::string& relativeDirectoryPath,
            const std::string& parentDirectoryPath,
            const std::string& shaderName
        ) ;

        /**
         * Store the content of the files into .hpp/.cpp files.
         * @param   shadersDir  Path to the shaders directory.
         * @param   headersPath Path to the C++ headers output.
         * @param   sourcesPath Path to the C++ sources output.
         */
        void storeIntoCppFiles(
            const std::string& shadersDir,
            const std::string& headersPath,
            const std::string& sourcesPath
        ) const ;

        /**
         * Insert a ShaderFile.
         */
        void insert(const ShaderFile& file) {
            m_files.push_back(file) ;
        }

        /**
         * Get the relative directory path.
         */
        const std::string& directoryPath() const {
            return m_relativeDirectoryPath ;
        }

        /**
         * Get the parent directory path.
         */
        const std::string& parentDirectoryPath() const {
            return m_parentDirectoryPath ;
        }

        /**
         * Get the shader name.
         */
        const std::string& shaderName() const {
            return m_shaderName ;
        }

        /**
         * Print content on console.
         */
        void debug() ;

    private:
        /**
         * Write C++ header files.
         * @param   shadersDir  Path to the shaders directory.
         * @param   headersPath Path to the C++ headers output.
         */
        void writeHeaderFiles(
            const std::string& shadersDir,
            const std::string& headersPath
        ) const ;

        /**
         * Write C++ source files.
         * @param   shadersDir  Path to the shaders directory.
         * @param   sourcesPath Path to the C++ sources output.
         */
        void writeSourceFiles(
            const std::string& shadersDir,
            const std::string& sourcesPath
        ) const ;

        /**
         * Create the directory to store the output C++ file.
         * @param   cppDirectory    Directory of the output (header or source).
         * @param   cppExtension    Extension of the C++ output file.
         * @return  Path of the output C++ file that can be written.
         */
        std::string createCppDirectory(
            const std::string& cppDirectory,
            const std::string& cppExtension
        ) const ;

        /**
         * Get the C++ variable suffix to add to the variable name from the
         * shader extension.
         * @param   extension   Extension of the shader file.
         * @return  The variable suffix for the C++ generated file.
         */
        std::string getCppVariableSuffixFromExtension(const std::string& extension) const ;
} ;

#endif
