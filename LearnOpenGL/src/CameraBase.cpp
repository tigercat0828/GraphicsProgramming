#include "CameraBase.h"

CameraBase::CameraBase(glm::vec3 position, float pitch, float yaw ) {

	this->yaw = yaw;
	this->pitch = pitch;

	front = glm::vec3(0, 0, -1);
	up = WORLD_UP;
	moveSpeed = 2.5;
	sensitivity = 0.1;
	zoom = 45;

	UpdateVectors();
}

glm::mat4 CameraBase::GetViewMatrix() const {
	return glm::lookAt(position, position + front, up);
}

glm::mat4 CameraBase::GetProjMatrix(float width, float height) const {
	return glm::perspective(glm::radians(zoom), width / height, 0.1f, 100.0f); // 100 is view distance
}

void CameraBase::Zoom(float yOffset) {
	zoom -= yOffset;
	if (zoom < 1.0) zoom = 1.0f;
	if (zoom > 45.0) zoom = 45.0f;
}

void CameraBase::Move(CAM_MOVEMENT move, float deltaTime) {
	float offset = moveSpeed * deltaTime;
	if (move == CAM_MOVEMENT::FORWARD) {
		position += front * offset;
	}
	if (move == CAM_MOVEMENT::BACKWARD) {
		position -= front * offset;
	}
	if (move == CAM_MOVEMENT::LEFT) {
		position -= right * offset;
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

void CameraBase::Turn(float xOffset, float yOffset) {

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	UpdateVectors();
}

void CameraBase::UpdateVectors() {
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, WORLD_UP));
	up = glm::normalize(glm::cross(right, this->front));
}
