#include <objects.h>




Object::Cube::Cube(std::string* textures)
{
	if (textures != nullptr)
	{
	}
}

void Object::Cube::GenerateTexture(unsigned int* textures, std::string* textureArray, int renderType)
{
	if (textureArray != nullptr)
	{
		if (sizeof(textureArray) / sizeof(std::string) == 6)
		{
			glGenTextures(6, textures);
			glActiveTexture(GL_TEXTURE0);
			glBindTextures(0,6, textures);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, renderType);

		}
	}
}

void Chunks1::Chunk::CheckChunk()
{
	for (int x = 0; x < Chunk::Width; x++)
	{
		for (int y = 0; y < Chunk::Height; y++)
		{
			for (int z = 0; z < Chunk::Depth; z++)
			{
				Chunk::Blocks[x][y][z] = true;
			}
		}
	}
}

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

void Chunks1::Chunk::loadChunk()
{
    for (int i = 0; i < Chunk::Width; i++)
    {
        for (int j = 0; j < Chunk::Height; j++)
        {
            for (int k = 0; k < Chunk::Depth; k++)
            {
                if (i > 0 && Blocks[i - 1][j][k] == false)
                {
                    Vertices.push_back(-0.5f-i);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(0.0f);

                    Vertices.push_back(-0.5f - i);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(0.0f);

                    Vertices.push_back(-0.5f - i);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(0.0f);

                    Vertices.push_back(-0.5f - i);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(0.0f);

                    Vertices.push_back(-0.5f - i);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(0.0f);

                    Vertices.push_back(0.5f - i);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(1.0f);

                    /*Vertices.push_back({-0.5f, 0.5f, 0.5f, 0.0f, 0.0f });
                    Vertices.push_back({-0.5f,-0.5f, 0.5f, 1.0f, 0.0f });
                    Vertices.push_back({-0.5f,-0.5f, 0.5f, 1.0f, 0.0f });
                    Vertices.push_back({-0.5f, 0.5f,-0.5f, 0.0f, 1.0f });*/
                }
                if (j > 0 && Blocks[i][j - 1][k] == false)
                {
                    Vertices.push_back(0.5f);
                    Vertices.push_back(-0.5f - j);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(0.0f);

                    Vertices.push_back(-0.5f);
                    Vertices.push_back(-0.5f - j);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(0.0f);

                    Vertices.push_back(-0.5f);
                    Vertices.push_back(-0.5f - j);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(1.0f);

                    Vertices.push_back(0.5f);
                    Vertices.push_back(-0.5f - j);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(0.0f);

                    Vertices.push_back(-0.5f);
                    Vertices.push_back(-0.5f - j);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(1.0f);

                    Vertices.push_back(0.5f);
                    Vertices.push_back(-0.5f - j);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(1.0f);
                    /*Vertices.push_back({  0.5f,-0.5f, 0.5f, 0.0f, 0.0f });
                    Vertices.push_back({ -0.5f,-0.5f, 0.5f, 1.0f, 0.0f });
                    Vertices.push_back({ -0.5f,-0.5f,-0.5f, 1.0f, 1.0f });
                    Vertices.push_back({  0.5f,-0.5f,-0.5f, 0.0f, 1.0f });*/
                }
                if (k > 0 && Blocks[i][j][k - 1] == false)
                {
                    Vertices.push_back(0.5f);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(-0.5f - k);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(0.0f);

                    Vertices.push_back(-0.5f);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(-0.5f - k);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(0.0f);

                    Vertices.push_back(-0.5f);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(-0.5f - k);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(1.0f);

                    Vertices.push_back(0.5f);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(-0.5f - k);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(0.0f);

                    Vertices.push_back(-0.5f);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(-0.5f - k);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(1.0f);

                    Vertices.push_back(0.5f);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(-0.5f - k);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(1.0f);

                    /*Vertices.push_back({  0.5f, 0.5f,-0.5f, 0.0f, 0.0f });
                    Vertices.push_back({ -0.5f, 0.5f,-0.5f, 1.0f, 0.0f });
                    Vertices.push_back({ -0.5f,-0.5f,-0.5f, 1.0f, 1.0f });
                    Vertices.push_back({  0.5f,-0.5f,-0.5f, 0.0f, 1.0f });*/
                }

                if (i < Width && Blocks[i + 1][j][k] == false)
                {
                    Vertices.push_back(-0.5f + i);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(-0.5f + i);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(-0.5f + i);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(-0.5f + i);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(-0.5f + i);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(0.5f + i);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(1.0f);
                }

                if (j < Height && Blocks[i][j + 1][k] == false)
                {
                    Vertices.push_back(0.5f);
                    Vertices.push_back(-0.5f + j);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(-0.5f + j);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(-0.5f + j);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(-0.5f + j);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(-0.5f + j);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(-0.5f + j);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(1.0f);
                }

                if (k < Depth && Blocks[i][j][k + 1] == false)
                {
                    Vertices.push_back(0.5f);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(-0.5f + k);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(-0.5f + k);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(-0.5f + k);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(-0.5f + k);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(-0.5f + k);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(1.0f);
                    Vertices.push_back(0.5f);
                    Vertices.push_back(-0.5f);
                    Vertices.push_back(-0.5f + k);
                    Vertices.push_back(0.0f);
                    Vertices.push_back(1.0f);
                }

            }
        }
    }
}

