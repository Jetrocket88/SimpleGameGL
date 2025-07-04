#include <iostream>

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


Camera camera;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

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
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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
	glViewport(0, 0, 800, 600);
	//lets openGL know that this is the name of the callback funciton
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	std::vector<float> vertices = {
		// Back face (z = -0.5)
		-0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,// 0
		 0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,// 1
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,// 2
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,// 3
		// Front face (z = 0.5)
		-0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 1.0f, 1.0f,  0.0f, 0.0f,// 4
		 0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,// 5
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,// 6
		-0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f // 7
	};

	Texture t0("resources/textures/dumb.png", "png");

	VertexBuffer VB(vertices);
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(4);
	layout.Push<float>(2);
	VertexArray VA;

	IndexBuffer IB(1);
	IB.Bind();

	VA.AddBuffer(VB, layout);
	VB.UnBind();

	Shader shader("shaders/Vertex.vert", "shaders/Fragment.frag");
	shader.Use();
	shader.setInt("ourTexture", 0);

	Chunk c1;
	c1.GenerateMesh();

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glfwSetCursorPosCallback(window, mouse_callback);

		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0f, 0.2f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		shader.Use();

		camera.Render();
		shader.setMat4f("view", camera.GetView());

		glm::mat4 projection = glm::perspective(glm::radians(camera.GetFov()), 800.0f / 600.0f, 0.1f, 100.0f);
		shader.setMat4f("projection", projection);

		glm::mat4 model = glm::mat4(1.0f);
		shader.setMat4f("model", model);

		t0.Bind(0);
		VA.Bind();
		IB.Bind();

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

// FUNCTIONAL PROGRAMMING BING BAM BOOM PYTHON EASY BLYAT
// renderer
// add textures
