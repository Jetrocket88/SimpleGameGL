#include "../headers/IndexBuffer.h"

IndexBuffer::IndexBuffer(unsigned int numCubes)
{
	generateData(numCubes);
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vecData.size() * sizeof(unsigned int), vecData.data(), GL_STATIC_DRAW);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void IndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::generateData(const unsigned int numCubes)
{
	vecData.clear();
	vecData.reserve(numCubes * 36);
	for (unsigned int i = 0; i < numCubes; i++) {
		for (unsigned int j = 0; j < 36; j++) {
			vecData.push_back(baseCubeIndices[j] + (8 * i));
		}
	}
}

