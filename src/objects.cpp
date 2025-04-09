#include <objects.h>

ChunkTest::Chunk::Chunk(glm::vec3 position)
{
    //addChunk();
    addChunkList(50);
    /*
    chunk.ID = 0;
    chunk.Position = position;
    chunks.push_back(chunk);*/
}

void ChunkTest::Chunk::addChunk()
{
    chunk_t temp;
    if (chunks.size() > 0) temp = chunks.back();

    if (chunks.size() < 1)
    {
        chunk.ID = 0;
        chunk.Position = glm::vec3(0, 0, 0);
    }
    else {
        chunk.ID = temp.ID + 1;
        chunk.Position = glm::vec3(temp.Position.x + 16, 0, temp.Position.z + 16);
    }
    chunks.push_back(chunk);
}

void ChunkTest::Chunk::addChunkList(int count)
{

    chunk_t temp;

    glm::vec3 position;

    for (int i = -count / 2; i < count / 2; i++)
    {
        for (int j = -count / 2; j < count / 2; j++)
        {
            chunk_t tempchunk;
            position = glm::vec3(i*16,0.0f,j*16);
            tempchunk.Position = position;
            if (chunks.size() < 1)
            {
                tempchunk.ID = 0;
            }
            else {
                tempchunk.ID = chunks.back().ID + 1;
            }
            chunks.push_back(tempchunk);
            temp = chunks.back();
        }
    }
}

void ChunkTest::Chunk::setBlock(chunk_t* chunk, blockTypes type, glm::vec3 position, bool IsSolid)
{
    position.x = (int)position.x;
    position.y = (int)position.y;
    position.z = (int)position.z;

    if(chunk->blocks.size() == 0) 
    {
        block b;
        b.ID = 0;
        b.type = type;
        b.Position = position;
        b.IsSolid = IsSolid;
        chunk->blocks.push_back(b);
    }
    else 
    {
        block b;
        b.ID = chunk->blocks.back().ID+1;
        b.type = type;
        b.Position = position;
        b.IsSolid = IsSolid;
        chunk->blocks.push_back(b);
    }

}

void ChunkTest::Chunk::checkSolidBlocks(block* _block, chunk_t* _chunk, std::vector<block*>* temp, Camera* player)
{
    block* b;
    for (unsigned int i = 0; i < _chunk->blocks.size(); i++)
    {
        b = &_chunk->blocks.at(i);
        if ((_block->Position.x + 1 == b->Position.x))
        {
            if ((_block->Position.y == b->Position.y) && (_block->Position.z == b->Position.z))
            {
                _block->renderFaces[0] = false;
            }
        }
        if ((_block->Position.x - 1 == b->Position.x))
        {
            if ((_block->Position.y == b->Position.y) && (_block->Position.z == b->Position.z))
            {
                _block->renderFaces[1] = false;
            }
        }
        if ((_block->Position.y + 1 == b->Position.y))
        {
            if ((_block->Position.x == b->Position.x) && (_block->Position.z == b->Position.z))
            {
                _block->renderFaces[2] = false;
            }
        }
        if ((_block->Position.y - 1 == b->Position.y))
        {
            if ((_block->Position.x == b->Position.x) && (_block->Position.z == b->Position.z))
            {
                _block->renderFaces[3] = false;
            }
        }
        if ((_block->Position.z + 1 == b->Position.z))
        {
            if ((_block->Position.x == b->Position.x) && (_block->Position.y == b->Position.y))
            {
                _block->renderFaces[4] = false;
            }
        }
        if ((_block->Position.z - 1 == b->Position.z))
        {
            if ((_block->Position.x == b->Position.x) && (_block->Position.y == b->Position.y))
            {
                _block->renderFaces[5] = false;
            }
        }
    }
    for (unsigned int i = 0; i < 6; i++)
    {
		if (_block->renderFaces[i] == true)
		{
            bool blockInTemp = false;
            for (unsigned int j = 0; j < temp->size(); j++)
            {
                block* b = temp->at(j);
                if (_block->ID == b->ID)
                {
                    blockInTemp = true;
                }
            }
            if(blockInTemp == false)
            {
                temp->push_back(_block);
            }
		}
    }
    _block->isLoaded = true;
}

