#version 450 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texturePositionVertex;

out vec2 texturePositionFragment;

void main ()
{
    gl_Position = vec4 (position, 0, 1);
    texturePositionFragment = texturePositionVertex;
}