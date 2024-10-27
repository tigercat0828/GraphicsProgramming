#include <iostream>
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_opengl3.h>
#include <spdlog/spdlog.h>
#include "Shader.h"
#include "stb_include.h"
#include "Application.h"
#include "Debug.h"
#include "VAO.h"
#include "VBO.h"

static void OnResize(int width, int height) {
	GL_CALL(glViewport(0, 0, width, height));
	spdlog::info("Resize {} {}", width, height);
}
static void OnKeyDown(SDL_Keycode keycode) {

	const char* keyName = SDL_GetKeyName(keycode);
	spdlog::info("Key {} pressed down", keyName);
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
static void OnMouseWheel(float wheelY) {
	if (wheelY > 0) {
		spdlog::info("wheel up");
	}
	else if (wheelY < 0) {
		spdlog::info("wheel down");
	}
}
static void OnMouseButtonDown(Uint8 button, int x, int y) {
	if (button == SDL_BUTTON_LEFT) {
		spdlog::info("Left button click down ({}, {})", x, y);
	}
	else if (button == SDL_BUTTON_RIGHT) {
		spdlog::info("right button click down ({}, {})", x, y);
	}
}
static void OnMouseMotion(float x, float y) {

	CursorMode mode = APP->GetCursorMode();
	if (mode == CursorMode::CURSOR_FREE) {
		spdlog::info("Mouse move to ({}, {})", x, y);
	}
	else {
		spdlog::info("Mouse offset({}, {})", x, y);
	}
	
}
int main(int argc, char** argv) {

	using MyFun = int(*)(int, int);

	APP->TEST("Launch!!");

	if (APP->Init("Main", 800, 600)) {
		APP->SetWindowResizeFunc(OnResize);
		APP->SetKeyDownFunc(OnKeyDown);
		APP->SetMouseWheelFunc(OnMouseWheel);
		APP->SetMouseButtonDownFunc(OnMouseButtonDown);
		APP->SetMouseMotioFunc(OnMouseMotion);
		APP->LockCursor();
	}
	else {
		exit(-1);
	}
	Shader basic("Basic.vert", "Basic.frag");
	

	while (APP->IsRunning()) {
		APP->ProcessInput();
		APP->Update();
		APP->Render();
	}

	APP->Destroy();
	return 0;
}