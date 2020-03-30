#ifndef __SPITE__TEXT_DATA__
#define __SPITE__TEXT_DATA__

#include <interfaces/IFileData.hpp>
#include <vector>

namespace Spite {

    /**
     * Encapsulate a text that can be read / written in a file.
     */
    class TextData final : public IFileData {
        private:
            /**
             * Encapsulated text.
             */
            std::vector<unsigned char> m_text ;

        public:
            /**
             * Set the file data.
             */
            void setData(const std::string& data) {
                m_text.insert(m_text.begin(), data.begin(), data.end()) ;
            }

            /**
             * Get the image raw data.
             * return   Output the raw data of the image. Data is
             *          expected to be an array of bytes.
             * @warning @a data should not be initialized, an array is
             *          allocated on getting data.
             */
            exported std::vector<unsigned char>& data() {
                return m_text ;
            }

            /**
             * Get the text as string.
             */
            exported std::string toString() {
                return std::string(m_text.begin(), m_text.end()) ;
            }
    } ;
}

#endif
