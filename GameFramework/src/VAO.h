#pragma once
#include <glad/glad.h>
#include "VBO.h"

class VAO {
public:
	GLuint ID;
	VAO() {
		glGenVertexArrays(1, &ID);
	}
	void AttribPointer(VBO& vbo, GLuint layout, int size, GLenum type, GLsizei stride, const void* offset) {
		vbo.Bind();
		glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
		vbo.UnBind();
	}
	void Bind() {
		glBindVertexArray(ID);
	}
	void UnBind() {
		glBindVertexArray(0);
	}
	void Delete() {
		glDeleteVertexArrays(1, &ID);
	}
};