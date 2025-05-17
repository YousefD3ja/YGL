#ifndef PHYSICS_H
#define PHYSICS_H
#include <objects.h>
#include <camera.h>

namespace Physics
{
	class Player
	{
	public:
		static void checkCurrentChunk(ChunkManager::Chunk* chunkList, PlayerObject* player);

		static void placeBlock(ChunkManager::Chunk* chunkList, ChunkManager::blockTypes type, PlayerObject* player);

		static void DeleteBlocks(ChunkManager::Chunk* chunkList, PlayerObject* player);

		static void Process(ChunkManager::Chunk* chunkList, PlayerObject* player);

		static void ProcessPlaceables(ChunkManager::Chunk* chunkList, PlayerObject* player);
	};
}

namespace Engine
{
	class Physics
	{
	public:
		void CalculateGravity(ChunkManager::Chunk* chunkList, PlayerObject player);
	};
}

#endif