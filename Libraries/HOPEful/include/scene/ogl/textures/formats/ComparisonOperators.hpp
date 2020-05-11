#ifndef __HOPE__GL_COMPARISON_OPERATORS__
#define __HOPE__GL_COMPARISON_OPERATORS__

#include <HopeAPI.hpp>

namespace Hope::GL {
    /**
     * Comparison operators.
     */
    enum ComparisonOperator : GLint {
        LessOrEqual = GL_LEQUAL,
        GreaterOrEqual = GL_GEQUAL,
        Less = GL_LESS,
        Greater = GL_GREATER,
        Equal = GL_EQUAL,
        NotEqual = GL_NOTEQUAL,
        Always = GL_ALWAYS,
        Never = GL_NEVER
    } ;
}

#endif
