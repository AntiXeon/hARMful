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

inline Types::Void genQueries(Types::Size n, Types::UInt* ids) {
    return glGenQueries(n, ids) ;
}

inline Types::Void deleteQueries(Types::Size n, const Types::UInt* ids) {
    return glDeleteQueries(n, ids) ;
}

inline Types::Void beginConditionalRender(Types::UInt id, Types::Enum mode) {
    return glBeginConditionalRender(id, mode) ;
}

inline Types::Void beginQuery(Types::Enum target, Types::UInt id) {
    return glBeginQuery(target, id) ;
}

inline Types::Void beginTransformFeedback(Types::Enum primitiveMode) {
    return glBeginTransformFeedback(primitiveMode) ;
}

inline Types::Void endConditionalRender() {
    return glEndConditionalRender() ;
}

inline Types::Void endQuery(Types::Enum target) {
    return glEndQuery(target) ;
}

inline Types::Void endTransformFeedback() {
    return glEndTransformFeedback() ;
}

inline Types::Void getQueryObjectiv(Types::UInt id, Types::Enum pname, Types::Int* params) {
    return glGetQueryObjectiv(id, pname, params) ;
}

inline Types::Void getQueryObjectuiv(Types::UInt id, Types::Enum pname, Types::UInt* params) {
    return glGetQueryObjectuiv(id, pname, params) ;
}

inline Types::Void getQueryObjecti64v(Types::UInt id, Types::Enum pname, Types::Int64* params) {
    return glGetQueryObjecti64v(id, pname, params) ;
}

inline Types::Void getQueryObjectui64v(Types::UInt id, Types::Enum pname, Types::UInt64* params) {
    return glGetQueryObjectui64v(id, pname, params) ;
}

inline Types::Void getQueryiv(Types::Enum target, Types::Enum pname, Types::Int* params) {
    return glGetQueryiv(target, pname, params) ;
}

inline Types::Void queryCounter(Types::UInt id, Types::Enum target) {
    return glQueryCounter(id, target) ;
}

inline Types::Void transformFeedbackVaryings(Types::UInt program, Types::Size count, const Types::Char** varyings, Types::Enum bufferMode) {
    return glTransformFeedbackVaryings(program, count, varyings, bufferMode) ;
}

inline Types::Boolean isQuery(Types::UInt id) {
    return glIsQuery(id) ;
}

