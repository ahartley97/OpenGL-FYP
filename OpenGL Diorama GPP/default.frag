#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the current position from the Vertex Shader
in vec3 crntPos;

// Gets the Texture Units from the main function
uniform sampler2D tex0;
uniform sampler2D tex1;

// Gets the color of the light from the main function
uniform vec4 lightColor;

// Gets the position of the light from the main function
uniform vec3 lightPos1;
uniform vec3 lightPos2;
uniform vec3 lightPos3;
uniform vec3 lightPos4;
uniform vec3 lightPos5;

// Gets the position of the camera from the main function
uniform vec3 camPos;

// Gets the brightness of the day and night cycle
uniform float brightness;

vec4 pointLight(vec3 lightPos)
{	
	// used in two variables so I calculate it here to not have to do it twice
	vec3 lightVec = lightPos - crntPos;

	// intensity of light with respect to distance
	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(tex0, texCoord) * (diffuse * inten + ambient) + texture(tex1, texCoord).r * specular * inten) * lightColor;
}

vec4 direcLight(sampler2D _Texture)
{
	// ambient lighting
	//float ambient = 0.20f;
	float ambient = brightness - 0.6;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(_Texture, texCoord) * (diffuse + ambient) + texture(tex1, texCoord).r * specular) * (1.0,1.0,1.0,1.0);
}

vec4 spotLight(vec3 lightPos)
{
	// controls how big the area that is lit up is
	float outerCone = 0.35f;
	float innerCone = 0.55f;

	// ambient lighting
	float ambient = 0.10f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	// calculates the intensity of the crntPos based on its angle to the center of the light cone
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(tex0, texCoord) * (diffuse * inten + ambient) + texture(tex1, texCoord).r * specular * inten) * lightColor;
}


void main()
{
	// Outputs final color

	
	if (brightness > 0.3) //This is before the lights switch on
	{

		FragColor += direcLight(tex0) * 0.7 + vec4(0.0,0.0,0.0,1.0) * 0.3;
	}
	else //This is after the lights are switched on
	{
		FragColor += spotLight(lightPos1) * 0.7 + vec4(0.0,0.0,0.0,1.0) * 0.3;
		FragColor += spotLight(lightPos2) * 0.7 + vec4(0.0,0.0,0.0,1.0) * 0.3;
		FragColor += spotLight(lightPos3) * 0.7 + vec4(0.0,0.0,0.0,1.0) * 0.3;
		FragColor += spotLight(lightPos4) * 0.7 + vec4(0.0,0.0,0.0,1.0) * 0.3;
	}
}