#ifndef __BANE_TYPEDVALUE__
#define __BANE_TYPEDVALUE__

#include <memory>
#include <string>

namespace Bane {
    /**
     * Store a value of a single type at a time.
     */
    class TypedValue final {
        public:
            /**
             * List of the available types.
             */
            enum class Type: uint8_t {
                Char,
                Int8,
                UInt8,
                Int16,
                UInt16,
                Int32,
                UInt32,
                Int64,
                UInt64,
                Float,
                Double,
                String
            } ;

        private:
            /**
             * Union for storing the values.
             * Keep in mind that sizeof<std::unique_ptr<>> = 8, no over cost!
             */
            union ValUnion {
                char vChar ;
                int8_t vInt8 ;
                uint8_t vUInt8 ;
                int16_t vInt16 ;
                uint16_t vUInt16 ;
                int32_t vInt32 ;
                uint32_t vUInt32 ;
                int64_t vInt64 ;
                uint64_t vUInt64 ;
                float vFloat ;
                double vDouble ;
                std::unique_ptr<std::string> vString ;

                ValUnion() {}
                ~ValUnion() {}
                operator char() { return vChar ; }
                operator int8_t() { return vInt8 ; }
                operator uint8_t() { return vUInt8 ; }
                operator int16_t() { return vInt16 ; }
                operator uint16_t() { return vUInt16 ; }
                operator int32_t() { return vInt32 ; }
                operator uint32_t() { return vUInt32 ; }
                operator int64_t() { return vInt64 ; }
                operator uint64_t() { return vUInt64 ; }
                operator float() { return vFloat ; }
                operator double() { return vDouble ; }
                operator std::string() { return *(vString.get()) ; }
            } ;

            /**
             * Type of the value.
             */
            TypedValue::Type m_type ;

            /**
             * Value contained in the current object.
             */
            ValUnion m_value ;

        public:
            /** Construct a new instance of TypedValue for Char. */
            TypedValue(const char val): m_type(Type::Char) { m_value.vChar = val ; }

            /** Construct a new instance of TypedValue for Int8. */
            TypedValue(const int8_t val): m_type(Type::Int8) { m_value.vInt8 = val ; }

            /** Construct a new instance of TypedValue for UInt8. */
            TypedValue(const uint8_t val): m_type(Type::UInt8) { m_value.vUInt8 = val ; }

            /** Construct a new instance of TypedValue for Int16. */
            TypedValue(const int16_t val): m_type(Type::Int16) { m_value.vInt16 = val ; }

            /** Construct a new instance of TypedValue for UInt16. */
            TypedValue(const uint16_t val): m_type(Type::UInt16) { m_value.vUInt16 = val ; }

            /** Construct a new instance of TypedValue for Int32. */
            TypedValue(const int32_t val): m_type(Type::Int32) { m_value.vInt32 = val ; }

            /** Construct a new instance of TypedValue for UInt32. */
            TypedValue(const uint32_t val): m_type(Type::UInt32) { m_value.vUInt32 = val ; }

            /** Construct a new instance of TypedValue for Int64. */
            TypedValue(const int64_t val): m_type(Type::Int64) { m_value.vInt64 = val ; }

            /** Construct a new instance of TypedValue for UInt64. */
            TypedValue(const uint64_t val): m_type(Type::UInt64) { m_value.vUInt64 = val ; }

            /** Construct a new instance of TypedValue for Float. */
            TypedValue(const float val): m_type(Type::Float) { m_value.vFloat = val ; }

            /** Construct a new instance of TypedValue for Double. */
            TypedValue(const double val): m_type(Type::Double) { m_value.vDouble = val ; }

            /** Construct a new instance of TypedValue for String. */
            TypedValue(const std::string& val): m_type(Type::String) {
                m_value.vString = std::make_unique<std::string>(val) ;
            }

            /**
             * Get the type of the current value.
             * @return  Type of the current value.
             */
            TypedValue::Type type() const {
                return m_type ;
            }

            /**
             * Convert the value to the wanted type if possible.
             * @return  The current value casted to the wanted type.
             */
            template<typename T>
            T value() const {
                return static_cast<T>(m_value) ;
            }
    } ;
}

#endif
