// This line ensures that the header file is only included once in the program
#pragma once

// Include external headers and basic mesh class header
#include "ExternalHeaders.h"
#include "BasicMesh.h"

// Define a Model class
class Model
{
public:
	// Constructor that loads a 3D model from the specified file path
	Model(const GLchar* path)
	{
		this->loadModel(path);
	}

	// Method that draws the meshes in the model using the provided shader
	void Draw(Shader shader)
	{
		// Loop through each mesh in the model and draw it
		for (GLuint i = 0; i < this->meshes.size(); i++)
		{
			this->meshes[i].Draw(shader);
		}
	}
private:
	// Vector of BasicMesh objects that represent the meshes in the model
	std::vector<BasicMesh> meshes;
	// String that represents the directory where the model file is located
	std::string directory;

	// Vector of Texture objects that represent the textures that have been loaded for the model
	std::vector<Texture> textures_loaded;

	// Private method that loads a 3D model from the specified file path
	void loadModel(std::string path)
	{
		// Create an instance of the Assimp importer
		Assimp::Importer importer;

		// Load the model from the specified file path and apply some post-processing options
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		// If the scene failed to load, output an error message and return
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
			return;
		}

		// Get the directory path of the model file and store it in the "directory" member variable
		this->directory = path.substr(0, path.find_last_of('/'));

		// Recursively process each node in the scene starting from the root node
		this->processNode(scene->mRootNode, scene);
	}


	// This function processes a node in the scene's hierarchy.
	void processNode(aiNode* node, const aiScene* scene)
	{
		// Iterate through each mesh in the node.
		for (GLuint i = 0; i < node->mNumMeshes; i++)
		{
			// Get the mesh from the scene's list of meshes.
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

			// Process the mesh and add it to the Model's list of meshes.
			this->meshes.push_back(this->processMesh(mesh, scene));
		}

		// Recursively process each child node in the hierarchy.
		for (GLuint i = 0; i < node->mNumChildren; i++)
		{
			this->processNode(node->mChildren[i], scene);
		}
	}

	// This function processes a mesh and returns a BasicMesh object.
	BasicMesh processMesh(aiMesh* mesh, const aiScene* scene)
	{
		// Create vectors to store the mesh's vertices, indices, and textures.
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;

		// Iterate through each vertex in the mesh.
		for (GLuint i = 0; i < mesh->mNumVertices; i++)
		{
			// Create a new Vertex object.
			Vertex vertex;

			// Set the vertex's position.
			glm::vec3 vector;
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;

			// Set the vertex's normal.
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;

			// Set the vertex's texture coordinates.
			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else
			{
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);
			}

			// Add the new vertex to the list of vertices.
			vertices.push_back(vertex);
		}

		// Iterate through each face in the mesh.
		for (GLuint i = 0; i < mesh->mNumFaces; i++)
		{
			// Get the face from the mesh.
			aiFace face = mesh->mFaces[i];

			// Add each index in the face to the list of indices.
			for (GLuint j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		// If the mesh has a material, load its textures.
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			// Load the diffuse maps.
			std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			// Load the specular maps.
			std::vector<Texture>  specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		}

		return BasicMesh(vertices, indices, textures);
	}

	// This function loads textures for a given material and texture type.
	// It returns a vector of Texture structs.
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
	{
		std::vector<Texture> textures;

		// Iterate over all the textures of the given type for the material.
		for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);

			GLboolean skip = false;

			// Check if the texture has already been loaded.
			for (GLuint j = 0; j < textures_loaded.size(); j++)
			{
				if (textures_loaded[j].path == str)
				{
					textures.push_back(textures_loaded[j]);
					skip = true;
					break;
				}
			}

			// If the texture has not been loaded before, load it.
			if (!skip)
			{
				Texture texture;
				texture.id = TextureFromFile(str.C_Str(), this->directory);
				texture.type = typeName;
				texture.path = str;
				textures.push_back(texture);

				this->textures_loaded.push_back(texture);
			}
		}

		return textures;
	}

	// This function loads a texture from a file.
	GLint TextureFromFile(const char* path, std::string directory)
	{
		std::string filename = std::string(path);
		filename = directory + '/' + filename;
		GLuint textureID;
		glGenTextures(1, &textureID);

		int width, height, channels;

		// Load the image using the SOIL library.
		unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, &channels, SOIL_LOAD_RGB);

		// Bind the texture and set its parameters.
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Free the image data.
		SOIL_free_image_data(image);

		return textureID;
	}

};

