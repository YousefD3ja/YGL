#include <objects.h>

Object::Cube::Cube(std::string* textures)
{
	if (textures != nullptr)
	{
	}
}

void Object::Cube::GenerateTexture(unsigned int* textures, std::string* textureArray, int renderType)
{
	if (textureArray != nullptr)
	{
		if (sizeof(textureArray) / sizeof(std::string) == 6)
		{
			glGenTextures(6, textures);
			glActiveTexture(GL_TEXTURE0);
			glBindTextures(0,6, textures);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, renderType);

		}
	}
}