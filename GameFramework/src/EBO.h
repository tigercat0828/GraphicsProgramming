#pragma once
#include <glad/glad.h>
class EBO {
public:
	GLuint ID;
	EBO(GLuint* data, GLsizeiptr size, GLenum usage) {
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
	}
	void Bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}
	void UnBind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void Delete() {
		glDeleteBuffers(1, &ID);
	}
};