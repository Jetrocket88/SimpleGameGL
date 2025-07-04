#pragma once

#include <cstdint>
#include <vector>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "BlockFaceData.h"
#include "Texture.h"
#include "Shader.h"

enum class BlockType : uint8_t {
	Air, Grass, Dirt, Stone
};

struct Block {
	BlockType type = BlockType::Grass;
};

class Chunk
{
public:
	static const int m_Width = 16;
	static const int m_Height = 16;
	static const int m_Depth = 256;

	Block blocks[m_Width][m_Height][m_Depth];

	std::vector<float> vertexData;
	std::vector<unsigned int> indices;

	VertexArray VA;
	VertexBuffer* VB;
	IndexBuffer* IB;
	VertexBufferLayout* layout;


	Chunk();
	~Chunk();

	void GenerateMesh();
	void Draw();
	bool checkNeighbours(unsigned int i, unsigned int j, unsigned int k);
private:
};

