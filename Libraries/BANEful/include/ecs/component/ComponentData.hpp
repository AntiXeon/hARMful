#ifndef __BANE_COMPONENTDATA__
#define __BANE_COMPONENTDATA__

#include "TypedValue.hpp"
#include <vector>

namespace Bane {
    /**
     * Specific data of a Component.
     */
    class ComponentData {
        private:
            /**
             * Values of the ComponentData.
             * They should be accessed by named values as enumerations in
             * inherited classes.
             */
            std::vector<TypedValue> m_values ;

        public:
            /**
             * Available quantity of a Component type on a single Entity.
             */
            enum class Quantity : uint8_t {
                One = 0,
                Many = 1
            } ;

            /**
             * Get the quantity of the Component type a single Entity can bear.
             */
            virtual Quantity quantity() const = 0 ;

        protected:
            /**
             * Get the value stored at the wanted index.
             * @return  The value at the wanted index.
             */
            TypedValue& value(const unsigned int index) {
                return m_values[index] ;
            }
    } ;
}

#endif
