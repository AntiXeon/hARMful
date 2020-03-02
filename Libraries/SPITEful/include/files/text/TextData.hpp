#ifndef __SPITE__TEXT_DATA__
#define __SPITE__TEXT_DATA__

#include <interfaces/IFileData.hpp>
#include <string>

namespace Spite {

    /**
     * Encapsulate a text that can be read / written in a file.
     */
    class TextData final : public IFileData {
        private:
            /**
             * Encapsulated text.
             */
            std::string m_text ;

        public:
            /**
             * Get the file data.
             */
            std::string& data() {
                return m_text ;
            }

            /**
             * Set the file data.
             */
            void setData(const std::string& data) {
                m_text = data ;
            }

            /**
             * Get the file raw data.
             * @param   data    Output the raw data of the file.
             * @param   size    Output the size of the file @a data.
             */
            exported void data(unsigned char*& data, unsigned int& size) override {
                data = reinterpret_cast<unsigned char*>(&m_text[0]) ;
                size = static_cast<unsigned int>(m_text.size()) ;
            }

            /**
             * Free data from memory.
             */
            exported void freeData() override {
                m_text.clear() ;
            }
    } ;
}

#endif
