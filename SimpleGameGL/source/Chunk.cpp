#include "../headers/Chunk.h"

Chunk::Chunk(int x, int z)
	: IB(nullptr), VB(nullptr), layout(nullptr), m_OriginX(x), m_OriginZ(z)
{
	initialiseBlocks();
}

Chunk::~Chunk() {
	delete IB;
}

void Chunk::GenerateMesh()
{
	int temp = 0;
	vertexData.clear();
	for (unsigned int i = 0; i < 16; i++) {
		for (unsigned int j = 0; j < 16; j++) {
			for (unsigned int k = 0; k < 256; k++) {
				if (blocks[i][j][k].type != BlockType::Air) {
					for (int face = 0; face < 6; face++) {
						if (isFaceVisible(i, j, k, face)) {
							for (const Vertex& v : blockVertexTemplate[face]) {
								vertexData.push_back(static_cast<float>(i) + static_cast<float>(m_OriginX) + v.x);
								vertexData.push_back(static_cast<float>(k) + v.y);
								vertexData.push_back(static_cast<float>(j) + static_cast<float>(m_OriginZ) + v.z);
								vertexData.push_back(v.u);
								vertexData.push_back(v.v);
								vertexData.push_back(static_cast<float>(blocks[i][j][k].type));
							}
							count++;
						}
					}
				}
			}
		}
	}
	VB = new VertexBuffer(vertexData);
	IB = new IndexBuffer(count); // Number of vertices
	VA = VertexArray();

	layout = new VertexBufferLayout();
	layout->Push<float>(3); //coordinates
	layout->Push<float>(2); //tex coords
	layout->Push<float>(1); //tex layer


	IB->Bind();

	VA.AddBuffer(*this->VB, *this->layout);
	VB->UnBind();
}

void Chunk::Draw() const
{
	VA.Bind();
	IB->Bind();

	glDrawElements(GL_TRIANGLES, 6 * count, GL_UNSIGNED_INT, nullptr);
}

bool Chunk::isFaceVisible(unsigned int i, unsigned int j, unsigned int k, unsigned int face) const
{
	int nx = i, ny = k, nz = j;
	switch (face)
	{
	case 0: nz--; break;//back face
	case 1: nz++; break;//front face
	case 2: ny--; break;//bottom face
	case 3: ny++; break;//top face
	case 4: nx--; break;//left face
	case 5: nx++; break;//right face
	}
	if (nx < 0 || nx >= 16 || nz < 0 || nz >= 16 || ny < 0 || ny >= 256) {
		return true; //face at chunk boundary is visible 
	}
	return blocks[nx][nz][ny].type == BlockType::Air;
}

void Chunk::initialiseBlocks()
{
	int temp = 0;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 256; k++) {
				if (temp % 2 == 0) {
					blocks[i][j][k].type = BlockType::Grass;
				}
				else {
					blocks[i][j][k].type = BlockType::Dirt;
				}
				temp++;
			}
		}
	}
}
