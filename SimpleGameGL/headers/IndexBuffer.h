#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <vector>

class IndexBuffer
{
public:

	IndexBuffer(unsigned int numFaces);

	void Bind() const;
	void UnBind() const;

	const unsigned int baseFaceIndices[6] = {
		0, 1, 2, 2, 3, 0
	};

	void generateData(const unsigned int numFaces);

private:
	std::vector<unsigned int> vecData;
	unsigned int ID;

};

