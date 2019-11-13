#version 330 core
in vec3 pos;
in vec3 N;

uniform vec4 lightPosition; // In view coordinate frame!

layout (location=0) out vec4 fragColor;

const vec4 ambientProduct = vec4(0.1, 0.1, 0.1, 1.0);
const vec4 diffuseProduct = vec4(0.5, 0.3, 0.2, 1.0);
const vec4 specularProduct = vec4(0.9, 0.9, 0.9, 1.0);
const float shininess = 100.0;

void main(void) {
    
    vec3 light = lightPosition.xyz;
    vec3 L = normalize(light - pos);
    vec3 E = normalize(-pos);
    vec3 H = normalize(L + E);
    
    vec4 ambient = ambientProduct;
    
    float Kd = max(dot(L, N), 0.0);
    vec4 diffuse = Kd * diffuseProduct;
    
    float Ks = pow(max(dot(N, H), 0.0), shininess);
    vec4 specular = Ks * specularProduct;
    
    if (dot(L, N) < 0.0) {
        specular = vec4(0.0, 0.0, 0.0, 1.0);
    }
    
    fragColor = (ambient + diffuse + specular);
}
