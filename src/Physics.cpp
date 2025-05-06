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

	for (unsigned int c = 0; c < chunkList->loadedChunks.size(); c++)
	{
		ChunkTest::chunk_t* ck = chunkList->loadedChunks.at(c);
		if (
			((player->placeableBlock.x <= ck->Position.x + 8) && (player->placeableBlock.x >= ck->Position.x - 8)) &&
			((player->placeableBlock.z <= ck->Position.z + 8) && (player->placeableBlock.z >= ck->Position.z - 8))
			)
		{
			chunk = ck;
			break;
		}
	}

	if (chunk != nullptr)
	{
		ChunkTest::block* tempBlock;
		bool emptyPos = true;

		for (unsigned int i = 0; i < chunk->blocks.size(); i++)
		{
			tempBlock = &chunk->blocks.at(i);

			if (tempBlock->Position == player->placeableBlock)
			{
				emptyPos = false;
			}
		}
		if(emptyPos)
		{
			ChunkTest::Chunk::setBlock(chunk, type, player->placeableBlock, true, true);
		}
	}
	Sleep(5);
}

void Physics::Player::DeleteBlocks(ChunkTest::Chunk* chunkList, Camera* player)
{

	std::vector<ChunkTest::block> temp;
	std::vector<ChunkTest::block*> tempP;
	ChunkTest::block* b = nullptr;

	ChunkTest::chunk_t* chunk = nullptr;
	for (auto c : chunkList->sortedChunks)
	{
		if (
			((player->placeableBlock.x <= c->Position.x + 8) && (player->placeableBlock.x >= c->Position.x - 8)) &&
			((player->placeableBlock.z <= c->Position.z + 8) && (player->placeableBlock.z >= c->Position.z - 8))
			)
		{
			chunk = c;
			break;
		}
	}
	if (chunk != nullptr)
	{
		for (unsigned int i = 0; i < chunk->blocks.size(); i++)
		{
			b = &chunk->blocks.at(i);

			if(b != nullptr)
			{
				if (b->Position != player->placeableBlock)
				{
					temp.push_back(*b);
				}
				else
				{
					std::cout << "Deleting Block: " << b->Position.x << " " << b->Position.y << " " << b->Position.z << std::endl;
				}
			}
		}
		for (unsigned int i = 0; i < temp.size(); i++)
		{
			b = &temp.at(i);
			ChunkTest::Chunk::checkSolidBlocks(b, chunk, new std::vector<ChunkTest::block*>, player);
		}
		chunk->blocks = temp;
		Sleep(5);
	}
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
		if (player->deleteBlock)
		{
			DeleteBlocks(chunkList, player);
			player->deleteBlock = false;
		}
	}
}

void Physics::Player::ProcessPlaceables(ChunkTest::Chunk* chunkList, Camera* player)
{
	ChunkTest::chunk_t* ck = nullptr;
	ChunkTest::block* bk = nullptr;
	while (true)
	{
		player->placeableBlock.x = (int)(player->Position.x + player->Front.x * player->range);
		player->placeableBlock.y = (int)(player->Position.y + player->Front.y * player->range);
		player->placeableBlock.z = (int)(player->Position.z + player->Front.z * player->range);
	}
}