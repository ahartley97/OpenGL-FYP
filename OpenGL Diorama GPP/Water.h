#pragma once
#include"ExternalHeaders.h"
class Water
{
public:
	// Variables for water properties and dimensions
	float numCellX = 1000;
	float numCellZ = 1000;
	int numVertX = static_cast<int>(numCellX + 1);
	int numVertZ = static_cast<int>(numCellZ + 1);

	// Dimensions for reflection and refraction textures
	const int REFLECTION_WIDTH = 320;
	const int REFLECTION_HEIGHT = 180;

	const int REFRACTION_WIDTH = 1280;
	const int REFRACTION_HEIGHT = 720;

	// Variables for texture locations and wave movement
	int location_reflectionTexture = 0;
	int location_refractionTexture = 0;
	int location_dudvMap = 0;
	int location_moveFactor = 0;

	float Wave_Speed = 0.01f;
	float moveFactor = 0;

	// Vectors to hold the coordinates, indices, texture coordinates, normals, and colors of the water
	std::vector<glm::vec3> WaterCoords;
	std::vector<GLuint> WaterIndices;
	std::vector<glm::vec2> WaterTexCoords;
	std::vector<glm::vec3> WaterNormals;
	std::vector<glm::vec3> WaterColors;

	// Variables for water position and model matrix
	glm::vec3 waterPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 waterModel = glm::mat4(1.0f);

	// Function to populate the vectors with the coordinates, indices, texture coordinates, normals, and colors of the water
	void populateVerts();
};

