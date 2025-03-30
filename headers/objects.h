#ifndef OBJECTS_H
#define OBJECTS_H

#include <buffers.h>
#include <texture.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Object
{
	class Cube
	{
		glm::vec3 Position;
		float vertices[3*8] = 
		{
			// Front square
			-0.5f, -0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f,
			0.5f, 0.5f, 0.5f,
			0.5, -0.5, 0.5,
			// Back square
			-0.5, -0.5, -0.5,
			-0.5,  0.5, -0.5,
			 0.5,  0.5, -0.5,
			 0.5, -0.5, -0.5,

		};
		unsigned int indices[3*2*6] =
		{
			// Front square
			0,1,2,
			0,3,2,
			// Right square
			3,2,7,
			3,6,7,
			// Back square
			4,5,6,
			4,7,6,
			// Left square
			0,1,5,
			0,4,5,
			// Upper square
			1,5,6,
			1,2,6,
			// Lower square
			0,4,7,
			0,3,7
		};

		unsigned int currentTexture;
		unsigned int textures[6];

		Cube(std::string* textures);

		void GenerateTexture(unsigned int* textures, std::string* textureArray, int renderType);
	};
}

#endif
