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

inline Types::UInt createShader(Types::Enum shaderType) {
    return glCreateShader(shaderType) ;
}

inline Types::Void deleteShader(Types::UInt shader) {
    return glDeleteShader(shader) ;
}

inline Types::Void shaderSource(Types::UInt shader, Types::Size count, const Types::Char** string, const Types::Int* length) {
    return glShaderSource(shader, count, string, length) ;
}

inline Types::Void compileShader(Types::UInt shader) {
    return glCompileShader(shader) ;
}

inline Types::Void attachShader(Types::UInt program, Types::UInt shader) {
    return glAttachShader(program, shader) ;
}

inline Types::Void detachShader(Types::UInt program, Types::UInt shader) {
    return glDetachShader(program, shader) ;
}

inline Types::Void getAttachedShaders(Types::UInt program, Types::Size maxCount, Types::Size* count, Types::UInt* shaders) {
    return glGetAttachedShaders(program, maxCount, count, shaders) ;
}

inline Types::Void getShaderiv(Types::UInt shader, Types::Enum pname, Types::Int* params) {
    return glGetShaderiv(shader, pname, params) ;
}

inline Types::Void getShaderInfoLog(Types::UInt shader, Types::Size maxLength, Types::Size* length, Types::Char* infoLog) {
    return glGetShaderInfoLog(shader, maxLength, length, infoLog) ;
}

inline Types::Void getShaderSource(Types::UInt shader, Types::Size bufSize, Types::Size* length, Types::Char* source) {
    return glGetShaderSource(shader, bufSize, length, source) ;
}

inline Types::Boolean isShader(Types::UInt shader) {
    return glIsShader(shader) ;
}

