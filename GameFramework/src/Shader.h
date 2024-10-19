#pragma once
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <glm/glm.hpp>
class Shader {
public:
	GLuint ID;
	std::string Name;
	Shader(const char* vsFile, const char* fsFile) {
		// 獲取當前工作目錄並定位到 Assets 資料夾
		std::filesystem::path assetsPath = std::filesystem::current_path() / "Assets" / "Shaders";

		// 構建完整的著色器文件路徑
		std::filesystem::path vsPath = assetsPath / vsFile;
		std::filesystem::path fsPath = assetsPath / fsFile;

		Name = vsPath.stem().string();
		
		// v stand for vertex shader; f stand for fragment shader
		std::string vCode, fCode;
		std::ifstream vFile, fFile;
		vFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			vFile.open(vsPath);
			fFile.open(fsPath);
			std::stringstream vStream, fStream;

			vStream << vFile.rdbuf();
			fStream << fFile.rdbuf();

			vFile.close();
			fFile.close();

			vCode = vStream.str();
			fCode = fStream.str();
		}
		catch (std::ifstream::failure e) {
			spdlog::error("Fail to open shader files : {}", Name);
		}
		const char* vSource = vCode.c_str();
		const char* fSource = fCode.c_str();

		unsigned int vID, fID;
		int success;
		char infoLog[512];


		vID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vID, 1, &vSource, NULL);
		glCompileShader(vID);
		CheckError(vID, "VERTEX");

		fID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fID, 1, &fSource, NULL);
		glCompileShader(fID);
		CheckError(fID, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vID);
		glAttachShader(ID, fID);
		glLinkProgram(ID);
		CheckError(ID, "PROGRAM");

		glDeleteShader(vID);
		glDeleteShader(fID);


	}
	void Use() {
		glUseProgram(ID);
	}
	void SetBool(const char* name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name), value);
	}
	void SetInt(const char* name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name), value);
	}
	void SetFloat(const char* name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name), value);
	}
	void SetVec2(const char* name, const glm::vec2 vec) const {
		unsigned int uniLoc = glGetUniformLocation(ID, name);
		glUniform2fv(uniLoc, 1, &vec[0]);
	}
	void SetVec3(const char* name, const glm::vec3 vec) const {
		unsigned int uniLoc = glGetUniformLocation(ID, name);
		glUniform3fv(uniLoc, 1, &vec[0]);
	}
	void SetVec4(const char* name, const glm::vec4 vec) const {
		unsigned int uniLoc = glGetUniformLocation(ID, name);
		glUniform4fv(uniLoc, 1, &vec[0]);
	}
	void SetMat4(const char* name,const glm::mat4 &mat) const {
		unsigned int uniLoc = glGetUniformLocation(ID, name);
		glUniformMatrix4fv(uniLoc, 1, GL_FALSE, &mat[0][0]);
	}
	void Delete() const {
		glDeleteProgram(ID);
	}
private:
	void CheckError(unsigned int ID, const std::string& type) {
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


		
};