#include <glm/gtc/type_ptr.hpp>
#include "OGL/VBO.h"
#include "Debug.h"
VBO::VBO(float* data, GLsizeiptr size, GLenum usage) {
	GL_CALL(glGenBuffers(1, &ID));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, ID));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VBO::VBO(glm::vec3* data, GLsizeiptr size, GLenum usage)
{
	GL_CALL(glGenBuffers(1, &ID));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, ID));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VBO::SetData(float* data, GLsizeiptr size, GLenum usage)
{
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
}

void VBO::SetData(glm::vec3* data, GLsizeiptr size, GLenum usage)
{
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
}

void VBO::SubData(GLintptr start, GLsizeiptr size, float* data)
{
	GL_CALL(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
}
void VBO::SubData(GLintptr start, GLsizeiptr size, glm::vec3* data)
{
	GL_CALL(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
}


void VBO::Bind() const {
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, ID));
}

void VBO::Unbind() const {
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VBO::Delete() const {
	GL_CALL(glDeleteBuffers(1, &ID));
}
