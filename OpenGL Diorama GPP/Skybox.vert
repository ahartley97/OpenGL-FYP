#version 330 core
// Positions/Coordinates
layout (location = 0) in vec3 aPos;

// Outputs the texture coordinates to the Fragment Shader
out vec3 TexCoords;

uniform mat4 combined;

void main()
{
    TexCoords = aPos;
    gl_Position = combined * vec4(aPos, 1.0);
}  