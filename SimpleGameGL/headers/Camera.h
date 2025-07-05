#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:

	Camera();
	void PollMouse(double xpos, double ypos);
	void Render();
	void ProcessInput(GLFWwindow* window, float deltaTime);
	glm::mat4 GetView() const;
	float GetFov() const;

	float defaultSpeed = 20.0f;
	float currentSpeed, verticalSpeed;


private:

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view;

	bool firstMouse = true;
	float lastX = 400.0f, lastY = 300.0f;
	float yaw = -90.0f;
	float pitch = 0.0f;
	float fov = 45.0f;
};

