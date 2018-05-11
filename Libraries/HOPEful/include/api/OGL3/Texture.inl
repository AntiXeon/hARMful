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

inline Types::Void genTextures(Types::Size n, Types::UInt* textures) {
    return glGenTextures(n, textures) ;
}

inline Types::Void deleteTextures(Types::Size n, const Types::UInt* textures) {
    return glDeleteTextures(n, textures) ;
}

inline Types::Void activeTexture(Types::Enum texture) {
    return glActiveTexture(texture) ;
}

inline Types::Void bindTexture(Types::Enum target, Types::UInt texture) {
    return glBindTexture(target, texture) ;
}

inline Types::Void generateMipmap(Types::Enum target) {
    return glGenerateMipmap(target) ;
}

inline Types::Void getCompressedTexImage(Types::Enum target, Types::Int lod, Types::Void* img) {
    return glGetCompressedTexImage(target, lod, img) ;
}

inline Types::Void texBuffer(Types::Enum target, Types::Enum internalFormat, Types::UInt buffer) {
    return glTexBuffer(target, internalFormat, buffer) ;
}

inline Types::Void texImage1D(Types::Enum target, Types::Int level, Types::Int internalFormat, Types::Size width, Types::Int border, Types::Enum format, Types::Enum type, const Types::Void* data) {
    return glTexImage1D(target, level, internalFormat, width, border, format, type, data) ;
}

inline Types::Void texImage2D(Types::Enum target, Types::Int level, Types::Int internalFormat, Types::Size width, Types::Size height, Types::Int border, Types::Enum format, Types::Enum type, const Types::Void* data) {
    return glTexImage2D(target, level, internalFormat, width, height, border, format, type, data) ;
}

inline Types::Void texImage2DMultisample(Types::Enum target, Types::Size samples, Types::Int internalformat, Types::Size width, Types::Size height, Types::Boolean fixedsamplelocations) {
    return glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations) ;
}

inline Types::Void texImage3D(Types::Enum target, Types::Int level, Types::Int internalFormat, Types::Size width, Types::Size height, Types::Size depth, Types::Int border, Types::Enum format, Types::Enum type, const Types::Void* data) {
    return glTexImage3D(target, level, internalFormat, width, height, depth, border, format, type, data) ;
}

inline Types::Void texImage3DMultisample(Types::Enum target, Types::Size samples, Types::Int internalformat, Types::Size width, Types::Size height, Types::Size depth, Types::Boolean fixedsamplelocations) {
    return glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations) ;
}

inline Types::Void texParameterf(Types::Enum target, Types::Enum pname, Types::Float param) {
    return glTexParameterf(target, pname, param) ;
}

inline Types::Void texParameteri(Types::Enum target, Types::Enum pname, Types::Int param) {
    return glTexParameteri(target, pname, param) ;
}

inline Types::Void texParameterfv(Types::Enum target, Types::Enum pname, const Types::Float* params) {
    return glTexParameterfv(target, pname, params) ;
}

inline Types::Void texParameteriv(Types::Enum target, Types::Enum pname, const Types::Int* params) {
    return glTexParameteriv(target, pname, params) ;
}

inline Types::Void texParameterIiv(Types::Enum target, Types::Enum pname, const Types::Int* params) {
    return glTexParameterIiv(target, pname, params) ;
}

inline Types::Void texParameterIuiv(Types::Enum target, Types::Enum pname, const Types::UInt* params) {
    return glTexParameterIuiv(target, pname, params) ;
}

inline Types::Void texSubImage1D(Types::Enum target, Types::Int level, Types::Int xoffset, Types::Size width, Types::Enum format, Types::Enum type, const Types::Void* data) {
    return glTexSubImage1D(target, level, xoffset, width, format, type, data) ;
}

inline Types::Void texSubImage2D(Types::Enum target, Types::Int level, Types::Int xoffset, Types::Int yoffset, Types::Size width, Types::Size height, Types::Enum format, Types::Enum type, const Types::Void* data) {
    return glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, data) ;
}

inline Types::Void texSubImage3D(Types::Enum target, Types::Int level, Types::Int xoffset, Types::Int yoffset, Types::Int zoffset, Types::Size width, Types::Size height, Types::Size depth, Types::Enum format, Types::Enum type, const Types::Void* data) {
    return glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data) ;
}

