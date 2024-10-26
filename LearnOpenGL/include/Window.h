#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <spdlog/spdlog.h>

class Window {
public:
	std::string Title;
	int Width;
	int Height;
	SDL_Window* Instance;
	Window() {}
	Window(const std::string& title, int width, int height) : Title(title), Width(width), Height(height) {
		Instance = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			Width, Height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
		);

		LockCursor();

	}
	void LockCursor() const {
		SDL_WarpMouseInWindow(Instance, Width, Height);
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
};