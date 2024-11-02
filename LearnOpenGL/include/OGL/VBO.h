#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
struct VBO {

public:
	GLuint ID{0};
	VBO() {};
	VBO(float* data, GLsizeiptr size, GLenum usage);
	VBO(glm::vec3* data, GLsizeiptr size, GLenum usage);
	void SetData(float* data, GLsizeiptr size, GLenum usage);
	void SetData(glm::vec3* data, GLsizeiptr size, GLenum usage);
	void SubData(GLintptr  start, GLsizeiptr size, float* data);
	void SubData(GLintptr  start, GLsizeiptr size, glm::vec3* data);
	void Bind() const;
	void Unbind() const;
	void Delete() const;
};