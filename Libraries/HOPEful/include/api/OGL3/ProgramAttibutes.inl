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

inline Types::Void bindAttribLocation(Types::UInt program, Types::UInt index, const Types::Char* name) {
    return glBindAttribLocation(program, index, name) ;
}

inline Types::Void getActiveAttrib(Types::UInt program, Types::UInt index, Types::Size bufSize, Types::Size* length, Types::Int* size, Types::Enum* type, Types::Char* name) {
    return glGetActiveAttrib(program, index, bufSize, length, size, type, name) ;
}

inline Types::Int getAttribLocation(Types::UInt program, const Types::Char* name) {
    return glGetAttribLocation(program, name) ;
}

inline Types::Void enableVertexAttribArray(Types::UInt index) {
    return glEnableVertexAttribArray(index) ;
}

inline Types::Void disableVertexAttribArray(Types::UInt index) {
    return glDisableVertexAttribArray(index) ;
}

inline Types::Void getVertexAttribdv(Types::UInt index, Types::Enum pname, Types::Double* params) {
    return glGetVertexAttribdv(index, pname, params) ;
}

inline Types::Void getVertexAttribfv(Types::UInt index, Types::Enum pname, Types::Float* params) {
    return glGetVertexAttribfv(index, pname, params) ;
}

inline Types::Void getVertexAttribiv(Types::UInt index, Types::Enum pname, Types::Int* params) {
    return glGetVertexAttribiv(index, pname, params) ;
}

inline Types::Void getVertexAttribIiv(Types::UInt index, Types::Enum pname, Types::Int* params) {
    return glGetVertexAttribIiv(index, pname, params) ;
}

inline Types::Void getVertexAttribIuiv(Types::UInt index, Types::Enum pname, Types::UInt* params) {
    return glGetVertexAttribIuiv(index, pname, params) ;
}

inline Types::Void getVertexAttribPointerv(Types::UInt index, Types::Enum pname, Types::Void** pointer) {
    return glGetVertexAttribPointerv(index, pname, pointer) ;
}

inline Types::Void vertexAttrib1f(Types::UInt index, Types::Float v0) {
    return glVertexAttrib1f(index, v0) ;
}

inline Types::Void vertexAttrib1s(Types::UInt index, Types::Short v0) {
    return glVertexAttrib1s(index, v0) ;
}

inline Types::Void vertexAttrib1d(Types::UInt index, Types::Double v0) {
    return glVertexAttrib1d(index, v0) ;
}

inline Types::Void vertexAttribI1i(Types::UInt index, Types::Int v0) {
    return glVertexAttribI1i(index, v0) ;
}

inline Types::Void vertexAttribI1ui(Types::UInt index, Types::UInt v0) {
    return glVertexAttribI1ui(index, v0) ;
}

inline Types::Void vertexAttrib2f(Types::UInt index, Types::Float v0, Types::Float v1) {
    return glVertexAttrib2f(index, v0, v1) ;
}

inline Types::Void vertexAttrib2s(Types::UInt index, Types::Short v0, Types::Short v1) {
    return glVertexAttrib2s(index, v0, v1) ;
}

inline Types::Void vertexAttrib2d(Types::UInt index, Types::Double v0, Types::Double v1) {
    return glVertexAttrib2d(index, v0, v1) ;
}

inline Types::Void vertexAttribI2i(Types::UInt index, Types::Int v0, Types::Int v1) {
    return glVertexAttribI2i(index, v0, v1) ;
}

inline Types::Void vertexAttribI2ui(Types::UInt index, Types::UInt v0, Types::UInt v1) {
    return glVertexAttribI2ui(index, v0, v1) ;
}

inline Types::Void vertexAttrib3f(Types::UInt index, Types::Float v0, Types::Float v1, Types::Float v2) {
    return glVertexAttrib3f(index, v0, v1, v2) ;
}

inline Types::Void vertexAttrib3s(Types::UInt index, Types::Short v0, Types::Short v1, Types::Short v2) {
    return glVertexAttrib3s(index, v0, v1, v2) ;
}

inline Types::Void vertexAttrib3d(Types::UInt index, Types::Double v0, Types::Double v1, Types::Double v2) {
    return glVertexAttrib3d(index, v0, v1, v2) ;
}

