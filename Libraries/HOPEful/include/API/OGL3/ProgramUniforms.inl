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

inline Types::Void getActiveUniform(Types::UInt program, Types::UInt index, Types::Size bufSize, Types::Size* length, Types::Int* size, Types::Enum* type, Types::Char* name) {
    return glGetActiveUniform(program, index, bufSize, length, size, type, name) ;
}

inline Types::Void getActiveUniformBlockiv(Types::UInt program, Types::UInt uniformBlockIndex, Types::Enum pname, Types::Int* params) {
    return glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params) ;
}

inline Types::Void getActiveUniformBlockName(Types::UInt program, Types::UInt uniformBlockIndex, Types::Size bufSize, Types::Size* length, Types::Char* uniformBlockName) {
    return glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName) ;
}

inline Types::Void getActiveUniformName(Types::UInt program, Types::UInt uniformIndex, Types::Size bufSize, Types::Size* length, Types::Char* uniformName) {
    return glGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName) ;
}

inline Types::Void getActiveUniformsiv(Types::UInt program, Types::Size uniformCount, const Types::UInt* uniformIndices, Types::Enum pname, Types::Int* params) {
    return glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params) ;
}

inline Types::Void getUniformfv(Types::UInt program, Types::Int location, Types::Float* params) {
    return glGetUniformfv(program, location, params) ;
}

inline Types::Void getUniformiv(Types::UInt program, Types::Int location, Types::Int* params) {
    return glGetUniformiv(program, location, params) ;
}

inline Types::Void getUniformuiv(Types::UInt program, Types::Int location, Types::UInt* params) {
    return glGetUniformuiv(program, location, params) ;
}

inline Types::UInt getUniformBlockIndex(Types::UInt program, const Types::Char* uniformBlockName) {
    return glGetUniformBlockIndex(program, uniformBlockName) ;
}

inline Types::Void getUniformIndices(Types::UInt program, Types::Size uniformCount, const Types::Char** uniformNames, Types::UInt* uniformIndices) {
    return glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices) ;
}

inline Types::Int getUniformLocation(Types::UInt program, const Types::Char* name) {
    return glGetUniformLocation(program, name) ;
}

inline Types::Void uniform1f(Types::Int location, Types::Float v0) {
    return glUniform1f(location, v0) ;
}

inline Types::Void uniform2f(Types::Int location, Types::Float v0, Types::Float v1) {
    return glUniform2f(location, v0, v1) ;
}

inline Types::Void uniform3f(Types::Int location, Types::Float v0, Types::Float v1, Types::Float v2) {
    return glUniform3f(location, v0, v1, v2) ;
}

inline Types::Void uniform4f(Types::Int location, Types::Float v0, Types::Float v1, Types::Float v2, Types::Float v3) {
    return glUniform4f(location, v0, v1, v2, v3) ;
}

inline Types::Void uniform1i(Types::Int location, Types::Int v0) {
    return glUniform1i(location, v0) ;
}

inline Types::Void uniform2i(Types::Int location, Types::Int v0, Types::Int v1) {
    return glUniform2i(location, v0, v1) ;
}

inline Types::Void uniform3i(Types::Int location, Types::Int v0, Types::Int v1, Types::Int v2) {
    return glUniform3i(location, v0, v1, v2) ;
}

inline Types::Void uniform4i(Types::Int location, Types::Int v0, Types::Int v1, Types::Int v2, Types::Int v3) {
    return glUniform4i(location, v0, v1, v2, v3) ;
}

inline Types::Void uniform1ui(Types::Int location, Types::UInt v0) {
    return glUniform1ui(location, v0) ;
}

inline Types::Void uniform2ui(Types::Int location, Types::UInt v0, Types::UInt v1) {
    return glUniform2ui(location, v0, v1) ;
}

inline Types::Void uniform3ui(Types::Int location, Types::UInt v0, Types::UInt v1, Types::UInt v2) {
    return glUniform3ui(location, v0, v1, v2) ;
}

