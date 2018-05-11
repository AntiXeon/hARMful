#include "GL/glew.h"
#include "GL/gl.h"

namespace Hope {
	namespace OGL3 {
		namespace Types {
            typedef GLboolean       Boolean ;
            typedef GLbyte          Byte ;
            typedef GLubyte         UByte ;
            typedef GLchar          Char ;
            typedef GLshort         Short ;
            typedef GLushort        UShort ;
            typedef GLint           Int ;
            typedef GLuint          UInt ;
            typedef GLfixed         Fixed ;
            typedef GLint64         Int64 ;
            typedef GLuint64        UInt64 ;
            typedef GLfloat         Float ;
            typedef GLdouble        Double ;
            typedef GLhalf          Half ;
            typedef GLclampf        Clampf ;
            typedef GLclampd        Clampd ;
            typedef GLsizei         Size ;
            typedef GLenum          Enum ;
            typedef GLvoid          Void ;
            typedef void            Void ;
            typedef GLintptr        IntPtr ;
            typedef GLintptrARB     IntPtrARB ;
            typedef GLsizeiptr      SizePtr ;
            typedef GLsizeiptrARB   SizePtrARB ;
            typedef GLsync          Sync ;
            typedef GLbitfield      BitField ;
		} ;

		#include "OGL3/Buffers.inl"
		#include "OGL3/Framebuffer.inl"
		#include "OGL3/Misc.inl"
		#include "OGL3/ProgramAttibutes.inl"
		#include "OGL3/Program.inl"
		#include "OGL3/ProgramUniforms.inl"
		#include "OGL3/Query.inl"
		#include "OGL3/RenderBuffer.inl"
		#include "OGL3/Rendering.inl"
		#include "OGL3/Sampler.inl"
		#include "OGL3/Shader.inl"
		#include "OGL3/Sync.inl"
		#include "OGL3/Texture.inl"
		#include "OGL3/TypeGetter.inl"
		#include "OGL3/VertexArray.inl"
	} ;
} ;

// To anticipate the use of Vulkan in future versions of the library.
using namespace Hope::OGL3::Types ;
