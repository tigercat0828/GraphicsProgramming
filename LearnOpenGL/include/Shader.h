#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>
class Shader {
public:
	GLuint ID{0};
	std::string Name;
	Shader() = default;
	Shader(const char* vsFile, const char* fsFile);
	void Use() const;
	void Unuse() const;
	void SetBool(const char* name, bool value) const;
	void SetInt(const char* name, int value) const;
	void SetFloat(const char* name, float value) const;
	void SetVec2(const char* name, const glm::vec2 vec) const;
	void SetVec3(const char* name, const glm::vec3 vec) const;
	void SetVec4(const char* name, const glm::vec4 vec) const;
	void SetMat4(const char* name, const glm::mat4& mat) const;
	void Delete() const;
private:
	void CheckCompileError(GLuint ID, const std::string& type) const;
};