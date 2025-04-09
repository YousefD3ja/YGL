#include <Physics.h>

void Physics::Player::checkCurrentChunk(ChunkTest::Chunk* chunkList, Camera* player)
{
	while (true)
	{
		for (unsigned int i = 0; i < chunkList->chunks.size(); i++)
		{
			ChunkTest::chunk_t* ck = &chunkList->chunks.at(i);
			if (
				((player->Position.x < ck->Position.x + 8) && (player->Position.x > ck->Position.x - 8)) &&
				((player->Position.z < ck->Position.z + 8) && (player->Position.z > ck->Position.z - 8))
				)
			{
				player->currentChunk = ck;
			}
		}
	}
}

void Physics::Player::placeBlock(ChunkTest::Chunk* chunkList, ChunkTest::blockTypes type, Camera* player)
{
	ChunkTest::chunk_t* chunk = nullptr;

	for (unsigned int c = 0; c < chunkList->sortedChunks.size(); c++)
	{
		ChunkTest::chunk_t* ck = chunkList->sortedChunks.at(c);
		if (
			((player->placeableBlock.x <= ck->Position.x + 8) && (player->placeableBlock.x >= ck->Position.x - 8)) &&
			((player->placeableBlock.z <= ck->Position.z + 8) && (player->placeableBlock.z >= ck->Position.z - 8))
			)
		{
			chunk = ck;
			break;
		}
	}

	player->placeableBlock.x = (int)player->placeableBlock.x;
	player->placeableBlock.y = (int)player->placeableBlock.y;
	player->placeableBlock.z = (int)player->placeableBlock.z;

	std::cout << "BlockPos: " << player->placeableBlock.x << "," << player->placeableBlock.y << "," << player->placeableBlock.z << std::endl;

	if (chunk != nullptr)
	{

		for (auto b : chunk->blocks)
		{
			if(player->Position == b.Position)
			{
				if (player->Position.x > player->Front.x) player->placeableBlock.x = player->Position.x + 1;
				if (player->Position.y > player->Front.y) player->placeableBlock.y = player->Position.y + 1;
				if (player->Position.z > player->Front.z) player->placeableBlock.z = player->Position.z + 1;

				if (player->Position.x < player->Front.x) player->placeableBlock.x = player->Position.x - 1;
				if (player->Position.y < player->Front.y) player->placeableBlock.y = player->Position.y - 1;
				if (player->Position.z < player->Front.z) player->placeableBlock.z = player->Position.z - 1;
			}
		}

		ChunkTest::Chunk::setBlock(chunk, type, player->placeableBlock, true);
	}

	Sleep(200);
}

void Physics::Player::Process(ChunkTest::Chunk* chunkList, Camera* player)
{
	while (true)
	{
		if (player->placedBlock)
		{
			placeBlock(chunkList, player->currentBlock, player);

			player->placedBlock = false;
		}
	}
}

void Physics::Player::ProcessPlaceables(ChunkTest::Chunk* chunkList, Camera* player)
{
	ChunkTest::chunk_t* ck = nullptr;
	ChunkTest::block* bk = nullptr;
	while (true)
	{
		player->placeableBlock.x = player->Position.x + player->Front.x * player->range;
		player->placeableBlock.y = player->Position.y + player->Front.y * player->range;
		player->placeableBlock.z = player->Position.z + player->Front.z * player->range;

		/*player->placeableBlock.x = (int)player->placeableBlock.x;
		player->placeableBlock.y = (int)player->placeableBlock.y;
		player->placeableBlock.z = (int)player->placeableBlock.z;*/

		/*for (unsigned int b = 0; b < player->currentChunk->blocks.size(); b++)
		{
			bk = &player->currentChunk->blocks.at(b);
			if (player->Position == bk->Position)
			{
				if (player->Position.x > player->Front.x) player->placeableBlock.x = player->Position.x + 1;
				if (player->Position.y > player->Front.y) player->placeableBlock.y = player->Position.y + 1;
				if (player->Position.z > player->Front.z) player->placeableBlock.z = player->Position.z + 1;

				if (player->Position.x < player->Front.x) player->placeableBlock.x = player->Position.x - 1;
				if (player->Position.y < player->Front.y) player->placeableBlock.y = player->Position.y - 1;
				if (player->Position.z < player->Front.z) player->placeableBlock.z = player->Position.z - 1;
			}
		}*/
	}
}