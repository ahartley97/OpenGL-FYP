#pragma once
#include "ExternalHeaders.h" //Include the external headers
class Skybox
{
public:
    void Initialise();//function to initialise the variables
    std::string skyboxTexnames[6];//array to hold the names of the day time textures
    std::string NightSkyboxTexNames[6];//array to hold the names of the night time textures
};

