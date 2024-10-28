#pragma once
#include <glm/glm.hpp>
#include <ostream>
struct Transform {
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	Transform() = default;
	Transform(glm::vec3 position, glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1)) : position(position), rotation(rotation), scale(scale) {}
};