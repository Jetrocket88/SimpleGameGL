#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <vector>

class IndexBuffer
{
public:

	IndexBuffer(unsigned int numCubes);

	void Bind() const;
	void UnBind() const;

	const unsigned int baseCubeIndices[36] = {
		0, 1, 2, 2, 3, 0, // Back face
		4, 5, 6, 6, 7, 4, // Front face
		4, 5, 1, 1, 0, 4, // Bottom face
		7, 6, 2, 2, 3, 7, // Top face
		4, 0, 3, 3, 7, 4, // Left face
		5, 1, 2, 2, 6, 5  // Right face
	};

	void generateData(const unsigned int numCubes);

private:
	std::vector<unsigned int> vecData;
	unsigned int ID;

};

