#include "OGL/VAO.h"
#include "Debug.h"
VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

void VAO::AttribPointer(const VBO& vbo, GLuint layout, int size, GLenum type, GLsizei stride, const void* offset) const {
	vbo.Bind();
	GL_CALL(glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset));
	GL_CALL(glEnableVertexAttribArray(layout));
	vbo.UnBind();
}
void VAO::Bind() const {
	GL_CALL(glBindVertexArray(ID));
}

void VAO::UnBind() const {
	GL_CALL(glBindVertexArray(0));
}

void VAO::Delete() const {
	GL_CALL(glDeleteVertexArrays(1, &ID));
}
