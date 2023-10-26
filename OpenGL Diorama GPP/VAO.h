// Header guard to prevent multiple inclusion of the same header file
#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h> // OpenGL library header file
#include "VBO.h" // Header file for Vertex Buffer Object (VBO)

class VAO
{
public:
	GLuint ID; // ID of the Vertex Array Object (VAO)
	VAO(); // Constructor

	// Function to link an attribute to a VBO in the VAO
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

	// Function to bind the VAO
	void Bind();

	// Function to unbind the VAO
	void Unbind();

	// Function to delete the VAO
	void Delete();
};

#endif // End of header guard for VAO_CLASS_H
