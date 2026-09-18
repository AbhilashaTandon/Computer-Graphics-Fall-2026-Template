#version 330 core

uniform mat4 proj;
layout (location = 0) in vec3 aPos;

out vec4 pos;

void main()
{
    pos = proj * vec4(aPos, 1.);
    gl_Position = pos;
}
