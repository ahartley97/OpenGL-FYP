// Header guard to prevent multiple includes
#ifndef VBO_CLASS_H
#define VBO_CLASS_H

// OpenGL extension loader library
#include <glad/glad.h>

// Class definition for VBO
class VBO
{
public:
	GLuint ID; // ID of the VBO
	VBO(GLfloat* vertices, GLsizeiptr size); // Constructor that takes pointer to vertices and size of the array

	void Bind(); // Bind the VBO
	void Unbind(); // Unbind the VBO
	void Delete(); // Delete the VBO


};
#endif VBO_CLASS_H
