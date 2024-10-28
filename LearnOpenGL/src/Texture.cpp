#pragma once
#include <filesystem>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include "Debug.h"
#include "Texture.h"
#include "stb_include.h"
Texture::Texture(const char* file) {

	std::filesystem::path filepath = std::filesystem::current_path() / "Assets" / "Textures" / file;
	std::string extension = filepath.extension().string();
	GLenum format = (extension == ".png") ? GL_RGBA : GL_RGB;

	GL_CALL(glGenTextures(1, &ID));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, ID));
	// set the texture wrapping parameters
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));	// set texture wrapping to GL_REPEAT (default wrapping method)
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	// set texture filtering parameters
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	spdlog::info("Loading texture {}", file);
	unsigned char* data = stbi_load(filepath.string().c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data));
		GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
	}
	else {
		spdlog::error("Fail to load texture {}", file);
	}
	stbi_image_free(data);
}

void Texture::Bind() const {
	GL_CALL(glBindTexture(GL_TEXTURE_2D, ID));
}

void Texture::UnBind() const {
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::Delete() const {
	GL_CALL(glDeleteTextures(1, &ID));
}

void Texture::AssignUnit(const Shader& shader, const char* uniform, int value) {
	shader.Use();
	shader.SetInt(uniform, value);
}