void ChunkTest::Chunk::ChunkThread(Chunk* chunkList, Camera* player)
{
    std::vector<chunk_t*> temp;
    while(true)
    {
        for (unsigned int c = 0; c < chunkList->chunks.size(); c++)
        {
            ChunkTest::chunk_t* ck = &chunkList->chunks.at(c);

            if (
                ((player->Position.x > player->Front.x) && (player->Position.x + 32 > ck->Position.x)) ||
                ((player->Position.x < player->Front.x) && (player->Position.x - 32 < ck->Position.x)) ||
                ((player->Position.z > player->Front.z) && (player->Position.z + 32 > ck->Position.z)) ||
                ((player->Position.z < player->Front.z) && (player->Position.z - 32 < ck->Position.z))
                )
            {
                temp.push_back(ck);
            }
        }
        chunkList->tempLoaded = temp;
        chunkList->loadedUpdated = true;
        temp.clear();
    }
}


void ChunkTest::Chunk::ChenkPriorityThread(Chunk* chunkList, Camera* player)
{
    std::vector<chunk_t*> copy;

    while(true)
    {
        if (chunkList->loadedUpdated)
        {
            chunkList->loadedChunks = chunkList->tempLoaded;
            chunkList->loadedUpdated = false;
        }
        copy = chunkList->loadedChunks;

        for (auto ck : copy)
        {
            if (
                (ck->Position.x < player->Position.x + 16) && (ck->Position.x > player->Position.x - 16) &&
                (ck->Position.z < player->Position.z + 16) && (ck->Position.z > player->Position.z - 16))
            {
                ck->Priority = 0;
            }
            else if (
                (ck->Position.x < player->Position.x + 32) && (ck->Position.x > player->Position.x - 32) &&
                (ck->Position.z < player->Position.z + 32) && (ck->Position.z > player->Position.z - 32)
            )
            {
                ck->Priority = 1;
            }
            else if (
                (ck->Position.x < player->Position.x + 64) && (ck->Position.x > player->Position.x - 64) &&
                (ck->Position.z < player->Position.z + 64) && (ck->Position.z > player->Position.z - 64)
            )
            {
                ck->Priority = 2;
            }
            else
            {
                ck->Priority = 4;
            }
        }
        chunkList->PriorityChecked = true;
    }
}

void ChunkTest::Chunk::SortingThread(Chunk* chunkList, Camera* player)
{
    std::vector<chunk_t*> temp;
    std::vector<chunk_t*> copy;
    while (true)
    {
        if(chunkList->PriorityChecked)
        {
            chunkList->PriorityChecked = false;
            copy = chunkList->loadedChunks;
            for (auto ck : copy)
            {
                if (ck->Priority < 2)
                {
                    temp.push_back(ck);
                }
            }
            copy.clear();
            if (temp.size() < 0) std::cout << "temp is empty" << std::endl;
            std::sort(temp.begin(), temp.end(), [](chunk_t* a, chunk_t* b) {return a->Priority < b->Priority; });
            chunkList->sortedChunks = temp;
            temp.clear();
            chunkList->SortedUpdated = true;
        }
    }
}


void ChunkTest::Chunk::checkChunkThread(Chunk* ChunkList, Camera* player)
{
    block* b;
    std::vector<block*> temp;
    std::vector<chunk_t*> copy;
    while(true)
    {
        copy = ChunkList->tempLoaded;
        for (chunk_t* ck : copy)
        {
            if (
                (ck->Position.x < player->Position.x + 64) && (ck->Position.x > player->Position.x - 64) &&
                (ck->Position.z < player->Position.z + 64) && (ck->Position.z > player->Position.z - 64)
            )
            {
                for (unsigned int i = 0; i < ck->blocks.size(); i++)
                {
                    b = &ck->blocks.at(i);

                    b->model = glm::mat4(1.0f);
                    b->chunkModel = glm::mat4(1.0f);

                    b->chunkModel = glm::translate(b->chunkModel, ck->Position);
                    b->model = glm::translate(b->model, b->Position);

                    checkSolidBlocks(b, ck, &temp, player);
                }
                ck->renderedBlocks = temp;
                temp.clear();
            }
        }
    }
}