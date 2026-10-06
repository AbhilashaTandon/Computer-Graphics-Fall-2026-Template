#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 proj;
uniform mat4 model;
uniform mat4 view;
uniform vec4 light_pos;

out vec4 pos;
out vec4 norm;
out vec2 TexCoord;
out float light;

void main()
{
    pos = vec4(aPos, 1.);
    norm = proj * view * model * vec4(aNorm,0.);
    
    light = dot(norm, light_pos);
    gl_Position = proj * view * model * pos;
    TexCoord = aTexCoord;
}
