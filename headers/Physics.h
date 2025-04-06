#ifndef PHYSICS_H
#define PHYSICS_H
#include <objects.h>
#include <camera.h>

namespace Physics
{
	class Player
	{
	public:
		static void checkCurrentChunk(ChunkTest::Chunk* chunkList, Camera* player);

		static void placeBlock(ChunkTest::Chunk* chunkList, ChunkTest::blockTypes type, Camera* player);

		static void Process(ChunkTest::Chunk* chunkList, Camera* player);

	};
}
#endif