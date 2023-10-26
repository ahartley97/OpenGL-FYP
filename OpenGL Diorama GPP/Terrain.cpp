// Include the header file for the Terrain class
#include "Terrain.h"

// Load the heightmap image and store the data in the 'data' variable
void Terrain::loadHeightmap()
{
    // Set the flag to flip the image vertically during loading (for OpenGL compatibility)
    stbi_set_flip_vertically_on_load(true);

    // Load the heightmap image and retrieve its width, height, number of channels, and data
    data = stbi_load("_heightmap.jpg", &Heightwidth, &Heightheight, &HeightnrChannels, 0);

    // Check if the image was loaded successfully
    if (data)
    {
        std::cout << "Loaded heightmap of size " << Heightheight << " x " << Heightwidth << std::endl;
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
}

void Terrain::populateVectors()
{
    // set up vertex data (and buffer(s)) and configure vertex attributes
   // ------------------------------------------------------------------
    std::vector<float> vertices;
    float yScale = 64.0f / 256.0f, yShift = 0.0f;
    int rez = 1;
    unsigned bytePerPixel = HeightnrChannels;
    for (int i = 0; i < Heightheight; i++)
    {
        for (int j = 0; j < Heightwidth; j++)
        {
            unsigned char* pixelOffset = data + (j + Heightwidth * i) * bytePerPixel;
            unsigned char y = pixelOffset[0];

            // vertex

            GrassCoords.push_back(glm::vec3(-Heightheight / 2.0f + Heightheight * i / (float)Heightheight,
                ((int)y * yScale - yShift) * -1 + 4, -Heightwidth / 2.0f + Heightwidth * j / (float)Heightwidth));
            GrassTexCoords.push_back({ ((float)i / Heightheight) * 100, ((float)j / Heightwidth) * 100 });
            GrassNormals.push_back({ 0,1,0 });
        }
    }
    std::cout << "Loaded " << GrassCoords.size() / 3 << " vertices" << std::endl;
    stbi_image_free(data);

    std::vector<unsigned> indices;
    for (int i = 0; i < Heightheight - 1; i += rez)
    {
        for (int j = 0; j < Heightwidth; j += rez)
        {
            for (int k = 0; k < 2; k++)
            {
                GrassIndices.push_back(j + Heightwidth * (i + k * rez));
            }
        }
    }

    numStrips = (Heightheight - 1) / rez;
    numTrisPerStrip = (Heightwidth / rez) * 2 - 2;

    terrainModel = glm::translate(terrainModel, terrainPos);
}
