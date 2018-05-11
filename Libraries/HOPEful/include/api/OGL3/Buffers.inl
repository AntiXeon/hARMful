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

inline Types::Void genBuffers(Types::Size n, Types::UInt* buffers) {
    return glGenBuffers(n, buffers) ;
}

inline Types::Void deleteBuffers(Types::Size n, const Types::UInt* buffers) {
    return glDeleteBuffers(n, buffers) ;
}

inline Types::Void bufferData(Types::Enum target, Types::SizePtr size, const Types::Void* data, Types::Enum usage) {
    return glBufferData(target, size, data, usage) ;
}

inline Types::Void bufferSubData(Types::Enum target, Types::IntPtr offset, Types::SizePtr size, const Types::Void* data) {
    return glBufferSubData(target, offset, size, data) ;
}

inline Types::Void bindBuffer(Types::Enum target, Types::UInt buffer) {
    return glBindBuffer(target, buffer) ;
}

inline Types::Void bindBufferBase(Types::Enum target, Types::UInt index, Types::UInt buffer) {
    return glBindBufferBase(target, index, buffer) ;
}

inline Types::Void bindBufferRange(Types::Enum target, Types::UInt index, Types::UInt buffer, Types::IntPtr offset, Types::SizePtr size) {
    return glBindBufferRange(target, index, buffer, offset, size) ;
}

inline Types::Void drawBuffer(Types::Enum mode) {
    return glDrawBuffer(mode) ;
}

inline Types::Void drawBuffers(Types::Size n, const Types::Enum* bufs) {
    return glDrawBuffers(n, bufs) ;
}

inline Types::Void readBuffer(Types::Enum mode) {
    return glReadBuffer(mode) ;
}

inline Types::Void getBufferParameteriv(Types::Enum target, Types::Enum value, Types::Int* data) {
    return glGetBufferParameteriv(target, value, data) ;
}

inline Types::Void getBufferParameteri64v(Types::Enum target, Types::Enum value, Types::Int64* data) {
    return glGetBufferParameteri64v(target, value, data) ;
}

inline Types::Void getBufferPointerv(Types::Enum target, Types::Enum pname, Types::Void** params) {
    return glGetBufferPointerv(target, pname, params) ;
}

inline Types::Void getBufferSubData(Types::Enum target, Types::IntPtr offset, Types::SizePtr size, Types::Void* data) {
    return glGetBufferSubData(target, offset, size, data) ;
}

inline Types::Void copyBufferSubData(Types::Enum readtarget, Types::Enum writetarget, Types::IntPtr readoffset, Types::IntPtr writeoffset, Types::SizePtr size) {
    return glCopyBufferSubData(readtarget, writetarget, readoffset, writeoffset, size) ;
}

inline Types::Void clearBufferiv(Types::Enum buffer, Types::Int drawBuffer, const Types::Int* value) {
    return glClearBufferiv(buffer, drawBuffer, value) ;
}

inline Types::Void clearBufferuiv(Types::Enum buffer, Types::Int drawBuffer, const Types::UInt* value) {
    return glClearBufferuiv(buffer, drawBuffer, value) ;
}

inline Types::Void clearBufferfv(Types::Enum buffer, Types::Int drawBuffer, const Types::Float* value) {
    return glClearBufferfv(buffer, drawBuffer, value) ;
}

inline Types::Void clearBufferfi(Types::Enum buffer, Types::Int drawBuffer, Types::Float depth, Types::Int stencil) {
    return glClearBufferfi(buffer, drawBuffer, depth, stencil) ;
}

inline Types::Boolean isBuffer(Types::UInt buffer) {
    return glIsBuffer(buffer) ;
}

inline Types::Void* mapBuffer(Types::Enum target, Types::Enum access) {
    return glMapBuffer(target, access) ;
}

inline Types::Void* mapBufferRange(Types::Enum target, Types::IntPtr offset, Types::SizePtr length, Types::BitField access) {
    return glMapBufferRange(target, offset, length, access) ;
}

inline Types::Boolean unmapBuffer(Types::Enum target) {
    return glUnmapBuffer(target) ;
}

inline Types::Void flushMappedBufferRange(Types::Enum target, Types::IntPtr offset, Types::SizePtr length) {
    return glFlushMappedBufferRange(target, offset, length) ;
}

