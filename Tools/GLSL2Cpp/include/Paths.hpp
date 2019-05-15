#ifndef __GLSL2CPP__PATHS__
#define __GLSL2CPP__PATHS__

#define PathSeparator               "/"
#define LibName                     "HOPE"
#define LibDirName                  LibName "ful"
#define ShadersDirectoryName        "shaders"
#define ShadersDirectory            LibDirName PathSeparator ShadersDirectoryName
#define CppPath                     "scene" PathSeparator "components" PathSeparator "materials" PathSeparator
#define HeaderCppDirectory          LibDirName PathSeparator "include" PathSeparator CppPath
#define SourceCppDirectory          LibDirName PathSeparator "src" PathSeparator CppPath

#define LibDirectory                ".." PathSeparator ".." PathSeparator ".." PathSeparator "Libraries" PathSeparator LibDirName PathSeparator
#define SimLinkDirectory            "." PathSeparator LibDirName

#define GLSLDirectory               "GLSL"
#define IncludesDirectory           "includes"
#define ModuleDirectory             "modules"

#define GLSL450Directory            "450"
#define GLSL450ModulesDirectory     GLSLDirectory PathSeparator GLSL450Directory PathSeparator ModuleDirectory

#define GLSLIncludesDirectory       GLSLDirectory PathSeparator IncludesDirectory
#define ShadersCppHeadersDirectory  HeaderCppDirectory ShadersDirectoryName
#define ShadersCppSourcesDirectory  SourceCppDirectory ShadersDirectoryName
#define GLSLCppHeadersDirectory     ShadersCppHeadersDirectory PathSeparator GLSLDirectory
#define GLSLCppSourcesDirectory     ShadersCppSourcesDirectory PathSeparator GLSLDirectory

#define CppHeaderExtension          ".hpp"
#define CppSourceExtension          ".cpp"

#define VertexShaderExtension       ".vert"
#define FragmentShaderExtension     ".frag"
#define GeometryShaderExtension     ".geom"
#define GLSLModuleExtension         ".glsl"

#endif
