#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec4 pos;
out vec2 TexCoord;

void main()
{
    pos = vec4(aPos, 1.);
    gl_Position = pos;
    TexCoord = aTexCoord;
}
