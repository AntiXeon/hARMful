// This file is part of hARMful.
//
// hARMful is free software: you can redistribute
// it and/or modify it under the terms of the GNU
// General  Public License  as published  by  the
// Free Software Foundation,  either version 3 of
// the  License,  or (at your option)  any  later
// version.
//
// hARMful is  distributed in  the hope  that  it
// will  be  useful, but  WITHOUT  ANY  WARRANTY;
// without   even   the   implied   warranty   of
// MERCHANTABILITY  or  FITNESS FOR  A PARTICULAR
// PURPOSE.  See the  GNU General  Public License
// for more details.
//
// You  should have  received a  copy of  the GNU
// General  Public  License  along  with hARMful.
// If not, see <http://www.gnu.org/licenses/>.

static map<string, string> typesConversion ;

static void initTypesConversion() {
    typesConversion["GLboolean"]       = "Boolean" ;
    typesConversion["GLbyte"]          = "Byte" ;
    typesConversion["GLubyte"]         = "UByte" ;
    typesConversion["GLchar"]          = "Char" ;
    typesConversion["GLshort"]         = "Short" ;
    typesConversion["GLushort"]        = "UShort" ;
    typesConversion["GLint"]           = "Int" ;
    typesConversion["GLuint"]          = "UInt" ;
    typesConversion["GLfixed"]         = "Fixed" ;
    typesConversion["GLint64"]         = "Int64" ;
    typesConversion["GLuint64"]        = "UInt64" ;
    typesConversion["GLfloat"]         = "Float" ;
    typesConversion["GLdouble"]        = "Double" ;
    typesConversion["GLhalf"]          = "Half" ;
    typesConversion["GLclampf"]        = "Clampf" ;
    typesConversion["GLclampd"]        = "Clampd" ;
    typesConversion["GLsizei"]         = "Size" ;
    typesConversion["GLenum"]          = "Enum" ;
    typesConversion["GLvoid"]          = "Void" ;
    typesConversion["void"]            = "Void" ;
    typesConversion["GLintptr"]        = "IntPtr" ;
    typesConversion["GLintptrARB"]     = "IntPtrARB" ;
    typesConversion["GLsizeiptr"]      = "SizePtr" ;
    typesConversion["GLsizeiptrARB"]   = "SizePtrARB" ;
    typesConversion["GLsync"]          = "Sync" ;
    typesConversion["GLbitfield"]      = "BitField" ;

    typesConversion["const GLboolean"]       = "const Boolean" ;
    typesConversion["const GLbyte"]          = "const Byte" ;
    typesConversion["const GLubyte"]         = "const UByte" ;
    typesConversion["const GLchar"]          = "const Char" ;
    typesConversion["const GLshort"]         = "const Short" ;
    typesConversion["const GLushort"]        = "const UShort" ;
    typesConversion["const GLint"]           = "const Int" ;
    typesConversion["const GLuint"]          = "const UInt" ;
    typesConversion["const GLfixed"]         = "const Fixed" ;
    typesConversion["const GLint64"]         = "const Int64" ;
    typesConversion["const GLuint64"]        = "const UInt64" ;
    typesConversion["const GLfloat"]         = "const Float" ;
    typesConversion["const GLdouble"]        = "const Double" ;
    typesConversion["const GLhalf"]          = "const Half" ;
    typesConversion["const GLclampf"]        = "const Clampf" ;
    typesConversion["const GLclampd"]        = "const Clampd" ;
    typesConversion["const GLsizei"]         = "const Size" ;
    typesConversion["const GLenum"]          = "const Enum" ;
    typesConversion["const GLvoid"]          = "const Void" ;
    typesConversion["const void"]            = "const Void" ;
    typesConversion["const GLintptr"]        = "const IntPtr" ;
    typesConversion["const GLintptrARB"]     = "const IntPtrARB" ;
    typesConversion["const GLsizeiptr"]      = "const SizePtr" ;
    typesConversion["const GLsizeiptrARB"]   = "const SizePtrARB" ;
    typesConversion["const GLsync"]          = "const Sync" ;
    typesConversion["const GLbitfield"]      = "const BitField" ;


    typesConversion["GLboolean*"]       = "Boolean*" ;
    typesConversion["GLbyte*"]          = "Byte*" ;
    typesConversion["GLubyte*"]         = "UByte*" ;
    typesConversion["GLchar*"]          = "Char*" ;
    typesConversion["char*"]            = "Char*" ;
    typesConversion["GLshort*"]         = "Short*" ;
    typesConversion["GLushort*"]        = "UShort*" ;
    typesConversion["GLint*"]           = "Int*" ;
    typesConversion["GLuint*"]          = "UInt*" ;
    typesConversion["GLfixed*"]         = "Fixed*" ;
    typesConversion["GLint64*"]         = "Int64*" ;
    typesConversion["GLuint64*"]        = "UInt64*" ;
    typesConversion["GLfloat*"]         = "Float*" ;
    typesConversion["GLdouble*"]        = "Double*" ;
    typesConversion["GLhalf*"]          = "Half*" ;
    typesConversion["GLclampf*"]        = "Clampf*" ;
    typesConversion["GLclampd*"]        = "Clampd*" ;
    typesConversion["GLsizei*"]         = "Size*" ;
    typesConversion["GLenum*"]          = "Enum*" ;
    typesConversion["GLvoid*"]          = "Void*" ;
    typesConversion["void*"]            = "Void*" ;
    typesConversion["GLintptr*"]        = "IntPtr*" ;
    typesConversion["GLintptrARB*"]     = "IntPtrARB*" ;
    typesConversion["GLsizeiptr*"]      = "SizePtr*" ;
    typesConversion["GLsizeiptrARB*"]   = "SizePtrARB*" ;
    typesConversion["GLsync*"]          = "Sync*" ;
    typesConversion["GLbitfield*"]      = "BitField*" ;

    typesConversion["const GLboolean*"]       = "const Boolean*" ;
    typesConversion["const GLbyte*"]          = "const Byte*" ;
    typesConversion["const GLubyte*"]         = "const UByte*" ;
    typesConversion["const GLchar*"]          = "const Char*" ;
    typesConversion["const char*"]            = "const Char*" ;
    typesConversion["const GLshort*"]         = "const Short*" ;
    typesConversion["const GLushort*"]        = "const UShort*" ;
    typesConversion["const GLint*"]           = "const Int*" ;
    typesConversion["const GLuint*"]          = "const UInt*" ;
    typesConversion["const GLfixed*"]         = "const Fixed*" ;
    typesConversion["const GLint64*"]         = "const Int64*" ;
    typesConversion["const GLuint64*"]        = "const UInt64*" ;
    typesConversion["const GLfloat*"]         = "const Float*" ;
    typesConversion["const GLdouble*"]        = "const Double*" ;
    typesConversion["const GLhalf*"]          = "const Half*" ;
    typesConversion["const GLclampf*"]        = "const Clampf*" ;
    typesConversion["const GLclampd*"]        = "const Clampd*" ;
    typesConversion["const GLsizei*"]         = "const Size*" ;
    typesConversion["const GLenum*"]          = "const Enum*" ;
    typesConversion["const GLvoid*"]          = "const Void*" ;
    typesConversion["const void*"]            = "const Void*" ;
    typesConversion["const GLintptr*"]        = "const IntPtr*" ;
    typesConversion["const GLintptrARB*"]     = "const IntPtrARB*" ;
    typesConversion["const GLsizeiptr*"]      = "const SizePtr*" ;
    typesConversion["const GLsizeiptrARB*"]   = "const SizePtrARB*" ;
    typesConversion["const GLsync*"]          = "const Sync*" ;
    typesConversion["const GLbitfield*"]      = "const BitField*" ;

    typesConversion["GLboolean**"]       = "Boolean**" ;
    typesConversion["GLbyte**"]          = "Byte**" ;
    typesConversion["GLubyte**"]         = "UByte**" ;
    typesConversion["GLchar**"]          = "Char**" ;
    typesConversion["char**"]            = "Char**" ;
    typesConversion["GLshort**"]         = "Short**" ;
    typesConversion["GLushort**"]        = "UShort**" ;
    typesConversion["GLint**"]           = "Int**" ;
    typesConversion["GLuint**"]          = "UInt**" ;
    typesConversion["GLfixed**"]         = "Fixed**" ;
    typesConversion["GLint64**"]         = "Int64**" ;
    typesConversion["GLuint64**"]        = "UInt64**" ;
    typesConversion["GLfloat**"]         = "Float**" ;
    typesConversion["GLdouble**"]        = "Double**" ;
    typesConversion["GLhalf**"]          = "Half**" ;
    typesConversion["GLclampf**"]        = "Clampf**" ;
    typesConversion["GLclampd**"]        = "Clampd**" ;
    typesConversion["GLsizei**"]         = "Size**" ;
    typesConversion["GLenum**"]          = "Enum**" ;
    typesConversion["GLvoid**"]          = "Void**" ;
    typesConversion["void**"]            = "Void**" ;
    typesConversion["GLintptr**"]        = "IntPtr**" ;
    typesConversion["GLintptrARB**"]     = "IntPtrARB**" ;
    typesConversion["GLsizeiptr**"]      = "SizePtr**" ;
    typesConversion["GLsizeiptrARB**"]   = "SizePtrARB**" ;
    typesConversion["GLsync**"]          = "Sync**" ;
    typesConversion["GLbitfield**"]      = "BitField**" ;

    typesConversion["const GLboolean**"]       = "const Boolean**" ;
    typesConversion["const GLbyte**"]          = "const Byte**" ;
    typesConversion["const GLubyte**"]         = "const UByte**" ;
    typesConversion["const GLchar**"]          = "const Char**" ;
    typesConversion["const char**"]            = "const Char**" ;
    typesConversion["const GLshort**"]         = "const Short**" ;
    typesConversion["const GLushort**"]        = "const UShort**" ;
    typesConversion["const GLint**"]           = "const Int**" ;
    typesConversion["const GLuint**"]          = "const UInt**" ;
    typesConversion["const GLfixed**"]         = "const Fixed**" ;
    typesConversion["const GLint64**"]         = "const Int64**" ;
    typesConversion["const GLuint64**"]        = "const UInt64**" ;
    typesConversion["const GLfloat**"]         = "const Float**" ;
    typesConversion["const GLdouble**"]        = "const Double**" ;
    typesConversion["const GLhalf**"]          = "const Half**" ;
    typesConversion["const GLclampf**"]        = "const Clampf**" ;
    typesConversion["const GLclampd**"]        = "const Clampd**" ;
    typesConversion["const GLsizei**"]         = "const Size**" ;
    typesConversion["const GLenum**"]          = "const Enum**" ;
    typesConversion["const GLvoid**"]          = "const Void**" ;
    typesConversion["const void**"]            = "const Void**" ;
    typesConversion["const GLintptr**"]        = "const IntPtr**" ;
    typesConversion["const GLintptrARB**"]     = "const IntPtrARB**" ;
    typesConversion["const GLsizeiptr**"]      = "const SizePtr**" ;
    typesConversion["const GLsizeiptrARB**"]   = "const SizePtrARB**" ;
    typesConversion["const GLsync**"]          = "const Sync**" ;
    typesConversion["const GLbitfield**"]      = "const BitField**" ;
}
