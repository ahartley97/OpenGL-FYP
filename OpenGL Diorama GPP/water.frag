#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

in vec4 clipSpace;
// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the current position from the Vertex Shader
in vec3 crntPos;

// Gets the position of the camera from the main function
uniform vec3 camPos;

// Declare uniforms that will be used in the shader
uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D dudvMap;
uniform float moveFactor;

// Declare a constant for wave strength
const float waveStregnth = 0.01;

void main()
{
	// Calculate normalized device coordinates from the vertex's clip space coordinates
	vec2 ndc = (clipSpace.xy/clipSpace.w) / 2.0 + 0.5;
	// Set the texture coordinates for both reflection and refraction
	vec2 refractTexCoords = vec2(ndc.x, ndc.y);
	vec2 reflectTexCoords = vec2(ndc.x, ndc.y);

	// Calculate the distortion of the water surface using the dudv map
	// and the move factor (which controls the speed of the waves)
	vec2 distortion1 = (texture(dudvMap, vec2(texCoord.x + moveFactor, texCoord.y)).rg * 2.0 - 1.0) * waveStregnth;
	vec2 distortion2 = (texture(dudvMap, vec2(-texCoord.x + moveFactor, texCoord.y + moveFactor)).rg * 2.0 - 1.0) * waveStregnth;
	vec2 total_distortion = distortion1 + distortion2;

	// Apply the distortion to the reflection and refraction texture coordinates
	reflectTexCoords += total_distortion;
	reflectTexCoords.x = clamp(reflectTexCoords.x, 0.001, 0.999);
	//reflectTexCoords.y = clamp(reflectTexCoords.y, -0.999, -0.001);
	refractTexCoords += total_distortion;
	refractTexCoords = clamp(refractTexCoords, 0.001, 0.999);

	// Sample the reflection and refraction textures using the distorted texture coordinates
	vec4 reflectColour = texture(reflectionTexture, reflectTexCoords);
	vec4 refractColour = texture(refractionTexture, refractTexCoords);

	// Mix the reflection and refraction colors
	//FragColor = mix(refractColour, reflectColour, 0.5);
	FragColor = refractColour * 0.5 + reflectColour * 0.5;

	// Adjust the final color by adding some color and multiplying by a factor
	FragColor = FragColor * 0.8 + vec4(0.0, 0.3, 0.5, 1.0) * 0.2;
}
