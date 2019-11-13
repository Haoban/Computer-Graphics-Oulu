#version 330 core
layout (location=0) in vec3 in_Position;
layout (location=2) in vec3 in_Normal;

// model-view and projection matrices
uniform mat4 mvmatrix; // model view matrix
uniform mat4 pmatrix;  // projection matrix

out vec3 pos;
out vec3 N;

void main(void)
{
    
    gl_Position = pmatrix * mvmatrix * vec4(in_Position, 1.0);
    pos = (mvmatrix * vec4(in_Position, 1.0)).xyz;  // position data
    N = normalize((mvmatrix * vec4(in_Normal, 0.0)).xyz);  // normal data
}



