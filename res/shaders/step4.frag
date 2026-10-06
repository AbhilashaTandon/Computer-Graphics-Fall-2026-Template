#version 330 core


in vec4 pos;
in vec4 norm;
in vec2 TexCoord;
in float light;
out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
    FragColor = vec4(light,light,light,1.f) * texture(ourTexture, TexCoord) + vec4(.1, .1, .1, .0);
} 


