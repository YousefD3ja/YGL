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

	glm::vec3 blockPos;
	blockPos.x = cos(glm::radians(player->Yaw)) * cos(glm::radians(player->Pitch));
	blockPos.y = sin(glm::radians(player->Pitch));
	blockPos.z = sin(glm::radians(player->Yaw)) * cos(glm::radians(player->Pitch));

	glm::mat4 model = glm::mat4(1.0f);

	for (unsigned int c = 0; c < chunkList->chunks.size(); c++)
	{
		ChunkTest::chunk_t* ck = &chunkList->chunks.at(c);
		if (
			((blockPos.x < ck->Position.x + 8) && (blockPos.x > ck->Position.x - 8)) &&
			((blockPos.z < ck->Position.z + 8) && (blockPos.z > ck->Position.z - 8))
			)
		{
			//model = glm::translate(model, ck->Position);
			chunk = ck;
		}
	}

	glm::vec3 position = player->Position + blockPos;

	std::cout << "BlockPos: " << position.x << "," << position.y << "," << position.z << std::endl;

	if(chunk != nullptr)
	{
		ChunkTest::Chunk::setBlock(*chunk, type, player->Position + glm::normalize(blockPos), true);
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
	}
}