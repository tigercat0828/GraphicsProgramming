#pragma once
#include <glad/glad.h>

#include "VBO.h"

class VAO {
public:
	GLuint ID;
	VAO();

	void AttribPointer(const VBO& vbo, GLuint layout, int size, GLenum type, GLsizei stride, const void* offset) const;
	void AttribPointer(GLuint layout, int size, GLenum type, GLsizei stride, const void* offset) const;
	void Bind() const;
	void Unbind() const;
	void Delete() const;
};