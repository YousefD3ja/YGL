#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/gl.h>

#include <stb/stb_image.h>
#include <shaderclass.h>

class Texture2D
{
	public:
		// ID reference of texture
		unsigned int ID;
		GLenum type;
		// Texture image dimensions
		int width, height, nrChannels;
		// Constructor that generates a initialized texture
		Texture2D(
			const char* texture, unsigned int numTex,
			GLenum textureType, 
			GLenum solt, GLenum format, 
			GLenum pixelType, int renderType);

		void textureUnit(Shader& shader, const char* uniform, int unit);

		void uniform(int uniformID, float unit);
		// Binds the texture as the current active GL_TEXTURE_2D texture object
		void Bind();
		// Unbinds the texture
		void Unbind();
		// Deletes the texture
		void Delete();
};

#endif
