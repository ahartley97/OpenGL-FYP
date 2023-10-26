#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;
// Normals (not necessarily normalized)
layout (location = 3) in vec3 aNormal;

out vec4 clipSpace;
// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the Fragment Shader
out vec2 texCoord;
// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outputs the current position for the Fragment Shader
out vec3 crntPos;

// Imports the camera matrix from the main function
uniform mat4 camMatrix;
// Imports the model matrix from the main function
uniform mat4 model;

const float tilling = 6.0;

void main()
{

	// calculates current position
	crntPos = vec3(model * vec4(aPos, 1.0f));
	// Outputs the positions/coordinates of all vertices
	clipSpace = camMatrix * vec4(crntPos, 1.0);
	gl_Position =  camMatrix * vec4(aPos, 1.0);
	texCoord = vec2(aPos.x/2.0 + 0.5, aPos.y/2.0 + 0.5) * tilling;

	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;
	// Assigns the normal from the Vertex Data to "Normal"
	Normal = aNormal;
}