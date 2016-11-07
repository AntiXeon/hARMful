#version 130

precision highp float ;

smooth in vec3 InterpolatedColor ;

// Output of the shader, going in the main framebuffer
out vec4 Color ;

void main() {
	Color = vec4 (InterpolatedColor, 1.0) ;
}
