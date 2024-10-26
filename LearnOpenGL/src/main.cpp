#include <iostream>
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_opengl3.h>
#include <spdlog/spdlog.h>
#include "stb_include.h"
#include "Application.h"
#include "Debug.h"

static void OnResize(int width, int height) {
	GL_CALL(glViewport(0, 0, width, height));
	spdlog::info("Resize {} {}", width, height);
}
static void OnKeyDown(SDL_Keysym keysym) {
	if (keysym.sym == SDLK_ESCAPE) {
		spdlog::info("window close");
		APP->Close();
	}
}
static void OnMouseWheel(float wheelY) {
	if (wheelY > 0) {
		std::cout << "向上滾動" << std::endl;
	}
	else if (wheelY < 0) {
		std::cout << "向下滾動" << std::endl;
	}
}
int main(int argc, char** argv) {

	using MyFun = int(*)(int, int);

	APP->TEST("Launch!!");

	if (APP->Init("Main", 800, 600)) {
		APP->SetWindowResizeFunc(OnResize);
		APP->SetKeyDownFunc(OnKeyDown);
		APP->SetMouseWheelFunc(OnMouseWheel);
	}
	else {
		exit(-1);
	}


	while (APP->IsRunning()) {
		APP->ProcessInput();
		APP->Update();
		APP->Render();
	}

	APP->Destroy();
	return 0;
}