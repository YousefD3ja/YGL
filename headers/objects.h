#ifndef OBJECTS_H
#define OBJECTS_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <shaderclass.h>
#include <buffers.h>
#include <vector>
#include <thread>
#include <windows.h>
#include <texture.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <camera.h>
#include <algorithm>

class Camera;


namespace ChunkTest
{
	

	enum blockTypes
	{
		GRASS,
		DIRT,
		WOOD,
		STONE,
	};

	class block
	{
	public:

		unsigned int ID;
		blockTypes type;
		glm::vec3 Position;

		glm::mat4 model;
		glm::mat4 chunkModel;

		bool IsSolid;
		bool isLoaded;

		bool renderFaces[6] = { true, true, true, true, true, true };

	};
	

	typedef struct chunk
	{
		unsigned int ID;
		unsigned int Priority;
		glm::vec3 Position;
		std::vector<block> blocks;
		std::vector<block*> renderedBlocks;
		float* ChunkVertices;
	}chunk_t;

	class Chunk
	{
	public:
		Chunk(glm::vec3 position);
		int Width=8, Height=8, Depth = 8;
		chunk_t chunk;
		void addChunk();
		void addChunkList(int count);

		static void setBlock(chunk_t* _chunk, blockTypes type, glm::vec3 position, bool IsSolid);

		static void checkSolidBlocks(block* _block, chunk_t* _chunk, std::vector<block*>* temp, Camera* player);

		static void checkThread(Chunk* testChunk, Camera* player);

		static void checkChunkThread(Chunk* Chunk, Camera* player);

		static void ChunkThread(Chunk* chunkList, Camera* camera);

		static void ChenkPriorityThread(Chunk* chunkList, Camera* player);

		static void SortingThread(Chunk* chunkList, Camera* player);

		

		std::vector<chunk_t> chunks;

		bool PriorityChecked;

		bool Rendered;

		bool loadedUpdated;
		std::vector<chunk_t*> tempLoaded;
		std::vector<chunk_t*> loadedChunks;

		std::vector<chunk_t*> tempV;
		bool SortedUpdated;
		std::vector<chunk_t*> sortedChunks;

		float ChunkVertices[6][5 * 4] = {
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
				-0.5f,-0.5f,-0.5f, 0.0f, 0.0f,
				-0.5f,-0.5f,0.5f, 0.0f, 1.0f,
				0.5f,-0.5f,0.5f, 1.0f, 1.0f,
				0.5f,-0.5f,-0.5f, 1.0f, 0.0f,
			}
		};

		unsigned int ChunkIndices[6] =
		{
			0,1,2,
			0,2,3
		};
	};
}


#endif
