// Diffuse/normal/specular material shader.

struct Material {
    vec3 ambient ;
    vec3 diffuse ;
    vec3 specular ;
    float shininess ;
} ;

uniform Material material ;
out vec4 outColor ;

void main() {
    outColor = vec4(material.diffuse, 1.f) ;
}
