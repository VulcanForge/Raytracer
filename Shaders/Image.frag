#version 450 core

in vec2 texturePositionFragment;

out vec4 colour;

uniform sampler2D imageTexture;

void main ()
{
    colour = texture (imageTexture, texturePositionFragment);
}