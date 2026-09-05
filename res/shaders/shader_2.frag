#version 330 core

uniform sampler2D u_Texture; //texture id

in vec4 pos;
in float time;
in vec2 texCoord;

out vec4 FragColor;

void main()
{
    FragColor = texture(u_Texture, texCoord);
} 