inline Types::Void getTexImage(Types::Enum target, Types::Int level, Types::Enum format, Types::Enum type, Types::Void* img) {
    return glGetTexImage(target, level, format, type, img) ;
}

inline Types::Void getTexLevelParameterfv(Types::Enum target, Types::Int level, Types::Enum pname, Types::Float* params) {
    return glGetTexLevelParameterfv(target, level, pname, params) ;
}

inline Types::Void getTexLevelParameteriv(Types::Enum target, Types::Int level, Types::Enum pname, Types::Int* params) {
    return glGetTexLevelParameteriv(target, level, pname, params) ;
}

inline Types::Void getTexParameterfv(Types::Enum target, Types::Enum pname, Types::Float* params) {
    return glGetTexParameterfv(target, pname, params) ;
}

inline Types::Void getTexParameteriv(Types::Enum target, Types::Enum pname, Types::Int* params) {
    return glGetTexParameteriv(target, pname, params) ;
}

inline Types::Void getTexParameterIiv(Types::Enum target, Types::Enum pname, Types::Int* params) {
    return glGetTexParameterIiv(target, pname, params) ;
}

inline Types::Void getTexParameterIuiv(Types::Enum target, Types::Enum pname, Types::UInt* params) {
    return glGetTexParameterIuiv(target, pname, params) ;
}

inline Types::Void compressedTexImage1D(Types::Enum target, Types::Int level, Types::Enum internalformat, Types::Size width, Types::Int border, Types::Size imageSize, const Types::Void* data) {
    return glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data) ;
}

inline Types::Void compressedTexImage2D(Types::Enum target, Types::Int level, Types::Enum internalformat, Types::Size width, Types::Size height, Types::Int border, Types::Size imageSize, const Types::Void* data) {
    return glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data) ;
}

inline Types::Void compressedTexImage3D(Types::Enum target, Types::Int level, Types::Enum internalformat, Types::Size width, Types::Size height, Types::Size depth, Types::Int border, Types::Size imageSize, const Types::Void* data) {
    return glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data) ;
}

inline Types::Void compressedTexSubImage1D(Types::Enum target, Types::Int level, Types::Int xoffset, Types::Size width, Types::Enum format, Types::Size imageSize, const Types::Void* data) {
    return glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data) ;
}

inline Types::Void compressedTexSubImage2D(Types::Enum target, Types::Int level, Types::Int xoffset, Types::Int yoffset, Types::Size width, Types::Size height, Types::Enum format, Types::Size imageSize, const Types::Void* data) {
    return glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data) ;
}

inline Types::Void compressedTexSubImage3D(Types::Enum target, Types::Int level, Types::Int xoffset, Types::Int yoffset, Types::Int zoffset, Types::Size width, Types::Size height, Types::Size depth, Types::Enum format, Types::Size imageSize, const Types::Void* data) {
    return glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data) ;
}

inline Types::Void copyTexImage1D(Types::Enum target, Types::Int level, Types::Enum internalformat, Types::Int x, Types::Int y, Types::Size width, Types::Int border) {
    return glCopyTexImage1D(target, level, internalformat, x, y, width, border) ;
}

inline Types::Void copyTexImage2D(Types::Enum target, Types::Int level, Types::Enum internalformat, Types::Int x, Types::Int y, Types::Size width, Types::Size height, Types::Int border) {
    return glCopyTexImage2D(target, level, internalformat, x, y, width, height, border) ;
}

inline Types::Void copyTexSubImage1D(Types::Enum target, Types::Int level, Types::Int xoffset, Types::Int x, Types::Int y, Types::Size width) {
    return glCopyTexSubImage1D(target, level, xoffset, x, y, width) ;
}

inline Types::Void copyTexSubImage2D(Types::Enum target, Types::Int level, Types::Int xoffset, Types::Int yoffset, Types::Int x, Types::Int y, Types::Size width, Types::Size height) {
    return glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height) ;
}

inline Types::Void copyTexSubImage3D(Types::Enum target, Types::Int level, Types::Int xoffset, Types::Int yoffset, Types::Int zoffset, Types::Int x, Types::Int y, Types::Size width, Types::Size height) {
    return glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height) ;
}

inline Types::Boolean isTexture(Types::UInt texture) {
    return glIsTexture(texture) ;
}

