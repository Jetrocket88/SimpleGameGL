#version 330 core
out vec4 FragColor;

in vec4 glColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = glColor * texture(ourTexture, TexCoord);
} 