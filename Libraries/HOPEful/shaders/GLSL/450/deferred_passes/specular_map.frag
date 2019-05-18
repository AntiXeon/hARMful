// Diffuse/normal/specular material shader.

struct Material {
    sampler2D specular ;
    float shininess ;
} ;

uniform Material material ;

layout(location = 0) in vec2 inTexCoord ;

out vec4 outColor ;

void main() {
    vec3 specularValue = vec3(texture(material.specular, inTexCoord).r) ;
    outColor = vec4(specularValue, material.shininess) ;
}
