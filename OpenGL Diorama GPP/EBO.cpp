// include header file for EBO class
#include "EBO.h"

// constructor takes in an array of indices and the size of the array
EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	// Generate a new buffer object for the EBO
	glGenBuffers(1, &ID);

	// Bind the buffer object to the GL_ELEMENT_ARRAY_BUFFER target
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

	// Set the buffer data with the indices and size provided
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

// Bind the EBO to the GL_ELEMENT_ARRAY_BUFFER target
void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbind the EBO by binding 0 to the GL_ELEMENT_ARRAY_BUFFER target
void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Delete the EBO buffer object
void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}