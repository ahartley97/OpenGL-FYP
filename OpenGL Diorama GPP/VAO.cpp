// Include the header file for the VAO class
#include "VAO.h"

// Constructor for the VAO class, which generates a vertex array object
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links an attribute from a VBO to the VAO
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	// Bind the VBO and set its attribute pointer
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);

	// Enable the attribute
	glEnableVertexAttribArray(layout);

	// Unbind the VBO
	VBO.Unbind();
}

// Bind the VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// Unbind the VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// Delete the VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}