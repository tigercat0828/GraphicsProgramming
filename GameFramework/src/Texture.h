#pragma once
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <filesystem>
#include <spdlog/spdlog.h>

class Texture {
public:
	int ID;
	int width;
	int height;
	int nrChannels;
	Texture(const char* file) {
		std::filesystem::path filepath = std::filesystem::current_path() / "Assets" / "Textures" / file;
		std::string extension = filepath.extension().string();
		GLenum format = (extension == ".png") ? GL_RGBA : GL_RGB;
		unsigned char* data = stbi_load(filepath.string().c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			spdlog::info("Loading texture {}", file);
		}
		else {
			spdlog::error("Fail to load texture {}", file);
		}
		stbi_image_free(data);
	}
};