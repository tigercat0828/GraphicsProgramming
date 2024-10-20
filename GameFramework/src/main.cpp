#pragma once
#include <iostream>
#include <SDL.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"
#include "Window.h"
using namespace std;
using namespace glm;


int WindowWidth = 800;
int WindowHeight = 600;


float DeltaTime = 0.0f;
float LastFrame = 0.0f;

Camera camera(vec3(0, 0, -3),0,-90);
bool isRunning = true;

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
void processKeyboardInput(const Uint8* state, float deltaTime) {
	if (state[SDL_SCANCODE_W]) {
		camera.Move(FORWARD, deltaTime);
	}
	if (state[SDL_SCANCODE_S]) {
		camera.Move(BACKWARD, deltaTime);
	}
	if (state[SDL_SCANCODE_A]) {
		camera.Move(LEFT, deltaTime);
	}
	if (state[SDL_SCANCODE_D]) {
		camera.Move(RIGHT, deltaTime);
	}
	if (state[SDL_SCANCODE_LSHIFT]) {
		camera.Move(DOWN, deltaTime);
	}
	if (state[SDL_SCANCODE_SPACE]) {
		camera.Move(UP, deltaTime);
	}
}

void processMouseInput(SDL_Event& event) {

	if (event.type == SDL_MOUSEMOTION) {
		float mx = event.motion.xrel;
		float my = event.motion.yrel;
		camera.Turn(mx, -my);
	}
}

void ProcessInput(SDL_Window* window, float deltaTime) {
	SDL_Event event;
	const Uint8* state = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit(0);
		}
		else if (event.type == SDL_KEYDOWN) {
			// 可以在這裡添加其他鍵盤事件處理
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
			}
		}
		processMouseInput(event);
	}
	processKeyboardInput(state, deltaTime);
}



Window mainWin;
int main(int argc, char** argv) {

	
	InitSDL();
	stbi_set_flip_vertically_on_load(true);
	// window creation
	
	// craete OpenGL context and make it current
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	mainWin = Window("LearnOpenGL", 800, 600);
	
	if (!mainWin.Instance) {
		spdlog::error("Fail to create SDL window");
		SDL_Quit();
		return -1;
	}
	else {
		spdlog::info("Success to create SDL window");
	}
	
	SDL_GLContext GLcontext = SDL_GL_CreateContext(mainWin.Instance);
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
		SDL_DestroyWindow(mainWin.Instance);
		SDL_Quit();
		return -1;
	}
	PrintInfo();

	 glEnable(GL_DEPTH_TEST);
	//====================================
	float vertices[] = {
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};

	VAO vao;
	vao.Bind();
	VBO vbo(vertices,sizeof(vertices), GL_STATIC_DRAW);
	vao.AttribPointer(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	vao.AttribPointer(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	
	vao.UnBind();
	vbo.UnBind();

	Shader shader("Basic.vert", "Basic.frag");
	

	Texture texture1("wall.jpg");
	Texture texture2("awesomeface.png");
	
	shader.Use();
	texture1.AssignUnit(shader, "texture1", 0);
	texture2.AssignUnit(shader, "texture2", 1);


	glViewport(0, 0, WindowWidth, WindowHeight);
	
	SDL_WarpMouseInWindow(mainWin.Instance, mainWin.Width, mainWin.Height);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	while (isRunning) {
		float currentFrame = SDL_GetTicks() / 1000.0f;
		DeltaTime = currentFrame - LastFrame;
		LastFrame = currentFrame;

		ProcessInput(mainWin.Instance, DeltaTime);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mat4 modelMat = mat4(1.0);
		mat4 viewMat = mat4(1.0);
		mat4 projMat = mat4(1.0);

		shader.Use();
		glActiveTexture(GL_TEXTURE0);
		texture1.Bind();
		glActiveTexture(GL_TEXTURE1);
		texture2.Bind();
		viewMat = camera.GetViewMatrix();
		projMat = camera.GetProjMatrix(WindowWidth, WindowHeight);
		shader.SetMat4("viewMat", viewMat);
		shader.SetMat4("projMat", projMat);

		vao.Bind();
		for (unsigned int i = 0; i < 10; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, (float)(SDL_GetTicks() / 1000.0f) * glm::radians(20.0f * (i + 1)), glm::vec3(1.0f, 0.3f, 0.5f));
			shader.SetMat4("modelMat", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		
		SDL_GL_SwapWindow(mainWin.Instance);
	}

	// clean up
	vao.Delete();
	vbo.Delete();
	shader.Delete();

	SDL_GL_DeleteContext(GLcontext);
	SDL_DestroyWindow(mainWin.Instance);
	SDL_Quit();
	return 0;

}