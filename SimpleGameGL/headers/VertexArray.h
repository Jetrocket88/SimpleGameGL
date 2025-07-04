#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int ID;

public:
	VertexArray();

	void Bind() const;
	void UnBind() const;

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};

