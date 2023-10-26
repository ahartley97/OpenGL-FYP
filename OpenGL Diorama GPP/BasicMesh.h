#pragma once

// Include external headers
#include "ExternalHeaders.h"

// Define a structure for a single vertex in a mesh
struct Vertex
{
    glm::vec3 Position;  // Position of the vertex in 3D space
    glm::vec3 Normal;    // Normal of the surface at this vertex
    glm::vec2 TexCoords; // Texture coordinates at this vertex
};

// Define a structure for a texture used in the mesh
struct Texture
{
    GLuint id;             // OpenGL texture id
    std::string type;      // Type of the texture
    aiString path;         // Path to the texture file
};

// Define a class for a basic mesh
class BasicMesh
{
public:
    std::vector<Vertex> vertices;   // Collection of vertices in the mesh
    std::vector<GLuint> indices;    // Collection of indices used to render the mesh
    std::vector<Texture> textures;  // Collection of textures used in the mesh

    // Constructor that takes in the vertices, indices, and textures
    BasicMesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);

    // Method to draw the mesh using a given shader program
    void Draw(Shader shader);

private:
    GLuint VAO, VBO, EBO;  // OpenGL handles for the vertex array object, vertex buffer object, and element buffer object

    // Helper function to set up the mesh for rendering
    void SetUpMesh();
};
