#include "OGL/VBO.h"
#include "Debug.h"
VBO::VBO(float* data, GLsizeiptr size, GLenum usage) {

	GL_CALL(glGenBuffers(1, &ID));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, ID));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
}

void VBO::Bind() const {
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, ID));
}

void VBO::UnBind() const {
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VBO::Delete() const {
	GL_CALL(glDeleteBuffers(1, &ID));
}
