#ifndef SHADER_CLASS_H  // Header guard to prevent multiple inclusions of the header
#define SHADER_CLASS_H

#include <glad/glad.h>   // Include the OpenGL header
#include <string>        // Include the string header
#include <fstream>       // Include the file stream header
#include <sstream>       // Include the string stream header
#include <iostream>      // Include the standard input/output header
#include <cerrno>        // Include the header for handling errors

// Declare a function to read the contents of a file and return them as a string
std::string get_file_contents(const char* filename);

// Declare the Shader class
class Shader
{
public:
	// The ID of the shader program
	GLuint ID;

	// Constructor that takes the paths to vertex and fragment shader files and creates a shader program
	Shader(const char* vertexFile, const char* fragmentFile);

	// Method to activate the shader program
	void Activate();

	// Method to delete the shader program
	void Delete();
};

#endif // SHADER_CLASS_H  // Close the header guard
