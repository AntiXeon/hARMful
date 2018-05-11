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

inline Types::Void blendColor(Types::Clampf red, Types::Clampf green, Types::Clampf blue, Types::Clampf alpha) {
    return glBlendColor(red, green, blue, alpha) ;
}

inline Types::Void blendEquation(Types::Enum mode) {
    return glBlendEquation(mode) ;
}

inline Types::Void blendEquationSeparate(Types::Enum modeRGB, Types::Enum modeAlpha) {
    return glBlendEquationSeparate(modeRGB, modeAlpha) ;
}

inline Types::Void blendFunc(Types::Enum sfactor, Types::Enum dfactor) {
    return glBlendFunc(sfactor, dfactor) ;
}

inline Types::Void blendFuncSeparate(Types::Enum srcRGB, Types::Enum dstRGB, Types::Enum srcAlpha, Types::Enum dstAlpha) {
    return glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha) ;
}

inline Types::Void pointParameterf(Types::Enum pname, Types::Float param) {
    return glPointParameterf(pname, param) ;
}

inline Types::Void pointParameteri(Types::Enum pname, Types::Int param) {
    return glPointParameteri(pname, param) ;
}

inline Types::Void pointParameterfv(Types::Enum pname, const Types::Float* params) {
    return glPointParameterfv(pname, params) ;
}

inline Types::Void pointParameteriv(Types::Enum pname, const Types::Int* params) {
    return glPointParameteriv(pname, params) ;
}

inline Types::Void clear(Types::BitField mask) {
    return glClear(mask) ;
}

inline Types::Void clearColor(Types::Clampf red, Types::Clampf green, Types::Clampf blue, Types::Clampf alpha) {
    return glClearColor(red, green, blue, alpha) ;
}

inline Types::Void clearDepth(Types::Clampd depth) {
    return glClearDepth(depth) ;
}

inline Types::Void clearStencil(Types::Int s) {
    return glClearStencil(s) ;
}

inline Types::Void clampColor(Types::Enum target, Types::Enum clamp) {
    return glClampColor(target, clamp) ;
}

inline Types::Void colorMask(Types::Boolean red, Types::Boolean green, Types::Boolean blue, Types::Boolean alpha) {
    return glColorMask(red, green, blue, alpha) ;
}

inline Types::Void colorMaski(Types::UInt buf, Types::Boolean red, Types::Boolean green, Types::Boolean blue, Types::Boolean alpha) {
    return glColorMaski(buf, red, green, blue, alpha) ;
}

inline Types::Void frontFace(Types::Enum mode) {
    return glFrontFace(mode) ;
}

inline Types::Void cullFace(Types::Enum mode) {
    return glCullFace(mode) ;
}

inline Types::Void depthFunc(Types::Enum func) {
    return glDepthFunc(func) ;
}

inline Types::Void depthMask(Types::Boolean flag) {
    return glDepthMask(flag) ;
}

inline Types::Void depthRange(Types::Clampd nearVal, Types::Clampd farVal) {
    return glDepthRange(nearVal, farVal) ;
}

inline Types::Void disable(Types::Enum cap) {
    return glDisable(cap) ;
}

inline Types::Void disablei(Types::Enum cap, Types::UInt index) {
    return glDisablei(cap, index) ;
}

inline Types::Void enable(Types::Enum cap) {
    return glEnable(cap) ;
}

inline Types::Void enablei(Types::Enum cap, Types::UInt index) {
    return glEnablei(cap, index) ;
}

inline Types::Void pointSize(Types::Float size) {
    return glPointSize(size) ;
}

inline Types::Void polygonMode(Types::Enum face, Types::Enum mode) {
    return glPolygonMode(face, mode) ;
}

inline Types::Void polygonOffset(Types::Float factor, Types::Float units) {
    return glPolygonOffset(factor, units) ;
}

inline Types::Void lineWidth(Types::Float width) {
    return glLineWidth(width) ;
}

inline Types::Void scissor(Types::Int x, Types::Int y, Types::Size width, Types::Size height) {
    return glScissor(x, y, width, height) ;
}

inline Types::Void stencilFunc(Types::Enum func, Types::Int ref, Types::UInt mask) {
    return glStencilFunc(func, ref, mask) ;
}

inline Types::Void stencilFuncSeparate(Types::Enum face, Types::Enum func, Types::Int ref, Types::UInt mask) {
    return glStencilFuncSeparate(face, func, ref, mask) ;
}

inline Types::Void stencilMask(Types::UInt mask) {
    return glStencilMask(mask) ;
}

inline Types::Void stencilMaskSeparate(Types::Enum face, Types::UInt mask) {
    return glStencilMaskSeparate(face, mask) ;
}

inline Types::Void logicOp(Types::Enum opcode) {
    return glLogicOp(opcode) ;
}

inline Types::Void stencilOp(Types::Enum sfail, Types::Enum dpfail, Types::Enum dppass) {
    return glStencilOp(sfail, dpfail, dppass) ;
}

inline Types::Void stencilOpSeparate(Types::Enum face, Types::Enum sfail, Types::Enum dpfail, Types::Enum dppass) {
    return glStencilOpSeparate(face, sfail, dpfail, dppass) ;
}

inline Types::Void viewport(Types::Int x, Types::Int y, Types::Size width, Types::Size height) {
    return glViewport(x, y, width, height) ;
}

inline Types::Void finish() {
    return glFinish() ;
}

inline Types::Void flush() {
    return glFlush() ;
}

inline Types::Boolean isEnabled(Types::Enum cap) {
    return glIsEnabled(cap) ;
}

inline Types::Boolean isEnabledi(Types::Enum cap, Types::UInt index) {
    return glIsEnabledi(cap, index) ;
}