inline Types::Void vertexAttribI3i(Types::UInt index, Types::Int v0, Types::Int v1, Types::Int v2) {
    return glVertexAttribI3i(index, v0, v1, v2) ;
}

inline Types::Void vertexAttribI3ui(Types::UInt index, Types::UInt v0, Types::UInt v1, Types::UInt v2) {
    return glVertexAttribI3ui(index, v0, v1, v2) ;
}

inline Types::Void vertexAttrib4f(Types::UInt index, Types::Float v0, Types::Float v1, Types::Float v2, Types::Float v3) {
    return glVertexAttrib4f(index, v0, v1, v2, v3) ;
}

inline Types::Void vertexAttrib4s(Types::UInt index, Types::Short v0, Types::Short v1, Types::Short v2, Types::Short v3) {
    return glVertexAttrib4s(index, v0, v1, v2, v3) ;
}

inline Types::Void vertexAttrib4d(Types::UInt index, Types::Double v0, Types::Double v1, Types::Double v2, Types::Double v3) {
    return glVertexAttrib4d(index, v0, v1, v2, v3) ;
}

inline Types::Void vertexAttrib4Nub(Types::UInt index, Types::UByte v0, Types::UByte v1, Types::UByte v2, Types::UByte v3) {
    return glVertexAttrib4Nub(index, v0, v1, v2, v3) ;
}

inline Types::Void vertexAttribI4i(Types::UInt index, Types::Int v0, Types::Int v1, Types::Int v2, Types::Int v3) {
    return glVertexAttribI4i(index, v0, v1, v2, v3) ;
}

inline Types::Void vertexAttribI4ui(Types::UInt index, Types::UInt v0, Types::UInt v1, Types::UInt v2, Types::UInt v3) {
    return glVertexAttribI4ui(index, v0, v1, v2, v3) ;
}

inline Types::Void vertexAttrib1fv(Types::UInt index, const Types::Float* v) {
    return glVertexAttrib1fv(index, v) ;
}

inline Types::Void vertexAttrib1sv(Types::UInt index, const Types::Short* v) {
    return glVertexAttrib1sv(index, v) ;
}

inline Types::Void vertexAttrib1dv(Types::UInt index, const Types::Double* v) {
    return glVertexAttrib1dv(index, v) ;
}

inline Types::Void vertexAttribI1iv(Types::UInt index, const Types::Int* v) {
    return glVertexAttribI1iv(index, v) ;
}

inline Types::Void vertexAttribI1uiv(Types::UInt index, const Types::UInt* v) {
    return glVertexAttribI1uiv(index, v) ;
}

inline Types::Void vertexAttrib2fv(Types::UInt index, const Types::Float* v) {
    return glVertexAttrib2fv(index, v) ;
}

inline Types::Void vertexAttrib2sv(Types::UInt index, const Types::Short* v) {
    return glVertexAttrib2sv(index, v) ;
}

inline Types::Void vertexAttrib2dv(Types::UInt index, const Types::Double* v) {
    return glVertexAttrib2dv(index, v) ;
}

inline Types::Void vertexAttribI2iv(Types::UInt index, const Types::Int* v) {
    return glVertexAttribI2iv(index, v) ;
}

inline Types::Void vertexAttribI2uiv(Types::UInt index, const Types::UInt* v) {
    return glVertexAttribI2uiv(index, v) ;
}

inline Types::Void vertexAttrib3fv(Types::UInt index, const Types::Float* v) {
    return glVertexAttrib3fv(index, v) ;
}

inline Types::Void vertexAttrib3sv(Types::UInt index, const Types::Short* v) {
    return glVertexAttrib3sv(index, v) ;
}

inline Types::Void vertexAttrib3dv(Types::UInt index, const Types::Double* v) {
    return glVertexAttrib3dv(index, v) ;
}

inline Types::Void vertexAttribI3iv(Types::UInt index, const Types::Int* v) {
    return glVertexAttribI3iv(index, v) ;
}

inline Types::Void vertexAttribI3uiv(Types::UInt index, const Types::UInt* v) {
    return glVertexAttribI3uiv(index, v) ;
}

inline Types::Void vertexAttrib4fv(Types::UInt index, const Types::Float* v) {
    return glVertexAttrib4fv(index, v) ;
}

inline Types::Void vertexAttrib4sv(Types::UInt index, const Types::Short* v) {
    return glVertexAttrib4sv(index, v) ;
}

