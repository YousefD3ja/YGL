#include <objects.h>




//Object::Cube::Cube(std::string* textures)
//{
//	if (textures != nullptr)
//	{
//	}
//}
//
//void Object::Cube::GenerateTexture(unsigned int* textures, std::string* textureArray, int renderType)
//{
//	if (textureArray != nullptr)
//	{
//		if (sizeof(textureArray) / sizeof(std::string) == 6)
//		{
//			glGenTextures(6, textures);
//			glActiveTexture(GL_TEXTURE0);
//			glBindTextures(0,6, textures);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, renderType);
//
//		}
//	}
//}
//
//void Chunks1::Chunk::CheckChunk()
//{
//	for (int x = 0; x < Chunk::Width; x++)
//	{
//		for (int y = 0; y < Chunk::Height; y++)
//		{
//			for (int z = 0; z < Chunk::Depth; z++)
//			{
//				Chunk::Blocks[x][y][z] = true;
//			}
//		}
//	}
//}

//void Chunks::Chunk::loadChunk()
//{
//	for (int i = 0; i < Chunk::Width; i++)
//	{
//		for (int j = 0;j < Chunk::Height; j++)
//		{
//			for (int k = 0; k < Chunk::Depth; k++)
//			{
//				if (i > 0 && Blocks[i - 1][j][k] == false)
//				{
//					Vertices.push_back(new float[5]{-0.5f, 0.5f, 0.5f, 0.0f, 0.0f });
//					Vertices.push_back(new float[5] {-0.5f,-0.5f, 0.5f, 1.0f, 0.0f });
//					Vertices.push_back(new float[5] {-0.5f,-0.5f,-0.5f, 1.0f, 1.0f });
//					Vertices.push_back(new float[5] {-0.5f, 0.5f,-0.5f, 0.0f, 1.0f });
//				}
//				if (j > 0 && Blocks[i][j - 1][k] == false)
//				{
//					Vertices.push_back(new float[5] {  0.5f,-0.5f, 0.5f, 0.0f, 0.0f });
//					Vertices.push_back(new float[5] { -0.5f,-0.5f, 0.5f, 1.0f, 0.0f });
//					Vertices.push_back(new float[5] { -0.5f,-0.5f,-0.5f, 1.0f, 1.0f });
//					Vertices.push_back(new float[5] {  0.5f,-0.5f,-0.5f, 0.0f, 1.0f });
//				}
//				if (k > 0 && Blocks[i][j][k - 1] == false)
//				{
//					Vertices.push_back(new float[5] {  0.5f, 0.5f,-0.5f, 0.0f, 0.0f });
//					Vertices.push_back(new float[5] { -0.5f, 0.5f,-0.5f, 1.0f, 0.0f });
//					Vertices.push_back(new float[5] { -0.5f,-0.5f,-0.5f, 1.0f, 1.0f });
//					Vertices.push_back(new float[5] {  0.5f,-0.5f,-0.5f, 0.0f, 1.0f });
//				}
//			}
//		}
//	}
//
//	for (int i = 0; i < sizeof(Vertices); i++)
//	{
//		VerticesF = Vertices.data();
//	}
//
//}


