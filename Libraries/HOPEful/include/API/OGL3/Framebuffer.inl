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

inline Types::Void genFramebuffers(Types::Size n, Types::UInt* ids) {
    return glGenFramebuffers(n, ids) ;
}

inline Types::Void deleteFramebuffers(Types::Size n, Types::UInt* framebuffers) {
    return glDeleteFramebuffers(n, framebuffers) ;
}

inline Types::Void bindFramebuffer(Types::Enum target, Types::UInt framebuffer) {
    return glBindFramebuffer(target, framebuffer) ;
}

inline Types::Void blitFramebuffer(Types::Int srcX0, Types::Int srcY0, Types::Int srcX1, Types::Int srcY1, Types::Int dstX0, Types::Int dstY0, Types::Int dstX1, Types::Int dstY1, Types::BitField mask, Types::Enum filter) {
    return glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter) ;
}

inline Types::Void getFramebufferAttachmentParameteriv(Types::Enum target, Types::Enum attachment, Types::Enum pname, Types::Int* params) {
    return glGetFramebufferAttachmentParameteriv(target, attachment, pname, params) ;
}

inline Types::Void framebufferRenderbuffer(Types::Enum target, Types::Enum attachment, Types::Enum renderbuffertarget, Types::UInt renderbuffer) {
    return glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer) ;
}

inline Types::Void framebufferTexture(Types::Enum target, Types::Enum attachment, Types::UInt texture, Types::Int level) {
    return glFramebufferTexture(target, attachment, texture, level) ;
}

inline Types::Void framebufferTexture1D(Types::Enum target, Types::Enum attachment, Types::Enum textarget, Types::UInt texture, Types::Int level) {
    return glFramebufferTexture1D(target, attachment, textarget, texture, level) ;
}

inline Types::Void framebufferTexture2D(Types::Enum target, Types::Enum attachment, Types::Enum textarget, Types::UInt texture, Types::Int level) {
    return glFramebufferTexture2D(target, attachment, textarget, texture, level) ;
}

inline Types::Void framebufferTexture3D(Types::Enum target, Types::Enum attachment, Types::Enum textarget, Types::UInt texture, Types::Int level, Types::Int layer) {
    return glFramebufferTexture3D(target, attachment, textarget, texture, level, layer) ;
}

inline Types::Void framebufferTextureLayer(Types::Enum target, Types::Enum attachment, Types::UInt texture, Types::Int level, Types::Int layer) {
    return glFramebufferTextureLayer(target, attachment, texture, level, layer) ;
}

inline Types::Enum checkFramebufferStatus(Types::Enum target) {
    return glCheckFramebufferStatus(target) ;
}

inline Types::Boolean isFramebuffer(Types::UInt framebuffer) {
    return glIsFramebuffer(framebuffer) ;
}

