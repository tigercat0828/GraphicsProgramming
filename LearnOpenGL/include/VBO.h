#pragma once
#include <glad/glad.h>

class VBO {

public:
	GLuint ID;
	VBO() {};
	VBO(float* data, GLsizeiptr size, GLenum usage);
	void Bind() const;
	void UnBind() const;
	void Delete() const;
};