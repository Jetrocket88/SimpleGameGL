#include "../headers/Shader.h"

void Shader::checkCompilationStatus()
{
	int success;
	char infoLog[512];

	glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		exit(EXIT_FAILURE);
	}
	success = 0;
	glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Shader::checkLinkStatus() {
	int success;
	char infoLog[512];

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINKER::FAILED\n" << infoLog << std::endl;
		exit(EXIT_FAILURE);
	}
}

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
	std::ifstream vertexFile(vertexPath), fragmentFile(fragmentPath);
	std::string vertexSource, fragmentSource, line;

	//reading vertex file
	if (!vertexFile.is_open()) {
		std::cerr << "Failed to open vertex shader file" << std::endl;
		exit(EXIT_FAILURE);
	}
	while (getline(vertexFile, line)) {
		vertexSource += line + "\n";
	}
	vertexFile.close();

	//reading fragment file
	if (!fragmentFile.is_open()) {
		std::cerr << "Failed to open fragment shader file" << std::endl;
		exit(EXIT_FAILURE);
	}
	while (getline(fragmentFile, line)) {
		fragmentSource += line + "\n";
	}
	fragmentFile.close();

	vertexID = glCreateShader(GL_VERTEX_SHADER);
	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vertexSourceCStr = vertexSource.c_str();
	glShaderSource(vertexID, 1, &vertexSourceCStr, NULL);
	glCompileShader(vertexID);

	const char* fragmentSourceCStr = fragmentSource.c_str();
	glShaderSource(fragmentID, 1, &fragmentSourceCStr, NULL);
	glCompileShader(fragmentID);
	checkCompilationStatus();

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexID);
	glAttachShader(shaderProgram, fragmentID);
	glLinkProgram(shaderProgram);
	checkLinkStatus();

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);

	glUseProgram(shaderProgram);
}

void Shader::Use() const
{
	glUseProgram(shaderProgram);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::setMat4f(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec4f(const std::string& name, float value[4]) const
{
	glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), value[0], value[1], value[2], value[3]);
}

