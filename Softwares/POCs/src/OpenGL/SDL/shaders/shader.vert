#version 130

// Attributes
in vec3 VertexColor ;
in vec3 VertexPosition ;

// Uniform
uniform mat4 ModelViewProjectionMatrix ;

// gl_Position declared as invariant
invariant gl_Position ;

// Interpolated color given to fragment shader
smooth out vec3 InterpolatedColor ;

void main () {
	InterpolatedColor = VertexColor ;
	gl_Position = ModelViewProjectionMatrix * vec4 (VertexPosition, 1.0) ; 
}
