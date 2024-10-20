#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
enum CAM_MOVEMENT {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
class Camera {
private:
	
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
	Camera(glm::vec3 position, float yaw=-90.0f, float pitch=0.0f) {

		this->yaw = yaw;
		this->pitch = pitch;

		front = glm::vec3(0, 0, -1);
		up = WORLD_UP;
		moveSpeed = 2.5;
		sensitivity = 0.1;
		zoom = 45;

		UpdateVectors();
	}
	glm::mat4 GetViewMatrix() const {
		return glm::lookAt(position, position + front, up);
	}
	glm::mat4 GetProjMatrix(float width, float height) const {
		return glm::perspective(glm::radians(zoom),width/height, 0.1f, 100.0f); // 100 is view distance
	}
	void Zoom(float yOffset) {
		zoom -= yOffset;
		if (zoom < 1.0) zoom = 1.0f;
		if (zoom > 45.0) zoom = 45.0f;
	}
	void Move(CAM_MOVEMENT move, float deltaTime) {
		float offset = moveSpeed * deltaTime;
		if (move == CAM_MOVEMENT::FORWARD) {
			position += front * offset;
		}
		if (move == CAM_MOVEMENT::BACKWARD) {
			position -= front * offset;
		}
		if (move == CAM_MOVEMENT::LEFT) {
			position -= right* offset;
		}
		if (move == CAM_MOVEMENT::RIGHT) {
			position += right * offset;
		}
		if (move == CAM_MOVEMENT::UP) {
			position += up * offset;
		}
		if (move == CAM_MOVEMENT::DOWN) {
			position -= up * offset;
		}
	}
	void Turn(float xOffset , float yOffset) {

		xOffset *= sensitivity;
		yOffset *= sensitivity;

		yaw += xOffset;
		pitch += yOffset;  

		if (pitch > 89.0f) {
			pitch= 89.0f;
		}
		if (pitch < -89.0f) {
			pitch = -89.0f;
		}
		//std::cout << "pitch  " << pitch << std::endl;
		//std::cout << "yaw  " << yaw << std::endl;


	
		UpdateVectors();
	}
private:
	void UpdateVectors() {
		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		this->front = glm::normalize(front);

		right = glm::normalize(glm::cross(front, WORLD_UP));
		up = glm::normalize(glm::cross(right, this->front));
	}
	
};
