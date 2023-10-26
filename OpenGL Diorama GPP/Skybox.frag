#version 330 core

//Outputs the frag colour
out vec4 FragColor;

//Inputs the texture coordinates
in vec3 TexCoords;

//Passing in the two different textures and the brightness 
uniform samplerCube skybox;
uniform samplerCube nightSkybox;
uniform float brightness;

void main()
{    
    //This outputs a mixture of my day and night skybox depending on the brightness
    FragColor = vec4(texture(skybox, TexCoords)) * (brightness) + vec4(texture(nightSkybox, TexCoords)) * ((1 - brightness) + 0.5);
}