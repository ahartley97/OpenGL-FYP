#pragma once

// Include external headers
#include "ExternalHeaders.h"

// Class for rendering a scene
class SceneRenderer
{
public:
    // Public member variables for the positions of trees and lanterns, and the model matrix for the tent
    std::vector<glm::mat4> TreePositions;     // Collection of positions for trees
    std::vector<glm::mat4> LanternPositions;  // Collection of positions for lanterns
    glm::mat4 Tent_Model;                     // Model matrix for the tent

    // Public member variable for the scale of the scene
    float scale = 4.0f;

    // Methods for populating the transform vectors for trees and lanterns
    void PopulateTreeTransformVectors();
    void PopulateLanternTransformVectors();

    // Method for populating the overall position vectors for trees, lanterns, and the tent
    void PopulatePositionVectors();
};
