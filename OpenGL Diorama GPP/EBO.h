#ifndef EBO_CLASS_H  // Include guard to prevent multiple definitions
#define EBO_CLASS_H

#include <glad/glad.h>

// Class for an element buffer object (EBO)
class EBO
{
public:
    GLuint ID;  // OpenGL handle for the EBO

    // Constructor that takes in an array of indices and the size of the array
    EBO(GLuint* indices, GLsizeiptr size);

    // Method to bind the EBO to the current OpenGL context
    void Bind();

    // Method to unbind the EBO from the current OpenGL context
    void Unbind();

    // Method to delete the EBO from memory
    void Delete();
};

#endif  // EBO_CLASS_H
