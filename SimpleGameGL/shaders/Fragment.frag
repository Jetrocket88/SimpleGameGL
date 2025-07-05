#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
flat in int TexLayer;

uniform sampler2DArray uTextureArray;

void main()
{
    FragColor = texture(uTextureArray, vec3(TexCoord, TexLayer));
} 