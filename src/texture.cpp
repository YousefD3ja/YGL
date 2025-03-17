#include "texture.h"

Texture2D::Texture2D(const char* texture,unsigned int numTex, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType, int renderType)
{

	// Assigns the texture type
	type = textureType;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(texture, &width, &height, &nrChannels, 0);
	glGenTextures(numTex, &ID);
	glActiveTexture(slot);
	glBindTexture(textureType, ID);

	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, renderType);

	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(textureType, 0, GL_RGBA, width, height, 0, format, pixelType, bytes);
	glGenerateMipmap(textureType);

	stbi_image_free(bytes);
	glBindTexture(textureType, 0);
}

void Texture2D::textureUnit(Shader& shader, const char* uniform, int unit)
{
	// Gets the location of the uniform
	unsigned int textureUnit = glGetUniformLocation(shader.ID, uniform);
	// Activates the shader
	shader.Avtivate();

	glUniform1i(textureUnit, unit);
}

void Texture2D::uniform(int uniformID, float unit)
{
	glUniform1i(uniformID, unit);
}

void Texture2D::Bind()
{
	glBindTexture(type, ID);
}

void Texture2D::Unbind()
{
	glBindTexture(type, 0);
}

void Texture2D::Delete()
{
	glDeleteTextures(1, &ID);
}