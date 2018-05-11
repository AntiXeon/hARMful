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

inline Types::Void getBooleanv(Types::Enum pname, Types::Boolean* params) {
    return glGetBooleanv(pname, params) ;
}

inline Types::Void getDoublev(Types::Enum pname, Types::Double* params) {
    return glGetDoublev(pname, params) ;
}

inline Types::Void getFloatv(Types::Enum pname, Types::Float* params) {
    return glGetFloatv(pname, params) ;
}

inline Types::Void getIntegerv(Types::Enum pname, Types::Int* params) {
    return glGetIntegerv(pname, params) ;
}

inline Types::Void getInteger64v(Types::Enum pname, Types::Int64* params) {
    return glGetInteger64v(pname, params) ;
}

inline Types::Void getBooleani_v(Types::Enum pname, Types::UInt index, Types::Boolean* data) {
    return glGetBooleani_v(pname, index, data) ;
}

inline Types::Void getIntegeri_v(Types::Enum pname, Types::UInt index, Types::Int* data) {
    return glGetIntegeri_v(pname, index, data) ;
}

inline Types::Void getInteger64i_v(Types::Enum pname, Types::UInt index, Types::Int64* data) {
    return glGetInteger64i_v(pname, index, data) ;
}

inline const Types::UByte* getString(Types::Enum name) {
    return glGetString(name) ;
}

inline const Types::UByte* getStringi(Types::Enum name, Types::UInt index) {
    return glGetStringi(name, index) ;
}

