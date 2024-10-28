#pragma once
#include <SDL2/SDL.h>
#define APP Application::GetInstance()


using WindowResizeFunc = void(*)(int width, int height);
using KeyDownFunc = void(*)(SDL_Keycode keycode);
using KeyPressedFunc = void(*)(const Uint8* state);
using MouseWheelFunc = void(*)(float wheelY);
using MouseButtonDownFunc = void(*)(Uint8 button, int x, int y);
using MouseMotionFunc = void(*)(float x, float y);

enum CursorMode {
	CURSOR_LOCKED,
	CURSOR_FREE,
};

class Application {
	 

private:
	uint32_t mWidth { 0 };
	uint32_t mHeight { 0 };
	SDL_Window* mWindow { nullptr };
	SDL_GLContext mGLcontext{nullptr};
	bool mIsRunning { true };
	CursorMode mCursorMode{ CURSOR_LOCKED };
	float mLastTime{ 0 };
public:
	float GetDeltaTime()const;
	float mDeltaTime{ 0 };
public:
	void TEST(const char* text);
	bool IsRunning() const;
	bool Init(const char* title, const int& width = 800, const int& height = 600);
	void ProcessInput();
	void Update();
	void Close();
	void Destroy();
	void Clear();
	void SwapFrameBuffer();
	void LockCursor();
	void UnLockCursor();
public:

	void GetWindowSize(int& width, int& height) const;
	void SetWindowSize(int width, int height);
	CursorMode GetCursorMode() const;
private:
	void SetCursorMode(CursorMode mode);
private:
	WindowResizeFunc mWindowResizeFunc{ nullptr };
	KeyDownFunc mKeyDownFunc{ nullptr };
	KeyPressedFunc mKeyPressedFunc{ nullptr };
	MouseWheelFunc mMouseWheelFunc{ nullptr };
	MouseButtonDownFunc mMouseButtonDownFunc{ nullptr };
	MouseMotionFunc mMouseMotionFunc{ nullptr };

public:
	void SetWindowResizeFunc(WindowResizeFunc func);
	void SetKeyDownFunc(KeyDownFunc func);
	void SetKeyPressedFunc(KeyPressedFunc func);
	void SetMouseWheelFunc(MouseWheelFunc func);
	void SetMouseButtonDownFunc(MouseButtonDownFunc func);
	void SetMouseMotioFunc(MouseMotionFunc func);
	
public:
	static Application* GetInstance();
	~Application();
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
private:
	static Application* mInstance;
	Application();
};
