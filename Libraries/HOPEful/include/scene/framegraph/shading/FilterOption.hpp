#ifndef __HOPE__FILTER_OPTION__
#define __HOPE__FILTER_OPTION__

#include <string>

namespace Hope {
    /**
     * A FilterOption is used to render or not some objects.
     * If a FrameGraph branch defines a FilterOption to render objects, only the
     * objects of the scene graph having a such FilterOption can be rendered
     * (the other ones are discarded).
     * The FilterOptions are defined in the material of the objects.
     */
    class FilterOption final {
        private:
            /**
             * Name of the filter option.
             */
            std::string m_name ;

            /**
             * Value of the filter option.
             */
            std::string m_value ;

        public:
            /**
             * Set the name of the filter option.
             */
            void setName(const std::string& name) {
                m_name = name ;
            }

            /**
             * Get the name of the filter option.
             */
            std::string name() const {
                return m_name ;
            }

            /**
             * Set the value of the filter option.
             */
            void setValue(const std::string& value) {
                m_value = value ;
            }

            /**
             * Get the value of the filter option.
             */
            std::string value() const {
                return m_value ;
            }

            /**
             * Compare if two filter options are equal.
             */
            bool operator==(const FilterOption& other) {
                return (m_name == other.m_name) && (m_value == other.m_value) ;
            }

            /**
             * Compare if two filter options are not equal.
             */
            bool operator!=(const FilterOption& other) {
                return !(*this == other) ;
            }
    } ;
}

#endif
