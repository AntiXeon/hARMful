layout(binding = 0) uniform samplerCube cubemap ;

layout(location = 0) in vec3 inTexCoord ;
out vec4 outColor ;

void main() {
    outColor = texture(cubemap, inTexCoord) ;
}
