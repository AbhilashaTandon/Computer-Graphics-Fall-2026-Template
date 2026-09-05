#version 330 core

uniform float aTime;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextCoord;

out vec4 pos;
out float time;
out vec2 texCoord;
uniform mat4 proj;


void main()
{
    texCoord = aTextCoord;
    time = aTime;
    pos = proj * vec4(aPos, 1.);
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}
