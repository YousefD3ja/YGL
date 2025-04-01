#ifndef OBJECTS_H
#define OBJECTS_H

#include <buffers.h>
#include <vector>
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

namespace Chunks1
{
	class Chunk
	{
	public:

		std::size_t Width = 8, Height = 8, Depth = 8;

		bool Blocks[16][16][16];

		float* VerticesF;

		std::vector<float> Vertices;

		void CheckChunk();

		void loadChunk();

		void loadVertices();
	};
}

namespace ChunkTest
	
{
	typedef enum blockTypes
	{
		GRASS,
		DIRT,
	};

	class block
	{
	public:
		unsigned int ID;
		blockTypes type;
		glm::vec3 Position;
		bool IsSolid;
		
		bool renderFaces[6] = {true, true, true, true, true, true};

		float facesVertices[6][5 * 4] = {
			{
				// front face
				0.5f,-0.5f,0.5f, 0.0f, 0.0f,
				0.5f,0.5f,0.5f, 0.0f, 1.0f,
				0.5f,0.5f,-0.5f, 1.0f, 1.0f,
				0.5f,-0.5f,-0.5f, 1.0f, 0.0f,
			},
			{
				// right face
				0.5f,-0.5f,-0.5f, 0.0f, 0.0f,
				0.5f,0.5f,-0.5f, 0.0f, 1.0f,
				-0.5f,0.5f,-0.5f, 1.0f, 1.0f,
				-0.5f,-0.5f,-0.5f, 1.0f, 0.0f,
			},
			{
				// back face
				-0.5f,-0.5f,-0.5f, 0.0f, 0.0f,
				-0.5f,0.5f,-0.5f, 0.0f, 1.0f,
				-0.5f,0.5f,0.5f, 1.0f, 1.0f,
				-0.5f,-0.5f,0.5f, 1.0f, 0.0f,
			},
			{
				// left face
				-0.5f,-0.5f,0.5f, 0.0f, 0.0f,
				-0.5f,0.5f,0.5f, 0.0f, 1.0f,
				0.5f,0.5f,0.5f, 1.0f, 1.0f,
				0.5f,-0.5f,0.5f, 1.0f, 0.0f,
			},
			{
				// upper face
				0.5f,0.5f,0.5f, 0.0f, 0.0f,
				-0.5f,0.5f,0.5f, 0.0f, 1.0f,
				-0.5f,0.5f,-0.5f, 1.0f, 1.0f,
				0.5f,0.5f,-0.5f, 1.0f, 0.0f,
			},
			{
				// bottom face
				0.5f,-0.5f,0.5f, 0.0f, 0.0f,
				-0.5f,-0.5f,0.5f, 0.0f, 1.0f,
				-0.5f,-0.5f,-0.5f, 1.0f, 1.0f,
				0.5f,-0.5f,-0.5f, 1.0f, 0.0f,
			} 
		};
		float facesIndices[6] =
		{
			0,1,2,
			0,2,3
		};

	};
	typedef struct chunk
	{
		unsigned int ID;
		glm::vec3 Position;
		std::vector<block> blocks;
		float* ChunkVertices;
		float facesVertices[6][5*4] =
		{
			{
				// front face
				0.5f,-0.5f,0.5f, 0.0f, 0.0f, //0
				0.5f,0.5f,0.5f, 0.0f, 1.0f, //1
				0.5f,0.5f,-0.5f, 1.0f, 1.0f, //2
				0.5f,-0.5f,-0.5f, 1.0f, 0.0f, //3
			},
			{
				// right face
				0.5f,-0.5f,-0.5f, 0.0f, 0.0f, //4
				0.5f,0.5f,-0.5f, 0.0f, 1.0f, //5
				-0.5f,0.5f,-0.5f, 1.0f, 1.0f, //6
				-0.5f,-0.5f,-0.5f, 1.0f, 0.0f, //7
			},
			{
				// back face
				-0.5f,-0.5f,-0.5f, 0.0f, 0.0f, //8
				-0.5f,0.5f,-0.5f, 0.0f, 1.0f, //9
				-0.5f,0.5f,0.5f, 1.0f, 1.0f, //10
				-0.5f,-0.5f,0.5f, 1.0f, 0.0f, //11
			},
			{
				// left face
				-0.5f,-0.5f,0.5f, 0.0f, 0.0f, //12
				-0.5f,0.5f,0.5f, 0.0f, 1.0f, //13
				0.5f,0.5f,0.5f, 1.0f, 1.0f, //14
				0.5f,-0.5f,0.5f, 1.0f, 0.0f, //15
			},
			{
				// upper face
				0.5f,0.5f,0.5f, 0.0f, 0.0f, //16
				-0.5f,0.5f,0.5f, 0.0f, 1.0f, //17
				-0.5f,0.5f,-0.5f, 1.0f, 1.0f, //18
				0.5f,0.5f,-0.5f, 1.0f, 0.0f, //19
			},
			{
				// bottom face
				0.5f,-0.5f,-0.5f, 1.0f, 0.0f, //23
				-0.5f,-0.5f,-0.5f, 1.0f, 1.0f, //22
				-0.5f,-0.5f,0.5f, 0.0f, 1.0f, //21
				0.5f,-0.5f,0.5f, 0.0f, 0.0f, //20
			}
		};
		unsigned int facesIndices[6] =
		{
			//front face
			0,1,2,
			0,2,3,
		};
	}chunk_t;

	class Chunk
	{
	public:
		Chunk(glm::vec3 position);
		int Width=8, Height=8, Depth = 8;
		chunk_t chunk;
		void addChunk();
		void addChunkList(unsigned int count);

		void setBlock(chunk_t& _chunk, blockTypes type, glm::vec3 position, bool IsSolid);

		void loadBlocks();

		void loadChunk(chunk_t& chunk);

		static void checkSolidBlocks(block* _block, chunk_t* _chunk);
		

		std::vector<chunk_t> chunks;
	};
}


#endif
