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

inline Types::Void genSamplers(Types::Size n, Types::UInt* samplers) {
    return glGenSamplers(n, samplers) ;
}

inline Types::Void deleteSamplers(Types::Size n, const Types::UInt* samplers) {
    return glDeleteSamplers(n, samplers) ;
}

inline Types::Void bindSampler(Types::UInt unit, Types::UInt sampler) {
    return glBindSampler(unit, sampler) ;
}

inline Types::Void samplerParameterf(Types::UInt sampler, Types::Enum pname, Types::Float param) {
    return glSamplerParameterf(sampler, pname, param) ;
}

inline Types::Void samplerParameteri(Types::UInt sampler, Types::Enum pname, Types::Int param) {
    return glSamplerParameteri(sampler, pname, param) ;
}

inline Types::Void samplerParameterfv(Types::UInt sampler, Types::Enum pname, const Types::Float* params) {
    return glSamplerParameterfv(sampler, pname, params) ;
}

inline Types::Void samplerParameteriv(Types::UInt sampler, Types::Enum pname, const Types::Int* params) {
    return glSamplerParameteriv(sampler, pname, params) ;
}

inline Types::Void samplerParameterIiv(Types::UInt sampler, Types::Enum pname, const Types::Int* params) {
    return glSamplerParameterIiv(sampler, pname, params) ;
}

inline Types::Void samplerParameterIuiv(Types::UInt sampler, Types::Enum pname, const Types::UInt* params) {
    return glSamplerParameterIuiv(sampler, pname, params) ;
}

inline Types::Void getSamplerParameterfv(Types::UInt sampler, Types::Enum pname, Types::Float* params) {
    return glGetSamplerParameterfv(sampler, pname, params) ;
}

inline Types::Void getSamplerParameteriv(Types::UInt sampler, Types::Enum pname, Types::Int* params) {
    return glGetSamplerParameteriv(sampler, pname, params) ;
}

inline Types::Void getSamplerParameterIiv(Types::UInt sampler, Types::Enum pname, Types::Int* params) {
    return glGetSamplerParameterIiv(sampler, pname, params) ;
}

inline Types::Void getSamplerParameterIuiv(Types::UInt sampler, Types::Enum pname, Types::UInt* params) {
    return glGetSamplerParameterIuiv(sampler, pname, params) ;
}

inline Types::Boolean isSampler(Types::UInt id) {
    return glIsSampler(id) ;
}

