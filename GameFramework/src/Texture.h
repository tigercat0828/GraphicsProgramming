#pragma once
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <filesystem>
#include <spdlog/spdlog.h>
#include "Shader.h";

class Texture {
public:
	GLuint ID;
	int width;
	int height;
	int nrChannels;
	Texture(const char* file) {


		std::filesystem::path filepath = std::filesystem::current_path() / "Assets" / "Textures" / file;
		std::string extension = filepath.extension().string();
		GLenum format = (extension == ".png") ? GL_RGBA : GL_RGB;

		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		spdlog::info("Loading texture {}", file);
		unsigned char* data = stbi_load(filepath.string().c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			spdlog::error("Fail to load texture {}", file);
		}
		stbi_image_free(data);
	}
	void Bind() {
		glBindTexture(GL_TEXTURE_2D, ID);
	}
	void UnBind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Delete() {
		glDeleteTextures(1, &ID);
	}
	void AssignUnit(Shader& shader, const char* uniform, int value) {
		shader.Use();
		shader.SetInt(uniform, value);
	}
};