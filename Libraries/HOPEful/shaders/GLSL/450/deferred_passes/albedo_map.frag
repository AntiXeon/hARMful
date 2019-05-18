// Diffuse/normal/specular material shader.

struct Material {
    sampler2D diffuse ;
} ;

uniform Material material ;

layout(location = 0) in vec2 inTexCoord ;

out vec4 outColor ;

void main() {
    vec3 textureColor = texture(material.diffuse, inTexCoord).rgb ;
    outColor = vec4(textureColor, 1.f) ;
}
