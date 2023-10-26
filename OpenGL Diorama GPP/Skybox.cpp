#include "Skybox.h"

void Skybox::Initialise()
{
    //Names for daytime skybox images
    skyboxTexnames[0] = "daySky_left.png";
    skyboxTexnames[1] = "daySky_right.png";
    skyboxTexnames[2] = "daySky_bottom.png";
    skyboxTexnames[3] = "daySky_top.png";
    skyboxTexnames[4] = "daySky_back.png";
    skyboxTexnames[5] = "daySky_front.png";

    //Names for nighttime skybox images
    NightSkyboxTexNames[0] = "nightSky_left.png";
    NightSkyboxTexNames[1] = "nightSky_right.png";
    NightSkyboxTexNames[2] = "nightSky_bottom.png";
    NightSkyboxTexNames[3] = "nightSky_top.png";
    NightSkyboxTexNames[4] = "nightSky_back.png";
    NightSkyboxTexNames[5] = "nightSky_front.png";
}