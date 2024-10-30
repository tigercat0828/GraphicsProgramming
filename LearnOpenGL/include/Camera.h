#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CAM_MOVEMENT {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
class Camera {
public:
	glm::vec3 position;
private:
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 WORLD_UP = glm::vec3(0, 1, 0);
	float yaw;
	float pitch;
	//float roll;

	float moveSpeed;
	float sensitivity;
	float zoom;
public:
	Camera(glm::vec3 position, float pitch = -30.0f, float yaw = -90.0f );
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjMatrix(float width, float height) const;
	void Zoom(float yOffset);
	void Move(CAM_MOVEMENT move, float deltaTime);
	void Turn(float xOffset , float yOffset);
private:
	void UpdateVectors();
};
