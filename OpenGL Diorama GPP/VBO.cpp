// Include the header file for the VBO class
#include "VBO.h"

// Constructor for the VBO class, which takes in the vertices array and its size
VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	// Generate a buffer object, which will be used to store the vertex data
	glGenBuffers(1, &ID);

	// Bind the buffer object to the GL_ARRAY_BUFFER target
	glBindBuffer(GL_ARRAY_BUFFER, ID);

	// Copy the vertex data to the buffer object
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// Bind the buffer object to the GL_ARRAY_BUFFER target
void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbind the buffer object from the GL_ARRAY_BUFFER target
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Delete the buffer object
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}




