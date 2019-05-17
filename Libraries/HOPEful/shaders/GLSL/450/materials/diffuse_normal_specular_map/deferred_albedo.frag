// Diffuse/normal/specular material shader.

struct Material {
    layout(binding = 0) sampler2D diffuse ;
    layout(binding = 1) sampler2D normal ;
    layout(binding = 2) sampler2D specular ;
    vec3 ambient ;
    float shininess ;
} ;

uniform Material material ;

layout(location = 0) in vec2 inTexCoord ;

out vec4 outColor ;

void main() {
    vec3 textureColor = texture(material.diffuse, inTexCoord).rgb ;
    outColor = vec4(textureColor, 1.f) ;
}
