/*******************************************/
/* HOPEful - Part of the hARMful Engine    */
/*                                         */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    03/19/2015                 */
/* UPDATE:      03/19/2015                 */
/*                                         */
/* Inline OpenGL3.3 functions.             */
/*******************************************/

/**********************************************
This file is part of hARMful.

hARMful is free software: you can redistribute
it and/or modify it under the terms of the GNU
General  Public License  as published  by  the
Free Software Foundation,  either version 3 of
the  License,  or (at your option)  any  later
version.

hARMful is  distributed in  the hope  that  it
will  be  useful, but  WITHOUT  ANY  WARRANTY;
without   even   the   implied   warranty   of
MERCHANTABILITY  or  FITNESS FOR  A PARTICULAR
PURPOSE.  See the  GNU General  Public License
for more details.

You  should have  received a  copy of  the GNU
General  Public  License  along  with hARMful.
If not, see <http://www.gnu.org/licenses/>.
**********************************************/

inline Types::Void bindVertexArray(Types::UInt array) {
    return glBindVertexArray(array) ;
}

inline Types::Void deleteVertexArrays(Types::Size n, const Types::UInt* arrays) {
    return glDeleteVertexArrays(n, arrays) ;
}

inline Types::Void genVertexArrays(Types::Size n, Types::UInt* arrays) {
    return glGenVertexArrays(n, arrays) ;
}

inline Types::Void drawArrays(Types::Enum mode, Types::Int first, Types::Size count) {
    return glDrawArrays(mode, first, count) ;
}

inline Types::Void drawArraysInstanced(Types::Enum mode, Types::Int first, Types::Size count, Types::Size primcount) {
    return glDrawArraysInstanced(mode, first, count, primcount) ;
}

inline Types::Void drawElements(Types::Enum mode, Types::Size count, Types::Enum type, const Types::Void* indices) {
    return glDrawElements(mode, count, type, indices) ;
}

inline Types::Void drawElementsBaseVertex(Types::Enum mode, Types::Size count, Types::Enum type, Types::Void* indices, Types::Int basevertex) {
    return glDrawElementsBaseVertex(mode, count, type, indices, basevertex) ;
}

inline Types::Void drawElementsInstanced(Types::Enum mode, Types::Size count, Types::Enum type, const Types::Void* indices, Types::Size primcount) {
    return glDrawElementsInstanced(mode, count, type, indices, primcount) ;
}

inline Types::Void drawElementsInstancedBaseVertex(Types::Enum mode, Types::Size count, Types::Enum type, Types::Void* indices, Types::Size primcount, Types::Int basevertex) {
    return glDrawElementsInstancedBaseVertex(mode, count, type, indices, primcount, basevertex) ;
}

inline Types::Void drawRangeElements(Types::Enum mode, Types::UInt start, Types::UInt end, Types::Size count, Types::Enum type, const Types::Void* indices) {
    return glDrawRangeElements(mode, start, end, count, type, indices) ;
}

inline Types::Void drawRangeElementsBaseVertex(Types::Enum mode, Types::UInt start, Types::UInt end, Types::Size count, Types::Enum type, Types::Void* indices, Types::Int basevertex) {
    return glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex) ;
}

inline Types::Void multiDrawArrays(Types::Enum mode, const Types::Int* first, const Types::Size* count, Types::Size primcount) {
    return glMultiDrawArrays(mode, first, count, primcount) ;
}

inline Types::Void multiDrawElements(Types::Enum mode, const Types::Size* count, Types::Enum type, const Types::Void** indices, Types::Size primcount) {
    return glMultiDrawElements(mode, count, type, indices, primcount) ;
}

inline Types::Void multiDrawElementsBaseVertex(Types::Enum mode, const Types::Size* count, Types::Enum type, const Types::Void** indices, Types::Size primcount, Types::Int* basevertex) {
    return glMultiDrawElementsBaseVertex(mode, count, type, indices, primcount, basevertex) ;
}

inline Types::Boolean isVertexArray(Types::UInt array) {
    return glIsVertexArray(array) ;
}

