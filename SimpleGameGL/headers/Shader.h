#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <iostream>

class Shader
{
private:
	unsigned int vertexID, fragmentID, shaderProgram = 0;



	void checkCompilationStatus();
	void checkLinkStatus();

public:
	Shader(std::string vertexPath, std::string fragmentPath);
	void Use() const;

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4f(const std::string& name, glm::mat4 value) const;
	void setVec4f(const std::string& name, float value[4]) const;
};

