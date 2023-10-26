#include "BasicMesh.h"

BasicMesh::BasicMesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
{
    // Store the input vectors for vertices, indices and textures
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    // Call the SetUpMesh method to create the VAO, VBO, and EBO and bind the data to the buffer objects
    this->SetUpMesh();
}

void BasicMesh::Draw(Shader shader)
{
    // Counter variables for the number of diffuse and specular textures
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;

    // Iterate over all textures in the mesh
    for (GLuint i = 0; i < this->textures.size(); i++)
    {
        // Activate the texture unit for the current texture
        glActiveTexture(GL_TEXTURE0 + i);

        // Generate a string stream to concatenate the texture type (diffuse or specular) and its number to form a uniform name
        std::stringstream ss;
        std::string number;
        std::string name = this->textures[i].type;

        if ("texture_diffuse" == name)
        {
            ss << diffuseNr++;
        }
        else if ("texture_specular" == name)
        {
            ss << specularNr++;
        }

        number = ss.str();

        // Bind the texture to the current texture unit and set its corresponding uniform in the shader program
        glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
    }

    // Set the shininess uniform value in the shader program
    glUniform1f(glGetUniformLocation(shader.ID, "material.shininess"), 16.0f);

    // Bind the VAO to draw the mesh
    glBindVertexArray(this->VAO);

    // Draw the mesh using the indices and the current shader program
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);

    // Unbind the VAO after drawing
    glBindVertexArray(0);

    // Deactivate all texture units and unbind any bound textures
    for (GLuint i = 0; i < this->textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}


void BasicMesh::SetUpMesh()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

	//Vertex Positions:
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//Vertex Normals:
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

	//Vertex TexCoords:
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}
