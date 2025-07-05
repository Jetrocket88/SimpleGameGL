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
	Dirt, Grass, Air, Stone
};

struct Block {
	BlockType type;
};

class Chunk
{
public:
	static const int m_Width = 16;
	static const int m_Height = 16;
	static const int m_Depth = 256;
	int m_OriginX;
	int m_OriginZ;

	Block blocks[m_Width][m_Height][m_Depth];

	std::vector<float> vertexData;
	std::vector<unsigned int> indices;

	VertexArray VA;
	VertexBuffer* VB;
	IndexBuffer* IB;
	VertexBufferLayout* layout;
	int count = 0;


	Chunk(int x, int z);
	~Chunk();

	void GenerateMesh();
	void Draw() const;
private:
	bool isFaceVisible(unsigned int i, unsigned int j, unsigned int k, unsigned int face) const;
	void initialiseBlocks();
};

