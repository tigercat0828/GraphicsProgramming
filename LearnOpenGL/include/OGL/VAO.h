#pragma once
#include <glad/glad.h>

#include "VBO.h"

struct VAO {
public:
	GLuint ID;
	VAO();

	void AttribPointer(const VBO& vbo, GLuint layout, int size, GLenum type, GLsizei stride, const void* offset) const;
	void Bind() const;
	void UnBind() const;
	void Delete() const;
};