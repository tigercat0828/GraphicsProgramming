#pragma once
#include "Shader.h"
class Texture {
public:
	GLuint ID;
	int width;
	int height;
	int nrChannels;
	Texture(const char* file);
	void Bind() const;
	void UnBind() const;
	void Delete() const;
	void AssignUnit(const Shader& shader, const char* uniform, int value);
};