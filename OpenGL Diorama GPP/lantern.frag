#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Imports the color from the Vertex Shader
in vec3 color;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the current position from the Vertex Shader
in vec3 crntPos;

// Gets the Texture Units from the main function
uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;

// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;

// Gets the brightness of the day and night cycle
uniform float brightness;


void main()
{
	if(brightness < 0.3)
	{
			FragColor = vec4(texture(texture_diffuse, texCoord));//after light is switched on
	}
	else
	{
			FragColor = vec4(texture(texture_diffuse, texCoord)) * (brightness + 0.1) + vec4(0.0, 0.0, 0.0, 1.0) * ((1 - brightness));//before light is switched on
	}
}