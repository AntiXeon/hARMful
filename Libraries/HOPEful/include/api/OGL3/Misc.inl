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

inline Types::Void bindFragDataLocation(Types::UInt program, Types::UInt colorNumber, const Types::Char* name) {
    return glBindFragDataLocation(program, colorNumber, name) ;
}

inline Types::Void bindFragDataLocationIndexed(Types::UInt program, Types::UInt colorNumber, Types::UInt index, const Types::Char* name) {
    return glBindFragDataLocationIndexed(program, colorNumber, index, name) ;
}

inline Types::Enum getError() {
    return glGetError() ;
}

inline Types::Int getFragDataIndex(Types::UInt program, const Types::Char* name) {
    return glGetFragDataIndex(program, name) ;
}

inline Types::Int getFragDataLocation(Types::UInt program, const Types::Char* name) {
    return glGetFragDataLocation(program, name) ;
}

inline Types::Void getMultisamplefv(Types::Enum pname, Types::UInt index, Types::Float* val) {
    return glGetMultisamplefv(pname, index, val) ;
}

inline Types::Void getTransformFeedbackVarying(Types::UInt program, Types::UInt index, Types::Size bufSize, Types::Size* length, Types::Size* size, Types::Enum* type, Types::Char* name) {
    return glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name) ;
}

inline Types::Void hint(Types::Enum target, Types::Enum mode) {
    return glHint(target, mode) ;
}

inline Types::Void pixelStoref(Types::Enum pname, Types::Float param) {
    return glPixelStoref(pname, param) ;
}

inline Types::Void pixelStorei(Types::Enum pname, Types::Int param) {
    return glPixelStorei(pname, param) ;
}

inline Types::Void primitiveRestartIndex(Types::UInt index) {
    return glPrimitiveRestartIndex(index) ;
}

inline Types::Void provokingVertex(Types::Enum provokeMode) {
    return glProvokingVertex(provokeMode) ;
}

inline Types::Void readPixels(Types::Int x, Types::Int y, Types::Size width, Types::Size height, Types::Enum format, Types::Enum type, Types::Void* data) {
    return glReadPixels(x, y, width, height, format, type, data) ;
}

inline Types::Void sampleCoverage(Types::Clampf value, Types::Boolean invert) {
    return glSampleCoverage(value, invert) ;
}

inline Types::Void sampleMaski(Types::UInt maskNumber, Types::BitField mask) {
    return glSampleMaski(maskNumber, mask) ;
}