inline Types::Void vertexAttrib4dv(Types::UInt index, const Types::Double* v) {
    return glVertexAttrib4dv(index, v) ;
}

inline Types::Void vertexAttrib4iv(Types::UInt index, const Types::Int* v) {
    return glVertexAttrib4iv(index, v) ;
}

inline Types::Void vertexAttrib4bv(Types::UInt index, const Types::Byte* v) {
    return glVertexAttrib4bv(index, v) ;
}

inline Types::Void vertexAttrib4ubv(Types::UInt index, const Types::UByte* v) {
    return glVertexAttrib4ubv(index, v) ;
}

inline Types::Void vertexAttrib4usv(Types::UInt index, const Types::UShort* v) {
    return glVertexAttrib4usv(index, v) ;
}

inline Types::Void vertexAttrib4uiv(Types::UInt index, const Types::UInt* v) {
    return glVertexAttrib4uiv(index, v) ;
}

inline Types::Void vertexAttrib4Nbv(Types::UInt index, const Types::Byte* v) {
    return glVertexAttrib4Nbv(index, v) ;
}

inline Types::Void vertexAttrib4Nsv(Types::UInt index, const Types::Short* v) {
    return glVertexAttrib4Nsv(index, v) ;
}

inline Types::Void vertexAttrib4Niv(Types::UInt index, const Types::Int* v) {
    return glVertexAttrib4Niv(index, v) ;
}

inline Types::Void vertexAttrib4Nubv(Types::UInt index, const Types::UByte* v) {
    return glVertexAttrib4Nubv(index, v) ;
}

inline Types::Void vertexAttrib4Nusv(Types::UInt index, const Types::UShort* v) {
    return glVertexAttrib4Nusv(index, v) ;
}

inline Types::Void vertexAttrib4Nuiv(Types::UInt index, const Types::UInt* v) {
    return glVertexAttrib4Nuiv(index, v) ;
}

inline Types::Void vertexAttribI4bv(Types::UInt index, const Types::Byte* v) {
    return glVertexAttribI4bv(index, v) ;
}

inline Types::Void vertexAttribI4ubv(Types::UInt index, const Types::UByte* v) {
    return glVertexAttribI4ubv(index, v) ;
}

inline Types::Void vertexAttribI4sv(Types::UInt index, const Types::Short* v) {
    return glVertexAttribI4sv(index, v) ;
}

inline Types::Void vertexAttribI4usv(Types::UInt index, const Types::UShort* v) {
    return glVertexAttribI4usv(index, v) ;
}

inline Types::Void vertexAttribI4iv(Types::UInt index, const Types::Int* v) {
    return glVertexAttribI4iv(index, v) ;
}

inline Types::Void vertexAttribI4uiv(Types::UInt index, const Types::UInt* v) {
    return glVertexAttribI4uiv(index, v) ;
}

inline Types::Void vertexAttribP1ui(Types::UInt index, Types::Enum type, Types::Boolean normalized, Types::UInt value) {
    return glVertexAttribP1ui(index, type, normalized, value) ;
}

inline Types::Void vertexAttribP2ui(Types::UInt index, Types::Enum type, Types::Boolean normalized, Types::UInt value) {
    return glVertexAttribP2ui(index, type, normalized, value) ;
}

inline Types::Void vertexAttribP3ui(Types::UInt index, Types::Enum type, Types::Boolean normalized, Types::UInt value) {
    return glVertexAttribP3ui(index, type, normalized, value) ;
}

inline Types::Void vertexAttribP4ui(Types::UInt index, Types::Enum type, Types::Boolean normalized, Types::UInt value) {
    return glVertexAttribP4ui(index, type, normalized, value) ;
}

inline Types::Void vertexAttribDivisor(Types::UInt index, Types::UInt divisor) {
    return glVertexAttribDivisor(index, divisor) ;
}

inline Types::Void vertexAttribPointer(Types::UInt index, Types::Int size, Types::Enum type, Types::Boolean normalized, Types::Size stride, const Types::Void* pointer) {
    return glVertexAttribPointer(index, size, type, normalized, stride, pointer) ;
}

inline Types::Void vertexAttribIPointer(Types::UInt index, Types::Int size, Types::Enum type, Types::Size stride, const Types::Void* pointer) {
    return glVertexAttribIPointer(index, size, type, stride, pointer) ;
}