ChunkTest::Chunk::Chunk(glm::vec3 position)
{
    //addChunk();
    addChunkList(16);
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
    chunk_t tempchunk;

    glm::vec3 position;

    for (int i = -count / 2; i < count / 2; i++)
    {
        for (int j = -count / 2; j < count / 2; j++)
        {
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

void ChunkTest::Chunk::setBlock(chunk_t& chunk, blockTypes type, glm::vec3 position, bool IsSolid)
{
    if(chunk.blocks.size() == 0) 
    {
        block b;
        b.ID = 0;
        b.type = type;
        b.Position = position;
        b.IsSolid = IsSolid;
        chunk.blocks.push_back(b);
    }
    else 
    {
        block b;
        b.ID = chunk.blocks.back().ID+1;
        b.type = type;
        b.Position = position;
        b.IsSolid = IsSolid;
        chunk.blocks.push_back(b);
    }

}

void ChunkTest::Chunk::loadBlocks()
{
    for (unsigned int c = 0; c < chunks.size(); c++)
    {
        chunk_t& ck = chunks.at(c);
        for (unsigned int b = 0; b < ck.blocks.size(); b++)
        {
            block& bk = ck.blocks.at(b);
            for (int j = 0; j < 6; j++)
            {
                for (int i = 0; i < (sizeof(ChunkVertices[j]) / sizeof(float)); i += 5)
                {
                    glm::vec4 vertices = glm::vec4(ChunkVertices[j][i], ChunkVertices[j][(i)+1], ChunkVertices[j][(i)+2], 1.0f);
                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, bk.Position);
                    glm::vec3 temp = model * vertices;
                   /* bk.ChunkVertices[j][(i)+0] = temp.x;
                    bk.ChunkVertices[j][(i)+1] = temp.y;
                    bk.ChunkVertices[j][(i)+2] = temp.z;*/

                    std::cout << "";
                }
            }
        }
    }
}

void ChunkTest::Chunk::loadChunk(chunk_t& chunk)
{
    chunk.ChunkVertices = (float*)malloc(chunk.blocks.size() * (6 * (5 * 4)));
    for (unsigned int b = 0; b < chunk.blocks.size(); b++)
    {
        block& bk = chunk.blocks.at(b);
        for (int j = 0; j < 6; j++)
        {
            for (int i = 0; i < (sizeof(ChunkVertices[j]) / sizeof(float));i++)
            {
                //chunk.ChunkVertices[i] = bk.ChunkVertices[j][i];
                //std::cout <<chunk.ChunkVertices[i]<< ",";
                //std::cout << "i:" << i << ",j:" << j << std::endl;
            }
            for (int i = 0; i < (sizeof(chunk.ChunkVertices[i])); i += 5)
            {
                std::cout <<chunk.ChunkVertices[i]<< ",";
                std::cout <<chunk.ChunkVertices[i+1]<< ",";
                std::cout <<chunk.ChunkVertices[i+2]<< ",";
                std::cout <<chunk.ChunkVertices[i+3]<< ",";
                std::cout << chunk.ChunkVertices[i + 4] << "," << std::endl;;
            }
        }
    }
}

void ChunkTest::Chunk::checkSolidBlocks(block* _block, chunk_t* _chunk, std::vector<block*>* temp, Camera* player)
{
    block* b;

    bool rendered = false;

    for (unsigned int i = 0; i < _chunk->blocks.size(); i++)
    {
        b = &_chunk->blocks.at(i);
        if ((_block->Position.x + 1 == b->Position.x))
        {
            //_block->renderFaces[0] = true;
            if ((_block->Position.y == b->Position.y) && (_block->Position.z == b->Position.z))
            {
                _block->renderFaces[0] = false;
            }
            else if ((player->Position.x < player->Front.x) && (player->Position.x > _block->Position.x))
            {
                _block->renderFaces[0] = false;
            }
        }
        if ((_block->Position.x - 1 == b->Position.x))
        {
            //_block->renderFaces[1] = true;
            if ((_block->Position.y == b->Position.y) && (_block->Position.z == b->Position.z))
            {
                _block->renderFaces[1] = false;
            }
			else if ((player->Position.x > player->Front.x) && (player->Position.x < _block->Position.x))
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
            //_block->renderFaces[4] = true;
            if ((_block->Position.x == b->Position.x) && (_block->Position.y == b->Position.y))
            {
                _block->renderFaces[4] = false;
            }
            else if ((player->Position.z < player->Front.z) && (player->Position.z > _block->Position.z))
            {
                _block->renderFaces[4] = false;
            }
        }
        if ((_block->Position.z - 1 == b->Position.z))
        {
            //_block->renderFaces[5] = true;
            if ((_block->Position.x == b->Position.x) && (_block->Position.y == b->Position.y))
            {
                _block->renderFaces[5] = false;
            }
            else if ((player->Position.z > player->Front.z) && (player->Position.z < _block->Position.z))
            {
                _block->renderFaces[5] = false;
            }
        }
    }
    for (unsigned int i = 0; i < 6; i++)
    {
		if (_block->renderFaces[i] == true)
		{
            temp->push_back(_block);
            break;
		}
    }
    _block->isLoaded = true;
}

void ChunkTest::Chunk::thread(Chunk* testChunk, Camera* camera)
{
    while(true)
    {
        if(testChunk->chunks.size() > 0)
        {
            for (unsigned int c = 0; c < testChunk->chunks.size(); c++)
            {
                ChunkTest::chunk_t* ck = &testChunk->chunks.at(c);
                ChunkTest::block* b;

                std::vector<block*> temp;

                /*if (
                    (ck->Position.x < camera->Position.x + 16 && ck->Position.x > camera->Position.x - 16) &&
                    (ck->Position.z < camera->Position.z + 16 && ck->Position.z > camera->Position.z - 16)
                    )*/
                {
                    for (unsigned int i = 0; i < ck->blocks.size(); i++)
                    {
                        b = &ck->blocks.at(i);

                        b->model = glm::mat4(1.0f);
                        b->chunkModel = glm::mat4(1.0f);

                        b->chunkModel = glm::translate(b->chunkModel, ck->Position);
                        b->model = glm::translate(b->model, b->Position);

                        checkSolidBlocks(b, ck, &temp, camera);
                    }
                    
                    ck->renderedBlocks = temp;
                }
                temp.clear();
            }
        }
    }
}

void ChunkTest::Chunk::ChunkThread(Chunk* chunkList, Camera* camera)
{
    for (unsigned int c = 0; c < chunkList->chunks.size(); c++)
    {
        ChunkTest::chunk_t* ck = &chunkList->chunks.at(c);

        if (
            (camera->Position.x > camera->Front.x) && (camera->Position.x > ck->Position.x) ||
            (camera->Position.z > camera->Front.z) && (camera->Position.z > ck->Position.z) ||
            (camera->Position.x < camera->Front.x) && (camera->Position.x < ck->Position.x) ||
            (camera->Position.z < camera->Front.z) && (camera->Position.z < ck->Position.z)
            )
        {
            chunkList->loadedChunks.push_back(ck);

        }
    }
}

void ChunkTest::Chunk::checkThread(Chunk* testChunk, Camera* camera)
{
    for (unsigned int i = 0; i < testChunk->chunks.size(); i++)
    {
        std::thread ck(checkChunkThread, &testChunk->chunks.at(i), camera);
		ck.detach();
    }
}
void ChunkTest::Chunk::checkChunkThread(chunk_t* Chunk, Camera* player)
{
	while (true)
    {
        ChunkTest::block* b;

        std::vector<block*> temp;

        for (unsigned int i = 0; i < Chunk->blocks.size(); i++)
        {

            b = &Chunk->blocks.at(i);

            b->model = glm::mat4(1.0f);
            b->chunkModel = glm::mat4(1.0f);

            b->chunkModel = glm::translate(b->chunkModel, Chunk->Position);
            b->model = glm::translate(b->model, b->Position);

            checkSolidBlocks(b, Chunk, &temp, player);

        }

        Chunk->renderedBlocks = temp;

        temp.clear();
    }
}