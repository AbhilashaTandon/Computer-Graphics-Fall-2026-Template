
#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in float diffuse;

uniform sampler2D texture_diffuse1;

void main()
{    
    FragColor = vec4(diffuse, diffuse, diffuse, 1.) * texture(texture_diffuse1, TexCoords) * .8 + .2 * vec4(1.);
}
