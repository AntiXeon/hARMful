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

inline Types::UInt createProgram() {
    return glCreateProgram() ;
}

inline Types::Void deleteProgram(Types::UInt program) {
    return glDeleteProgram(program) ;
}

inline Types::Void validateProgram(Types::UInt program) {
    return glValidateProgram(program) ;
}

inline Types::Void linkProgram(Types::UInt program) {
    return glLinkProgram(program) ;
}

inline Types::Void useProgram(Types::UInt program) {
    return glUseProgram(program) ;
}

inline Types::Void getProgramiv(Types::UInt program, Types::Enum pname, Types::Int* params) {
    return glGetProgramiv(program, pname, params) ;
}

inline Types::Void getProgramInfoLog(Types::UInt program, Types::Size maxLength, Types::Size* length, Types::Char* infoLog) {
    return glGetProgramInfoLog(program, maxLength, length, infoLog) ;
}

inline Types::Boolean isProgram(Types::UInt program) {
    return glIsProgram(program) ;
}

