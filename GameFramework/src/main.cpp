#pragma once
#include <iostream>
#include <SDL.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <spdlog/spdlog.h>
#include "Shader.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
using namespace glm;


int WindowWidth = 800;
int WindowHeight = 600;
int InitSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		spdlog::error("Fail to init SDL : {}", SDL_GetError());
		exit(-1);
	}
	else {
		spdlog::info("Success to init SDL");
	}
}

void PrintInfo() {
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);  
	spdlog::info("Renderer: {}", reinterpret_cast<const char*>(renderer));
	spdlog::info("OpenGL version: {}", reinterpret_cast<const char*>(version));

	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	spdlog::info("Maximum nr of vertex attributes supported : {}", nrAttributes);
}
int main(int argc, char** argv) {
	InitSDL();
	stbi_set_flip_vertically_on_load(true);
	// window creation
	SDL_Window* window = SDL_CreateWindow(
		"LearnOpenGL",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WindowWidth, WindowHeight,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!window) {
		spdlog::error("Fail to create SDL window");
		SDL_Quit();
		return -1;
	}
	else {
		spdlog::info("Success to create SDL window");
	}
	// craete OpenGL context and make it current
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GLContext GLcontext = SDL_GL_CreateContext(window);
	if (!GLcontext) {
		spdlog::error("Fail to create OpenGL context");
		return -1;
	}
	else {
		spdlog::info("Success to create OpenGL context");
	}
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		spdlog::error("Fail to init GLAD");
		SDL_GL_DeleteContext(GLcontext);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}
	PrintInfo();
	//====================================
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	VAO vao;
	vao.Bind();
	VBO vbo(vertices,sizeof(vertices), GL_STATIC_DRAW);
	EBO ebo(indices,sizeof(indices), GL_STATIC_DRAW);
	vao.AttribPointer(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao.AttribPointer(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.AttribPointer(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	vao.UnBind();
	vbo.UnBind();
	ebo.UnBind();


	Shader shader("Basic.vert", "Basic.frag");
	

	Texture texture1("wall.jpg");
	Texture texture2("awesomeface.png");
	
	shader.Use();
	texture1.AssignUnit(shader, "texture1", 0);
	texture2.AssignUnit(shader, "texture2", 1);


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glViewport(0, 0, WindowWidth, WindowHeight);
	bool isRunning = true;


	while (isRunning) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) isRunning = false;
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					isRunning = false;
				}
			}
		}
		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		mat4 modelMat = mat4(1.0);
		mat4 viewMat = mat4(1.0);
		mat4 projMat = mat4(1.0);

		modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));
		projMat = glm::perspective(glm::radians(45.0f), WindowWidth / (float)WindowHeight, 0.1f, 100.0f);


		shader.Use();
		shader.SetMat4("modelMat", modelMat);
		shader.SetMat4("viewMat", viewMat);
		shader.SetMat4("projMat", projMat);

		glActiveTexture(GL_TEXTURE0);
		texture1.Bind();
		glActiveTexture(GL_TEXTURE1);
		texture2.Bind();
		
		vao.Bind();
		shader.Use();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		

		SDL_GL_SwapWindow(window);
	}

	// clean up
	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	shader.Delete();

	SDL_GL_DeleteContext(GLcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;

}