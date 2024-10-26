#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#define APP Application::GetInstance()


using WindowResizeFunc = void(*)(int width, int height);
using KeyDownFunc = void(*)(SDL_Keycode keycode);
using MouseWheelFunc = void(*)(float wheelY);
using MouseButtonFunc = void(*)();

class Application {
	 

private:
	uint32_t mWidth { 0 };
	uint32_t mHeight { 0 };
	SDL_Window* mWindow { nullptr };
	SDL_GLContext mGLcontext{nullptr};
	bool mIsRunning { true };

	
public:
	void TEST(const char* text);
	bool IsRunning() const;
	bool Init(const char* title, const int& width = 800, const int& height = 600);
	void ProcessInput();
	void Update();
	void Close();
	void Destroy();
	void Render();
public:
	void SetWindowSize(int width, int height);

private:
	WindowResizeFunc mWindowResizeFunc{ nullptr };
	KeyDownFunc mKeyDownFunc{ nullptr };
	MouseWheelFunc mMouseWheel{ nullptr };
public:
	void SetWindowResizeFunc(WindowResizeFunc func);
	void SetKeyDownFunc(KeyDownFunc func);
	void SetMouseWheelFunc(MouseWheelFunc func);
	void SetMouseButtonFunc();
public:
	static Application* GetInstance();
	~Application();
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
private:
	static Application* mInstance;
	Application();
};