inline Types::Void uniform4ui(Types::Int location, Types::UInt v0, Types::UInt v1, Types::UInt v2, Types::UInt v3) {
    return glUniform4ui(location, v0, v1, v2, v3) ;
}

inline Types::Void uniform1fv(Types::Int location, Types::Size count, const Types::Float* value) {
    return glUniform1fv(location, count, value) ;
}

inline Types::Void uniform2fv(Types::Int location, Types::Size count, const Types::Float* value) {
    return glUniform2fv(location, count, value) ;
}

inline Types::Void uniform3fv(Types::Int location, Types::Size count, const Types::Float* value) {
    return glUniform3fv(location, count, value) ;
}

inline Types::Void uniform4fv(Types::Int location, Types::Size count, const Types::Float* value) {
    return glUniform4fv(location, count, value) ;
}

inline Types::Void uniform1iv(Types::Int location, Types::Size count, const Types::Int* value) {
    return glUniform1iv(location, count, value) ;
}

inline Types::Void uniform2iv(Types::Int location, Types::Size count, const Types::Int* value) {
    return glUniform2iv(location, count, value) ;
}

inline Types::Void uniform3iv(Types::Int location, Types::Size count, const Types::Int* value) {
    return glUniform3iv(location, count, value) ;
}

inline Types::Void uniform4iv(Types::Int location, Types::Size count, const Types::Int* value) {
    return glUniform4iv(location, count, value) ;
}

inline Types::Void uniform1uiv(Types::Int location, Types::Size count, const Types::UInt* value) {
    return glUniform1uiv(location, count, value) ;
}

inline Types::Void uniform2uiv(Types::Int location, Types::Size count, const Types::UInt* value) {
    return glUniform2uiv(location, count, value) ;
}

inline Types::Void uniform3uiv(Types::Int location, Types::Size count, const Types::UInt* value) {
    return glUniform3uiv(location, count, value) ;
}

inline Types::Void uniform4uiv(Types::Int location, Types::Size count, const Types::UInt* value) {
    return glUniform4uiv(location, count, value) ;
}

inline Types::Void uniformMatrix2fv(Types::Int location, Types::Size count, Types::Boolean transpose, const Types::Float* value) {
    return glUniformMatrix2fv(location, count, transpose, value) ;
}

inline Types::Void uniformMatrix3fv(Types::Int location, Types::Size count, Types::Boolean transpose, const Types::Float* value) {
    return glUniformMatrix3fv(location, count, transpose, value) ;
}

inline Types::Void uniformMatrix4fv(Types::Int location, Types::Size count, Types::Boolean transpose, const Types::Float* value) {
    return glUniformMatrix4fv(location, count, transpose, value) ;
}

inline Types::Void uniformMatrix2x3fv(Types::Int location, Types::Size count, Types::Boolean transpose, const Types::Float* value) {
    return glUniformMatrix2x3fv(location, count, transpose, value) ;
}

inline Types::Void uniformMatrix3x2fv(Types::Int location, Types::Size count, Types::Boolean transpose, const Types::Float* value) {
    return glUniformMatrix3x2fv(location, count, transpose, value) ;
}

inline Types::Void uniformMatrix2x4fv(Types::Int location, Types::Size count, Types::Boolean transpose, const Types::Float* value) {
    return glUniformMatrix2x4fv(location, count, transpose, value) ;
}

inline Types::Void uniformMatrix4x2fv(Types::Int location, Types::Size count, Types::Boolean transpose, const Types::Float* value) {
    return glUniformMatrix4x2fv(location, count, transpose, value) ;
}

inline Types::Void uniformMatrix3x4fv(Types::Int location, Types::Size count, Types::Boolean transpose, const Types::Float* value) {
    return glUniformMatrix3x4fv(location, count, transpose, value) ;
}

inline Types::Void uniformMatrix4x3fv(Types::Int location, Types::Size count, Types::Boolean transpose, const Types::Float* value) {
    return glUniformMatrix4x3fv(location, count, transpose, value) ;
}

inline Types::Void uniformBlockBinding(Types::UInt program, Types::UInt uniformBlockIndex, Types::UInt uniformBlockBinding) {
    return glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding) ;
}

