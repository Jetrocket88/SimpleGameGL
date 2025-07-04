#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <vector>

class VertexBuffer {
private:
	unsigned int ID;

public:
	VertexBuffer(std::vector<float> vertices);
	void Bind() const;
	void UnBind() const;

};

