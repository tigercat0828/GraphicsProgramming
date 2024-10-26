#include "Debug.h"


void CheckError() {
	GLenum errorCode = glGetError();
	std::string error = "";
	if (errorCode != GL_NO_ERROR) {
		switch (errorCode) {
		case GL_INVALID_ENUM:		error = "INVAID_ENUM";			break;
		case GL_INVALID_VALUE:		error = "INVAID_VALUE";			break;
		case GL_INVALID_OPERATION:	error = "INVALID_OPERATION";	break;
		case GL_OUT_OF_MEMORY:		error = "OUT_OF_MEMORY";		break;
		default:					error = "UNKNOWN_ERROR";		break;
		}
		spdlog::error("{}", error);
		exit(-1);
	}
}


void PrintInfo() {
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	spdlog::info("Renderer: {}", reinterpret_cast<const char*>(renderer));
	spdlog::info("OpenGL version: {}", reinterpret_cast<const char*>(version));

	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	spdlog::info("Maximum vertex attributes : {}", nrAttributes);
}