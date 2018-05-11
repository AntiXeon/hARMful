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

inline Types::Void genRenderbuffers(Types::Size n, Types::UInt* renderbuffers) {
    return glGenRenderbuffers(n, renderbuffers) ;
}

inline Types::Void deleteRenderbuffers(Types::Size n, Types::UInt* renderbuffers) {
    return glDeleteRenderbuffers(n, renderbuffers) ;
}

inline Types::Void bindRenderbuffer(Types::Enum target, Types::UInt renderbuffer) {
    return glBindRenderbuffer(target, renderbuffer) ;
}

inline Types::Void getRenderbufferParameteriv(Types::Enum target, Types::Enum pname, Types::Int* params) {
    return glGetRenderbufferParameteriv(target, pname, params) ;
}

inline Types::Void renderbufferStorage(Types::Enum target, Types::Enum internalformat, Types::Size width, Types::Size height) {
    return glRenderbufferStorage(target, internalformat, width, height) ;
}

inline Types::Void renderbufferStorageMultisample(Types::Enum target, Types::Size samples, Types::Enum internalformat, Types::Size width, Types::Size height) {
    return glRenderbufferStorageMultisample(target, samples, internalformat, width, height) ;
}

inline Types::Boolean isRenderbuffer(Types::UInt renderbuffer) {
    return glIsRenderbuffer(renderbuffer) ;
}

