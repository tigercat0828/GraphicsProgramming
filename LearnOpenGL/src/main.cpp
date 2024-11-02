#include <iostream>
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_opengl3.h>
#include <spdlog/spdlog.h>
#include "Shader.h"
#include "Application.h"
#include "Debug.h"
#include "OGL/VBO.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "Primitives/Cube.h"
#include "Painter.h"
using namespace std;
using namespace glm;

static void OnResize(int width, int height);
static void OnKeyDown(SDL_Keycode keycode);
static void OnKeyPressed(const Uint8* state);
static void OnMouseWheel(float wheelY);
static void OnMouseMotion(float x, float y);
static void OnMouseButtonDown(Uint8 button, int x, int y);

Camera camera(glm::vec3(3, 3, 3 ), -30, -90);
int main(int argc, char** argv) {

	APP->TEST("Launch!!");
	if (APP->Init("Main", 600, 600)) {
		APP->SetWindowResizeFunc(OnResize);
		APP->SetKeyDownFunc(OnKeyDown);
		APP->SetKeyPressedFunc(OnKeyPressed);
		APP->SetMouseWheelFunc(OnMouseWheel);
		APP->SetMouseButtonDownFunc(OnMouseButtonDown);
		APP->SetMouseMotioFunc(OnMouseMotion);
		APP->LockCursor();
	}
	else {
		exit(-1);
	}
	PrintInfo();
	Cube::InitGL();
	vec3 cubePositions[] = {
		vec3(0.0f,  0.0f,  0.0f),
		vec3(2.0f,  5.0f, -15.0f),
		vec3(-1.5f, -2.2f, -2.5f),
		vec3(-3.8f, -2.0f, -12.3f),
		vec3(2.4f, -0.4f, -3.5f),
		vec3(-1.7f,  3.0f, -7.5f),
		vec3(1.3f, -2.0f, -2.5f),
		vec3(1.5f,  2.0f, -2.5f),
		vec3(1.5f,  0.2f, -1.5f),
		vec3(-1.3f,  1.0f, -1.5f)
	};
	vector<Cube> cubes;
	cubes.reserve(10);
	for (const auto& pos : cubePositions) 	cubes.emplace_back(Transform(pos));
	

	VAO vao;
	vao.Bind();
	float vertices[] = {
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		10.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 10.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 1.0f,
	};
	VBO vbo(vertices, sizeof(vertices), GL_STATIC_DRAW);
	vao.AttribPointer(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	vao.AttribPointer(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.Unbind();
	
	Shader defaultShader("xyzuv.vert", "xyzuv.frag");
	Shader axisShader("xyzrgb.vert", "xyzrgb.frag");

	Painter painter;
	painter.SetColor(Color::Yellow);
	
	Texture texture("wall.jpg");
	texture.AssignUnit(defaultShader, "uTexture", 0);

	int width, height;
	APP->GetWindowSize(width, height);
	
	while (APP->IsRunning()) {
		APP->Clear();
		APP->ProcessInput();

		mat4 modelMat = mat4(1.0);
		mat4 viewMat = mat4(1.0);
		mat4 projMat = mat4(1.0);

		viewMat = camera.GetViewMatrix();
		projMat = camera.GetProjMatrix(width, height);

		painter.SetMVPMat(modelMat, viewMat, projMat);
		painter.SetLineWidth(3);
		static float Time = 0;
		Time += APP->GetDeltaTime();
		painter.DrawLine(vec3(0, 0, 0), vec3(Time, Time, Time));

		axisShader.Use();
		axisShader.SetMat4("uViewMat", viewMat);
		axisShader.SetMat4("uProjMat", projMat);
		axisShader.SetMat4("uModelMat", modelMat);
		vao.Bind();
		// todo : show assert line
		GL_CALL(glLineWidth(2.0f));
		GL_CALL(glDrawArrays(GL_LINES, 0, 6));
		GL_CALL(glLineWidth(2.0f));
		vao.Unbind();

		defaultShader.Use();
		glActiveTexture(GL_TEXTURE0);
		texture.Bind();
		
		defaultShader.SetMat4("uViewMat", viewMat);
		defaultShader.SetMat4("uProjMat", projMat);
		defaultShader.SetMat4("uModelMat", modelMat);
		int i = 1;
		for (const auto& cube : cubes) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cube.transform.position);
			float angle = 20.0f * i++;
			model = glm::rotate(model, (float)(SDL_GetTicks() / 1000.0f) * glm::radians(20.0f * (i + 1)), glm::vec3(1.0f, 0.3f, 0.5f));
			defaultShader.SetMat4("uModelMat", model);
			cube.Render(defaultShader);
		}
		APP->SwapFrameBuffer();
	}

	Cube::ReleaseGLResource();
	painter.ReleaseGLResource();
	defaultShader.Delete();

	APP->Destroy();
	return 0;
}

static void OnResize(int width, int height) {
	spdlog::info("Resize {} {}", width, height);
	APP->SetWindowSize(width, height);
	GL_CALL(glViewport(0, 0, width, height));
}
static void OnKeyDown(SDL_Keycode keycode) {
	//spdlog::info("Key {} pressed down", SDL_GetKeyName(keycode));
	
	if (keycode == SDLK_ESCAPE) {
		spdlog::info("window close");
		APP->Close();
	}
	if (keycode == SDLK_TAB) {
		auto mode = APP->GetCursorMode();
		if (mode == CURSOR_FREE) {
			APP->LockCursor();
		}
		else {
			APP->UnLockCursor();
		}
	}
}
void OnKeyPressed(const Uint8* state) {
	//for (int i = 0; i < SDL_NUM_SCANCODES; ++i) if (state[i]) spdlog::info("Key {} pressed", SDL_GetScancodeName(static_cast<SDL_Scancode>(i)));

	//float deltaTime = APP->mDeltaTime;
	float deltaTime = APP->GetDeltaTime();
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
static void OnMouseWheel(float wheelY) {
	(wheelY > 0) ? spdlog::info("wheel up") : spdlog::info("wheel down");

	camera.Zoom(wheelY * 3.0f);
}
static void OnMouseButtonDown(Uint8 button, int x, int y) {
	if (button == SDL_BUTTON_LEFT) 
		spdlog::info("Left button click down ({}, {})", x, y);
	else if (button == SDL_BUTTON_RIGHT) 
		spdlog::info("right button click down ({}, {})", x, y);
	
}
static void OnMouseMotion(float x, float y) {
	CursorMode mode = APP->GetCursorMode();

	if (mode == CursorMode::CURSOR_FREE) {
		//spdlog::info("Mouse move to ({}, {})", x, y);
	}
	else {
		//spdlog::info("Mouse offset({}, {})", x, y);
		camera.Turn(x, -y);
	}
}
