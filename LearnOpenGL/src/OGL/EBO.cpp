#include "OGL/EBO.h"
#include "Debug.h"

EBO::EBO(GLuint* data, GLsizeiptr size, GLenum usage) {
	GL_CALL(glGenBuffers(1, &ID));
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage));
}

void EBO::Bind() const {
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
}

void EBO::UnBind() const {
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void EBO::Delete() const {
	GL_CALL(glDeleteBuffers(1, &ID));
}
