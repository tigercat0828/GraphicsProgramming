#include <filesystem>
#include <fstream>
#include <sstream>
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include "Shader.h"
#include "Debug.h"

Shader::Shader(const char* vertex_shader, const char* fragment_shader) {
	// 獲取當前工作目錄並定位到 Assets 資料夾
	std::filesystem::path assetsPath = std::filesystem::current_path() / "Assets" / "Shaders";

	// 構建完整的著色器文件路徑
	std::filesystem::path vsPath = assetsPath / vertex_shader;
	std::filesystem::path fsPath = assetsPath / fragment_shader;

	Name = vsPath.stem().string();

	// v stand for vertex shader; f stand for fragment shader
	std::string vsCode, fsCode;
	std::ifstream vsFile, fsFile;
	vsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vsFile.open(vsPath);
		fsFile.open(fsPath);
		std::stringstream vStream, fStream;

		vStream << vsFile.rdbuf();
		fStream << fsFile.rdbuf();

		vsFile.close();
		fsFile.close();

		vsCode = vStream.str();
		fsCode = fStream.str();
	}
	catch (std::ifstream::failure &e) {
		spdlog::error("Fail to open shader files : {}", Name);
		spdlog::error("{}", e.what());
	}
	const char* vSource = vsCode.c_str();
	const char* fSource = fsCode.c_str();

	GLuint vID, fID;
	int success;
	char infoLog[512];


	vID = GL_CALL(glCreateShader(GL_VERTEX_SHADER));
	GL_CALL(glShaderSource(vID, 1, &vSource, NULL));
	GL_CALL(glCompileShader(vID));
	CheckCompileError(vID, "VERTEX");

	fID = GL_CALL(glCreateShader(GL_FRAGMENT_SHADER));
	GL_CALL(glShaderSource(fID, 1, &fSource, NULL));
	GL_CALL(glCompileShader(fID));
	CheckCompileError(fID, "FRAGMENT");

	ID = GL_CALL(glCreateProgram());
	GL_CALL(glAttachShader(ID, vID));
	GL_CALL(glAttachShader(ID, fID));
	GL_CALL(glLinkProgram(ID));
	CheckCompileError(ID, "PROGRAM");

	GL_CALL(glDeleteShader(vID));
	GL_CALL(glDeleteShader(fID));
}
void Shader::Use() const {
	GL_CALL(glUseProgram(ID));
}

void Shader::Unuse() const {
	GL_CALL(glUseProgram(0));
}

void Shader::SetBool(const char* name, bool value) const {
	GLuint uniform = GL_CALL(glGetUniformLocation(ID, name));
	GL_CALL(glUniform1i(uniform, value));
}

void Shader::SetInt(const char* name, int value) const {
	GLuint uniform = GL_CALL(glGetUniformLocation(ID, name));
	GL_CALL(glUniform1i(uniform, value));
}

void Shader::SetFloat(const char* name, float value) const {
	GLuint uniform = GL_CALL(glGetUniformLocation(ID, name));
	GL_CALL(glUniform1f(uniform, value));
}

void Shader::SetVec2(const char* name, const glm::vec2 vec) const {
	GLuint uniform = GL_CALL(glGetUniformLocation(ID, name));
	GL_CALL(glUniform2fv(uniform, 1, &vec[0]));
}

void Shader::SetVec3(const char* name, const glm::vec3 vec) const {
	GLuint uniform = GL_CALL(glGetUniformLocation(ID, name));
	GL_CALL(glUniform3fv(uniform, 1, &vec[0]));
}

void Shader::SetVec4(const char* name, const glm::vec4 vec) const {
	GLuint uniform = GL_CALL(glGetUniformLocation(ID, name));
	GL_CALL(glUniform4fv(uniform, 1, &vec[0]));
}

void Shader::SetMat4(const char* name, const glm::mat4& mat) const {
	GLuint uniform = GL_CALL(glGetUniformLocation(ID, name));
	GL_CALL(glUniformMatrix4fv(uniform, 1, GL_FALSE, &mat[0][0]));
}

void Shader::Delete() const {
	GL_CALL(glDeleteProgram(ID));
}

void Shader::CheckCompileError(GLuint ID, const std::string& type) const {
	int success;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(ID, 1024, NULL, infoLog);
			spdlog::warn("Fail to compile \"{}\" {} shader ID {} : {}", Name, type, ID, infoLog);
		}
		else {
			spdlog::info("Success to compile \"{}\" {} shader ID {}", Name, type, ID);
		}
	}
	else {
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 1024, NULL, infoLog);
			spdlog::warn("Fail to link \"{}\" shader program ID {} : {}", Name, ID, infoLog);
		}
		else {
			spdlog::info("Success to link \"{}\" shader program ID {}", Name, ID);
		}
	}
}

