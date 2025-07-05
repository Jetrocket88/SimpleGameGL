#include "../headers/Camera.h"

Camera::Camera()
{
}

void Camera::PollMouse(double xpos, double ypos) {
	if (firstMouse) {
		lastX = static_cast<float>(xpos);
		lastY = static_cast<float>(ypos);
		firstMouse = false;
	}
	float xoffset = static_cast<float>(xpos) - lastX;
	float yoffset = lastY - static_cast<float>(ypos);
	lastX = static_cast<float>(xpos);
	lastY = static_cast<float>(ypos);

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}

void Camera::Render()
{
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	const float radius = 10.0f;
	float camX = sin(static_cast<float>(glfwGetTime())) * radius;
	float camZ = cos(static_cast<float>(glfwGetTime())) * radius;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::ProcessInput(GLFWwindow* window, float deltaTime)
{
	currentSpeed = defaultSpeed * deltaTime; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		currentSpeed *= 2;
	}
	verticalSpeed = currentSpeed * 0.5f;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += currentSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= currentSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * currentSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * currentSpeed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		cameraPos += verticalSpeed * cameraUp;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cameraPos -= verticalSpeed * cameraUp;
}

glm::mat4 Camera::GetView() const
{
	return view;
}
float Camera::GetFov() const {
	return fov;
}
