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

inline Types::Enum clientWaitSync(Types::Sync sync, Types::BitField flags, Types::UInt64 timeout) {
    return glClientWaitSync(sync, flags, timeout) ;
}

inline Types::Void deleteSync(Types::Sync sync) {
    return glDeleteSync(sync) ;
}

inline Types::Sync fenceSync(Types::Enum condition, Types::BitField flags) {
    return glFenceSync(condition, flags) ;
}

inline Types::Void getSynciv(Types::Sync sync, Types::Enum pname, Types::Size bufSize, Types::Size* length, Types::Int* values) {
    return glGetSynciv(sync, pname, bufSize, length, values) ;
}

inline Types::Void waitSync(Types::Sync sync, Types::BitField flags, Types::UInt64 timeout) {
    return glWaitSync(sync, flags, timeout) ;
}

inline Types::Boolean isSync(Types::Sync sync) {
    return glIsSync(sync) ;
}

