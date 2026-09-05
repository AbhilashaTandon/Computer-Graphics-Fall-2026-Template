#version 330 core

layout (location = 0) in vec3 aPos;

out vec4 pos;

void main()
{
    pos = vec4(aPos, 1.);
    gl_Position = pos;
}
