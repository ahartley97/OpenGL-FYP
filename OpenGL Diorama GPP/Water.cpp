#include "Water.h"

void Water::populateVerts()
{
    // Set the width and height of the water plane
    float width{ 115000 };
    float height{ 28500 };

    // Set an offset to adjust the position of the water plane vertices
    glm::vec3 offset(-60, 0, -70);

    // Loop through the vertices in the z direction
    for (int i = 0; i < numVertZ; i++)
    {
        // Calculate the ratio of the current vertex in the z direction
        float ratioX = i / (float)numVertZ;

        // Loop through the vertices in the x direction
        for (int j = 0; j < numVertX; j++)
        {
            // Calculate the ratio of the current vertex in the x direction
            float ratioZ = j / (float)numVertX;

            // Calculate the position of the vertex based on the ratios and the dimensions of the water plane
            glm::vec3 pos{ ratioX * width, 0, ratioZ * height };

            // Add the offset to adjust the position of the vertex
            WaterCoords.push_back(pos + offset);

            // Add the texture coordinates of the vertex
            WaterTexCoords.push_back(glm::vec2(j, i));

            // Add the normal of the vertex (in this case, always (0,1,0) as it's a flat water plane)
            WaterNormals.push_back(glm::vec3(0, 1, 0));
        }
    }

    // Loop through the cells of the water plane
    bool Swap = false;
    for (int cellZ = 0; cellZ < numCellZ; cellZ++)
    {
        for (int cellX = 0; cellX < numCellX; cellX++)
        {
            // Calculate the index of the first vertex in the cell
            int startVertIndex = (cellZ * numVertX) + cellX;

            // Add indices to create triangles for the cell, swapping the winding order every other cell
            if (Swap)
            {
                WaterIndices.push_back(startVertIndex);
                WaterIndices.push_back(startVertIndex + 1);
                WaterIndices.push_back(startVertIndex + numVertX);

                WaterIndices.push_back(startVertIndex + 1);
                WaterIndices.push_back(startVertIndex + numVertX + 1);
                WaterIndices.push_back(startVertIndex + numVertX);
            }
            else
            {
                WaterIndices.push_back(startVertIndex);
                WaterIndices.push_back(startVertIndex + numVertX + 1);
                WaterIndices.push_back(startVertIndex + numVertX);

                WaterIndices.push_back(startVertIndex + 1);
                WaterIndices.push_back(startVertIndex + numVertX + 1);
                WaterIndices.push_back(startVertIndex);
            }
            Swap = !Swap;
        }
        Swap = !Swap;
    }

    // Translate the water plane to its specified position
    waterModel = glm::translate(waterModel, waterPos);
}
