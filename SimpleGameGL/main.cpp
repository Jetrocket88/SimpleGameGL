#include <iostream>
#include <chrono>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "headers/Shader.h"
#include "headers/VertexBuffer.h"
#include "headers/VertexArray.h"
#include "headers/IndexBuffer.h"
#include "headers/Camera.h"
#include "headers/Texture.h"
#include "headers/Chunk.h"
#include "headers/FPS.h"
#include "headers/TextureArray.h"

Camera camera;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

const unsigned int WindowX = 1200;
const unsigned int WindowY = 800;

//callback function for when the user resizes the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	camera.PollMouse(xpos, ypos);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	camera.ProcessInput(window, deltaTime);
}


int main() {
	//setting properties
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window object
	GLFWwindow* window = glfwCreateWindow(WindowX, WindowY, "LearnOpenGL", NULL, NULL);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//loading glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//veiwport: so OpenGL knows how we want to display the data and coordinates with respect to the window 
	glViewport(0, 0, WindowX, WindowY);
	//lets openGL know that this is the name of the callback funciton
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	FPS Fps;

	//Texture t0("resources/textures/blocks/dirt.png", "png");
	TextureArray ta("resources/textures/blocks");

	Shader shader("shaders/Vertex.vert", "shaders/Fragment.frag");
	shader.Use();

	Chunk c1(40, 0);
	Chunk c2(0, 0);
	c1.GenerateMesh();
	c2.GenerateMesh();

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glfwSetCursorPosCallback(window, mouse_callback);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glClearColor(0.0f, 0.2f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;
		Fps.Update();

		shader.Use();
		ta.Bind(shader);

		camera.Render();
		shader.setMat4f("view", camera.GetView());

		glm::mat4 projection = glm::perspective(glm::radians(camera.GetFov()), static_cast<float>(WindowX) / static_cast<float>(WindowY), 0.1f, 1000.0f);
		shader.setMat4f("projection", projection);

		glm::mat4 model = glm::mat4(1.0f);
		shader.setMat4f("model", model);

		c1.Draw();
		c2.Draw();

		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cerr << "OpenGL error: " << err << std::endl;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

// FUNCTIONAL PROGRAMMING BING BAM BOOM PYTHON EASY BLYAT
// renderer
// add textures