void Chunks1::Chunk::loadVertices()
{
    VerticesF = Vertices.data();
}

ChunkTest::Chunk::Chunk(glm::vec3 position)
{
    chunk.ID = 0;
    chunk.Position = position;
    chunks.push_back(chunk);
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

void ChunkTest::Chunk::addChunkList(unsigned int count)
{

    chunk_t temp;
    if (chunks.size() > 0) temp = chunks.back();
    for (int i = 0; i < count; i++)
    {
        if (i % 2 == 0)
        {
            if (chunks.size() < 1)
            {
                chunk.ID = 0;
            }
            else {
                chunk.ID = temp.ID + 1;
            }
            chunk.Position = glm::vec3(temp.Position.x + 16, 0, temp.Position.z);
            chunks.push_back(chunk);
        }
        else
        {
            if (chunks.size() < 1)
            {
                chunk.ID = 0;
            }
            else {
                chunk.ID = temp.ID + 1;
            }
            chunk.Position = glm::vec3(temp.Position.x, 0, temp.Position.z + 16);
            chunks.push_back(chunk);
        }
        temp = chunks.back();
    }
}

void ChunkTest::Chunk::setBlock(chunk_t& chunk, blockTypes type, glm::vec3 position, bool IsSolid)
{
    if(chunk.blocks.size() == 0) 
    {
        chunk.blocks.push_back(block{ 0, type, position, IsSolid });
    }
    else 
    {
        chunk.blocks.push_back(block{ chunk.blocks.back().ID + 1, type, position, IsSolid });
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
                for (int i = 0; i < (sizeof(chunks.at(c).blocks.at(b).facesVertices[j]) / sizeof(float)); i += 5)
                {
                    glm::vec4 vertices = glm::vec4(bk.facesVertices[j][(i)], bk.facesVertices[j][(i)+1], bk.facesVertices[j][(i) + 2],1.0f);
                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, bk.Position);
                    glm::vec3 temp = model * vertices;
                    bk.facesVertices[j][(i)+0] = temp.x;
                    bk.facesVertices[j][(i)+1] = temp.y;
                    bk.facesVertices[j][(i)+2] = temp.z;

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
            for (int i = 0; i < (sizeof(chunk.blocks.at(b).facesVertices[j]) / sizeof(float));i++)
            {
                chunk.ChunkVertices[i] = bk.facesVertices[j][i];
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

void ChunkTest::Chunk::checkSolidBlocks(block* _block, chunk_t* _chunk)
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
        if((_block->Position.x - 1 == b->Position.x))
        {
            if ((_block->Position.y == b->Position.y) && (_block->Position.z == b->Position.z))
            {
                _block->renderFaces[1] = false;
            }
        }
        if((_block->Position.y + 1 == b->Position.y))
        {
            if ((_block->Position.x == b->Position.x) && (_block->Position.z == b->Position.z))
            {
                _block->renderFaces[2] = false;
            }
        }
        if((_block->Position.y - 1 == b->Position.y))
        {
            if ((_block->Position.x == b->Position.x) && (_block->Position.z == b->Position.z))
            {
                _block->renderFaces[3] = false;
            }
        }
        if((_block->Position.z + 1 == b->Position.z))
        {
            if ((_block->Position.x == b->Position.x) && (_block->Position.y == b->Position.y))
            {
                    _block->renderFaces[4] = false;
            }
        }
        if((_block->Position.z - 1 == b->Position.z))
        {
            if ((_block->Position.x == b->Position.x) && (_block->Position.y == b->Position.y))
            {
                _block->renderFaces[5] = false;
            }
        }
    }
}