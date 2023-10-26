#ifndef TERRAIN_CLASS_H
#define TERRAIN_CLASS_H

#include "ExternalHeaders.h"

class Terrain
{
public:
    // Index to use for rendering
    int index = 1;

    // Load the heightmap image
    void loadHeightmap();

    // Populate the coordinate vectors for grass
    void populateVectors();

    // Dimensions of the heightmap
    int Heightwidth;
    int Heightheight;
    int HeightnrChannels;
    unsigned char* data = 0;

    // Number of triangle strips and triangles per strip
    int numStrips;
    int numTrisPerStrip;

    // Vertex coordinates for grass
    std::vector<glm::vec3> GrassCoords;

    // Indices for vertices
    std::vector<GLuint> GrassIndices;

    // Texture coordinates for grass
    std::vector<glm::vec2> GrassTexCoords;

    // Normal vectors for grass
    std::vector<glm::vec3> GrassNormals;

    // Colors for grass vertices
    std::vector<glm::vec3> GrassColors =
    {
        // Colors for each vertex
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f}
    };

    // Position of the terrain
    glm::vec3 terrainPos = glm::vec3(0.0f, 0.0f, 0.0f);

    // Model matrix for the terrain
    glm::mat4 terrainModel = glm::mat4(1.0f);

};

#endif // TERRAIN_CLASS_H
