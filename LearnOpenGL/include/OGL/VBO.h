#pragma once
#include <glad/glad.h>

struct VBO {

public:
	GLuint ID{0};
	VBO() {};
	VBO(float* data, GLsizeiptr size, GLenum usage);
	void Bind() const;
	void UnBind() const;
	void Delete() const;
};