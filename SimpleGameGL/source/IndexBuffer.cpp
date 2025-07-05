#include "../headers/IndexBuffer.h"

IndexBuffer::IndexBuffer(unsigned int numFaces)
{
	generateData(numFaces);
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

void IndexBuffer::generateData(const unsigned int numFaces)
{
	vecData.clear();
	vecData.reserve(numFaces * 6);
	for (unsigned int i = 0; i < numFaces; i++) {
		for (unsigned int j = 0; j < 6; j++) {
			vecData.push_back(baseFaceIndices[j] + i * 4);
		}
	}
}
