#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../vendor/stb_image.h"

#include "Shader.h"

#include <iostream>
#include <string>

class TextureArray
{
private:
	unsigned int ID;

	const int m_Width = 16;
	const int m_Height = 16;
	static constexpr const char* blockNames[2] = { "grass", "dirt" };
	const unsigned int numTextures = sizeof(blockNames) / sizeof(blockNames[0]);

public:
	TextureArray(std::string path);
	void Bind(const Shader& shader) const;
};

