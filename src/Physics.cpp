#include <Physics.h>

void Physics::Player::checkCurrentChunk(ChunkManager::Chunk* chunkList, PlayerObject* player)
{
	while (true)
	{
		for (unsigned int i = 0; i < chunkList->chunks.size(); i++)
		{
			ChunkManager::chunk_t* ck = &chunkList->chunks.at(i);
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

void Physics::Player::placeBlock(ChunkManager::Chunk* chunkList, ChunkManager::blockTypes type, PlayerObject* player)
{
	ChunkManager::chunk_t* chunk = nullptr;

	for (unsigned int c = 0; c < chunkList->loadedChunks.size(); c++)
	{
		ChunkManager::chunk_t* ck = chunkList->loadedChunks.at(c);
		if (
			(((int)player->placeableBlock.x <= ck->Position.x + 8) && ((int)player->placeableBlock.x >= ck->Position.x - 8)) &&
			(((int)player->placeableBlock.z <= ck->Position.z + 8) && ((int)player->placeableBlock.z >= ck->Position.z - 8))
			)
		{
			chunk = ck;
			break;
		}
	}

	if (chunk != nullptr)
	{
		ChunkManager::block* tempBlock;
		bool emptyPos = true;

		for (unsigned int i = 0; i < chunk->blocks.size(); i++)
		{
			tempBlock = &chunk->blocks.at(i);

			if (tempBlock->Position == player->placeableBlock)
			{
				tempBlock->type = type;
				emptyPos = false;
			}
		}
		if(emptyPos)
		{
			ChunkManager::Chunk::setBlock(chunk, type, player->placeableBlock, true, true);
		}
	}
	Sleep(5);
}

void Physics::Player::DeleteBlocks(ChunkManager::Chunk* chunkList, PlayerObject* player)
{

	std::vector<ChunkManager::block> temp;
	std::vector<ChunkManager::block*> tempP;
	ChunkManager::block* b = nullptr;

	glm::vec3 pos = glm::vec3(1.0f);
	pos.x = (int)player->placeableBlock.x;
	pos.y = (int)player->placeableBlock.y;
	pos.z = (int)player->placeableBlock.z;

	ChunkManager::chunk_t* chunk = nullptr;
	for (auto c : chunkList->sortedChunks)
	{
		if (
			(((int)player->placeableBlock.x <= c->Position.x + 8) && ((int)player->placeableBlock.x >= c->Position.x - 8)) &&
			(((int)player->placeableBlock.z <= c->Position.z + 8) && ((int)player->placeableBlock.z >= c->Position.z - 8))
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
				if (b->Position != pos)
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
			ChunkManager::Chunk::checkSolidBlocks(b, chunk, new std::vector<ChunkManager::block*>, player);
		}
		chunk->blocks = temp;
		Sleep(5);
	}
}



void Physics::Player::Process(ChunkManager::Chunk* chunkList, PlayerObject* player)
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

void Physics::Player::ProcessPlaceables(ChunkManager::Chunk* chunkList, PlayerObject* player)
{
	ChunkManager::chunk_t* ck = nullptr;
	ChunkManager::block* bk = nullptr;
	while (true)
	{
		
		player->placeableBlock.x = (player->Position.x + player->Front.x * player->range);
		player->placeableBlock.y = (player->Position.y + player->Front.y * player->range);
		player->placeableBlock.z = (player->Position.z + player->Front.z * player->range);
		Sleep(5);
	}
}

void Engine::Physics::CalculateGravity(ChunkManager::Chunk* chunkList, PlayerObject player)
{

}