#ifndef BUFFERS_H
#define BUFFERS_H

#include <glad/gl.h>


class VBO
{
	public:

		// ID reference of VBO
		unsigned int ID;

		// Constructor that generates a VBO ID
		VBO(float* vertices, GLsizeiptr size);
		
		// Binds VBO
		void Bind();

		// Unbinds VBO
		void Unbind();

		// Deletes VBO
		void Delete();
};

class EBO
{
	public:
		// ID reference of EBO
		unsigned int ID;

		// Constructor that generates a EBO ID
		EBO(unsigned int* indices, GLsizeiptr size);

		// Binds EBO
		void Bind();

		// Unbinds EBO
		void Unbind();

		// Deletes EBO
		void Delete();
};

class VAO
{
	public:

		// ID reference of VAO
		unsigned int ID;

		// Constructor that generates a VAO ID
		VAO();
		// Links VBO to VAO
		void LinkAttrib(VBO vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

		// Binds VAO
		void Bind();

		// Unbinds VAO
		void Unbind();

		// Deletes VAO
		void Delete();
};

#endif
