#pragma once
#include <glad/glad.h>

class EBO {
public:
	GLuint ID;
	EBO(GLuint* data, GLsizeiptr size, GLenum usage);
	void Bind() const;
	void UnBind() const;
	void Delete() const;
};