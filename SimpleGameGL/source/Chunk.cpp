#include "../headers/Chunk.h"

extern const float blockVertexTemplate[]; // 6 faces * 4 vertices * 5 floats

Chunk::Chunk()
	: IB(nullptr), VB(nullptr)
{
}

Chunk::~Chunk() {
	delete IB;
}

void Chunk::GenerateMesh()
{
	int count = 0;
	vertexData.clear();
	for (unsigned int i = 0; i < 16; i++) {
		for (unsigned int j = 0; j < 16; j++) {
			for (unsigned int k = 0; k < 256; k++) {
				if (blocks[i][j][k].type != BlockType::Air && checkNeighbours(i, j, k)) {
					// Each face: 4 vertices, each vertex: 5 floats (x, y, z, u, v)
					for (int face = 0; face < 6; ++face) {
						for (int vert = 0; vert < 4; ++vert) {
							int idx = (face * 4 + vert) * 5;
							// Offset the position floats (x, y, z)
							float x = blockVertexTemplate[idx + 0] + static_cast<float>(i);
							float y = blockVertexTemplate[idx + 1] + static_cast<float>(j);
							float z = blockVertexTemplate[idx + 2] + static_cast<float>(k);
							float u = blockVertexTemplate[idx + 3];
							float v = blockVertexTemplate[idx + 4];
							vertexData.push_back(x);
							vertexData.push_back(y);
							vertexData.push_back(z);
							vertexData.push_back(u);
							vertexData.push_back(v);
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
	layout->Push<float>(3);
	layout->Push<float>(2);


	IB->Bind();

	VA.AddBuffer(*this->VB, *this->layout);
	VB->UnBind();
}

void Chunk::Draw()
{
	VA.Bind();
	IB->Bind();

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
}

bool Chunk::checkNeighbours(unsigned int i, unsigned int j, unsigned int k)
{
	std::vector<std::vector<unsigned int>> adjCoords =
	{ {i, j, k + 1}, {i, j, k - 1}, {i, j + 1, k}, {i, j - 1, k}, {i + 1, j, k}, {i - 1, j, k}, };
	for (const auto coord : adjCoords) {
		if ((coord[0] > 16 || coord[0] < 0) || (coord[1] > 16 || coord[1] < 0) || (coord[2] > 256 || coord[2] < 0)) {
			//if any of these are true, then one of then they are out of bounds so we need to continue
			continue;
		}
		else {
			if (blocks[coord[0]][coord[1]][coord[2]].type == BlockType::Air) {
				return true;
				//if it returns true that means we need to draw it because it can be seen
			}
		}
	}
	return false;
}
