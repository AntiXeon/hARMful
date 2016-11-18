/**
 * types.cpp
 * GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007
 *
 * @Author:      Denis CARLUS
 * @Created on:  18-Nov-2016
 * @Last change: 18-Nov-2016
 */

static map<string, string> typesConversion ;

static std::string addNamespace(const std::string& type, const std::string ns) {
    const std::string tag = "%n" ;

    std::string copyType = type ;
    size_t startPos = copyType.find(tag) ;
    if (startPos == std::string::npos) {
        return type ;
    }

    copyType.replace(startPos, tag.length(), ns + "::") ;
    return copyType ;
}

/**
 * Convert the OpenGL types to standard names.
 * @param namesp [description]
 */
static void initTypesConversion(const std::string& namesp) {
    typesConversion["GLboolean"]       = addNamespace("%nBoolean", namesp) ;
    typesConversion["GLbyte"]          = addNamespace("%nByte", namesp) ;
    typesConversion["GLubyte"]         = addNamespace("%nUByte", namesp) ;
    typesConversion["GLchar"]          = addNamespace("%nChar", namesp) ;
    typesConversion["GLshort"]         = addNamespace("%nShort", namesp) ;
    typesConversion["GLushort"]        = addNamespace("%nUShort", namesp) ;
    typesConversion["GLint"]           = addNamespace("%nInt", namesp) ;
    typesConversion["GLuint"]          = addNamespace("%nUInt", namesp) ;
    typesConversion["GLfixed"]         = addNamespace("%nFixed", namesp) ;
    typesConversion["GLint64"]         = addNamespace("%nInt64", namesp) ;
    typesConversion["GLuint64"]        = addNamespace("%nUInt64", namesp) ;
    typesConversion["GLfloat"]         = addNamespace("%nFloat", namesp) ;
    typesConversion["GLdouble"]        = addNamespace("%nDouble", namesp) ;
    typesConversion["GLhalf"]          = addNamespace("%nHalf", namesp) ;
    typesConversion["GLclampf"]        = addNamespace("%nClampf", namesp) ;
    typesConversion["GLclampd"]        = addNamespace("%nClampd", namesp) ;
    typesConversion["GLsizei"]         = addNamespace("%nSize", namesp) ;
    typesConversion["GLenum"]          = addNamespace("%nEnum", namesp) ;
    typesConversion["GLvoid"]          = addNamespace("%nVoid", namesp) ;
    typesConversion["void"]            = addNamespace("%nVoid", namesp) ;
    typesConversion["GLintptr"]        = addNamespace("%nIntPtr", namesp) ;
    typesConversion["GLintptrARB"]     = addNamespace("%nIntPtrARB", namesp) ;
    typesConversion["GLsizeiptr"]      = addNamespace("%nSizePtr", namesp) ;
    typesConversion["GLsizeiptrARB"]   = addNamespace("%nSizePtrARB", namesp) ;
    typesConversion["GLsync"]          = addNamespace("%nSync", namesp) ;
    typesConversion["GLbitfield"]      = addNamespace("%nBitField", namesp) ;

    typesConversion["const GLboolean"]       = addNamespace("const %nBoolean", namesp) ;
    typesConversion["const GLbyte"]          = addNamespace("const %nByte", namesp) ;
    typesConversion["const GLubyte"]         = addNamespace("const %nUByte", namesp) ;
    typesConversion["const GLchar"]          = addNamespace("const %nChar", namesp) ;
    typesConversion["const GLshort"]         = addNamespace("const %nShort", namesp) ;
    typesConversion["const GLushort"]        = addNamespace("const %nUShort", namesp) ;
    typesConversion["const GLint"]           = addNamespace("const %nInt", namesp) ;
    typesConversion["const GLuint"]          = addNamespace("const %nUInt", namesp) ;
    typesConversion["const GLfixed"]         = addNamespace("const %nFixed", namesp) ;
    typesConversion["const GLint64"]         = addNamespace("const %nInt64", namesp) ;
    typesConversion["const GLuint64"]        = addNamespace("const %nUInt64", namesp) ;
    typesConversion["const GLfloat"]         = addNamespace("const %nFloat", namesp) ;
    typesConversion["const GLdouble"]        = addNamespace("const %nDouble", namesp) ;
    typesConversion["const GLhalf"]          = addNamespace("const %nHalf", namesp) ;
    typesConversion["const GLclampf"]        = addNamespace("const %nClampf", namesp) ;
    typesConversion["const GLclampd"]        = addNamespace("const %nClampd", namesp) ;
    typesConversion["const GLsizei"]         = addNamespace("const %nSize", namesp) ;
    typesConversion["const GLenum"]          = addNamespace("const %nEnum", namesp) ;
    typesConversion["const GLvoid"]          = addNamespace("const %nVoid", namesp) ;
    typesConversion["const void"]            = addNamespace("const %nVoid", namesp) ;
    typesConversion["const GLintptr"]        = addNamespace("const %nIntPtr", namesp) ;
    typesConversion["const GLintptrARB"]     = addNamespace("const %nIntPtrARB", namesp) ;
    typesConversion["const GLsizeiptr"]      = addNamespace("const %nSizePtr", namesp) ;
    typesConversion["const GLsizeiptrARB"]   = addNamespace("const %nSizePtrARB", namesp) ;
    typesConversion["const GLsync"]          = addNamespace("const %nSync", namesp) ;
    typesConversion["const GLbitfield"]      = addNamespace("const %nBitField", namesp) ;


    typesConversion["GLboolean*"]       = addNamespace("%nBoolean*", namesp) ;
    typesConversion["GLbyte*"]          = addNamespace("%nByte*", namesp) ;
    typesConversion["GLubyte*"]         = addNamespace("%nUByte*", namesp) ;
    typesConversion["GLchar*"]          = addNamespace("%nChar*", namesp) ;
    typesConversion["char*"]            = addNamespace("%nChar*", namesp) ;
    typesConversion["GLshort*"]         = addNamespace("%nShort*", namesp) ;
    typesConversion["GLushort*"]        = addNamespace("%nUShort*", namesp) ;
    typesConversion["GLint*"]           = addNamespace("%nInt*", namesp) ;
    typesConversion["GLuint*"]          = addNamespace("%nUInt*", namesp) ;
    typesConversion["GLfixed*"]         = addNamespace("%nFixed*", namesp) ;
    typesConversion["GLint64*"]         = addNamespace("%nInt64*", namesp) ;
    typesConversion["GLuint64*"]        = addNamespace("%nUInt64*", namesp) ;
    typesConversion["GLfloat*"]         = addNamespace("%nFloat*", namesp) ;
    typesConversion["GLdouble*"]        = addNamespace("%nDouble*", namesp) ;
    typesConversion["GLhalf*"]          = addNamespace("%nHalf*", namesp) ;
    typesConversion["GLclampf*"]        = addNamespace("%nClampf*", namesp) ;
    typesConversion["GLclampd*"]        = addNamespace("%nClampd*", namesp) ;
    typesConversion["GLsizei*"]         = addNamespace("%nSize*", namesp) ;
    typesConversion["GLenum*"]          = addNamespace("%nEnum*", namesp) ;
    typesConversion["GLvoid*"]          = addNamespace("%nVoid*", namesp) ;
    typesConversion["void*"]            = addNamespace("%nVoid*", namesp) ;
    typesConversion["GLintptr*"]        = addNamespace("%nIntPtr*", namesp) ;
    typesConversion["GLintptrARB*"]     = addNamespace("%nIntPtrARB*", namesp) ;
    typesConversion["GLsizeiptr*"]      = addNamespace("%nSizePtr*", namesp) ;
    typesConversion["GLsizeiptrARB*"]   = addNamespace("%nSizePtrARB*", namesp) ;
    typesConversion["GLsync*"]          = addNamespace("%nSync*", namesp) ;
    typesConversion["GLbitfield*"]      = addNamespace("%nBitField*", namesp) ;

    typesConversion["const GLboolean*"]       = addNamespace("const %nBoolean*", namesp) ;
    typesConversion["const GLbyte*"]          = addNamespace("const %nByte*", namesp) ;
    typesConversion["const GLubyte*"]         = addNamespace("const %nUByte*", namesp) ;
    typesConversion["const GLchar*"]          = addNamespace("const %nChar*", namesp) ;
    typesConversion["const char*"]            = addNamespace("const %nChar*", namesp) ;
    typesConversion["const GLshort*"]         = addNamespace("const %nShort*", namesp) ;
    typesConversion["const GLushort*"]        = addNamespace("const %nUShort*", namesp) ;
    typesConversion["const GLint*"]           = addNamespace("const %nInt*", namesp) ;
    typesConversion["const GLuint*"]          = addNamespace("const %nUInt*", namesp) ;
    typesConversion["const GLfixed*"]         = addNamespace("const %nFixed*", namesp) ;
    typesConversion["const GLint64*"]         = addNamespace("const %nInt64*", namesp) ;
    typesConversion["const GLuint64*"]        = addNamespace("const %nUInt64*", namesp) ;
    typesConversion["const GLfloat*"]         = addNamespace("const %nFloat*", namesp) ;
    typesConversion["const GLdouble*"]        = addNamespace("const %nDouble*", namesp) ;
    typesConversion["const GLhalf*"]          = addNamespace("const %nHalf*", namesp) ;
    typesConversion["const GLclampf*"]        = addNamespace("const %nClampf*", namesp) ;
    typesConversion["const GLclampd*"]        = addNamespace("const %nClampd*", namesp) ;
    typesConversion["const GLsizei*"]         = addNamespace("const %nSize*", namesp) ;
    typesConversion["const GLenum*"]          = addNamespace("const %nEnum*", namesp) ;
    typesConversion["const GLvoid*"]          = addNamespace("const %nVoid*", namesp) ;
    typesConversion["const void*"]            = addNamespace("const %nVoid*", namesp) ;
    typesConversion["const GLintptr*"]        = addNamespace("const %nIntPtr*", namesp) ;
    typesConversion["const GLintptrARB*"]     = addNamespace("const %nIntPtrARB*", namesp) ;
    typesConversion["const GLsizeiptr*"]      = addNamespace("const %nSizePtr*", namesp) ;
    typesConversion["const GLsizeiptrARB*"]   = addNamespace("const %nSizePtrARB*", namesp) ;
    typesConversion["const GLsync*"]          = addNamespace("const %nSync*", namesp) ;
    typesConversion["const GLbitfield*"]      = addNamespace("const %nBitField*", namesp) ;

    typesConversion["GLboolean**"]       = addNamespace("%nBoolean**", namesp) ;
    typesConversion["GLbyte**"]          = addNamespace("%nByte**", namesp) ;
    typesConversion["GLubyte**"]         = addNamespace("%nUByte**", namesp) ;
    typesConversion["GLchar**"]          = addNamespace("%nChar**", namesp) ;
    typesConversion["char**"]            = addNamespace("%nChar**", namesp) ;
    typesConversion["GLshort**"]         = addNamespace("%nShort**", namesp) ;
    typesConversion["GLushort**"]        = addNamespace("%nUShort**", namesp) ;
    typesConversion["GLint**"]           = addNamespace("%nInt**", namesp) ;
    typesConversion["GLuint**"]          = addNamespace("%nUInt**", namesp) ;
    typesConversion["GLfixed**"]         = addNamespace("%nFixed**", namesp) ;
    typesConversion["GLint64**"]         = addNamespace("%nInt64**", namesp) ;
    typesConversion["GLuint64**"]        = addNamespace("%nUInt64**", namesp) ;
    typesConversion["GLfloat**"]         = addNamespace("%nFloat**", namesp) ;
    typesConversion["GLdouble**"]        = addNamespace("%nDouble**", namesp) ;
    typesConversion["GLhalf**"]          = addNamespace("%nHalf**", namesp) ;
    typesConversion["GLclampf**"]        = addNamespace("%nClampf**", namesp) ;
    typesConversion["GLclampd**"]        = addNamespace("%nClampd**", namesp) ;
    typesConversion["GLsizei**"]         = addNamespace("%nSize**", namesp) ;
    typesConversion["GLenum**"]          = addNamespace("%nEnum**", namesp) ;
    typesConversion["GLvoid**"]          = addNamespace("%nVoid**", namesp) ;
    typesConversion["void**"]            = addNamespace("%nVoid**", namesp) ;
    typesConversion["GLintptr**"]        = addNamespace("%nIntPtr**", namesp) ;
    typesConversion["GLintptrARB**"]     = addNamespace("%nIntPtrARB**", namesp) ;
    typesConversion["GLsizeiptr**"]      = addNamespace("%nSizePtr**", namesp) ;
    typesConversion["GLsizeiptrARB**"]   = addNamespace("%nSizePtrARB**", namesp) ;
    typesConversion["GLsync**"]          = addNamespace("%nSync**", namesp) ;
    typesConversion["GLbitfield**"]      = addNamespace("%nBitField**", namesp) ;

    typesConversion["const GLboolean**"]       = addNamespace("const %nBoolean**", namesp) ;
    typesConversion["const GLbyte**"]          = addNamespace("const %nByte**", namesp) ;
    typesConversion["const GLubyte**"]         = addNamespace("const %nUByte**", namesp) ;
    typesConversion["const GLchar**"]          = addNamespace("const %nChar**", namesp) ;
    typesConversion["const char**"]            = addNamespace("const %nChar**", namesp) ;
    typesConversion["const GLshort**"]         = addNamespace("const %nShort**", namesp) ;
    typesConversion["const GLushort**"]        = addNamespace("const %nUShort**", namesp) ;
    typesConversion["const GLint**"]           = addNamespace("const %nInt**", namesp) ;
    typesConversion["const GLuint**"]          = addNamespace("const %nUInt**", namesp) ;
    typesConversion["const GLfixed**"]         = addNamespace("const %nFixed**", namesp) ;
    typesConversion["const GLint64**"]         = addNamespace("const %nInt64**", namesp) ;
    typesConversion["const GLuint64**"]        = addNamespace("const %nUInt64**", namesp) ;
    typesConversion["const GLfloat**"]         = addNamespace("const %nFloat**", namesp) ;
    typesConversion["const GLdouble**"]        = addNamespace("const %nDouble**", namesp) ;
    typesConversion["const GLhalf**"]          = addNamespace("const %nHalf**", namesp) ;
    typesConversion["const GLclampf**"]        = addNamespace("const %nClampf**", namesp) ;
    typesConversion["const GLclampd**"]        = addNamespace("const %nClampd**", namesp) ;
    typesConversion["const GLsizei**"]         = addNamespace("const %nSize**", namesp) ;
    typesConversion["const GLenum**"]          = addNamespace("const %nEnum**", namesp) ;
    typesConversion["const GLvoid**"]          = addNamespace("const %nVoid**", namesp) ;
    typesConversion["const void**"]            = addNamespace("const %nVoid**", namesp) ;
    typesConversion["const GLintptr**"]        = addNamespace("const %nIntPtr**", namesp) ;
    typesConversion["const GLintptrARB**"]     = addNamespace("const %nIntPtrARB**", namesp) ;
    typesConversion["const GLsizeiptr**"]      = addNamespace("const %nSizePtr**", namesp) ;
    typesConversion["const GLsizeiptrARB**"]   = addNamespace("const %nSizePtrARB**", namesp) ;
    typesConversion["const GLsync**"]          = addNamespace("const %nSync**", namesp) ;
    typesConversion["const GLbitfield**"]      = addNamespace("const %nBitField**", namesp) ;
}
