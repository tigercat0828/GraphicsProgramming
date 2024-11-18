#include <memory>
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_opengl3.h>
#include "Application.h"
#include "Debug.h"
Application* Application::mInstance = nullptr;


bool Application::IsRunning() const {
	return mIsRunning;
}

void Application::Close() {
	mIsRunning = false;
}



float Application::GetDeltaTime() const {
	return mDeltaTime;
}

void Application::TEST(const char* text) {
	spdlog::info("HALO");
}

bool Application::Init(const char* title, const int& width, const int& height) {


	mWidth = width;
	mHeight = height;

	//spdlog::set_pattern("[%l] %v");
	
	if (SDL_Init(SDL_INIT_VIDEO ) < 0) {		// // SDL_INIT_EVERYTHING
		spdlog::error("Fail to init SDL : {}", SDL_GetError());
		return false;
	}
	else {
		spdlog::info("Success to init SDL"); 
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	mWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth, mHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |SDL_WINDOW_RESIZABLE);

	if (mWindow == NULL) {
		spdlog::error("Fail to create SDL window : {}", SDL_GetError());
		SDL_Quit();
		return false;
	}
	else {
		spdlog::info("Success to create SDL window");
	}

	mGLcontext = SDL_GL_CreateContext(mWindow);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		spdlog::error("Fail to init GLAD");
		SDL_GL_DeleteContext(mGLcontext);
		SDL_DestroyWindow(mWindow);
		SDL_Quit();
		return false;
	}
	else {
		spdlog::info("Success to init GLAD");
	}

	// Setup ImGui context
	//----------------------------------------------
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(mWindow, mGLcontext);
	ImGui_ImplOpenGL3_Init("#version 460");
	//----------------------------------------------

	if (mCursorMode == CURSOR_LOCKED) {
		LockCursor();
	}
	GL_CALL(glViewport(0, 0, mWidth, mHeight));
	GL_CALL(glEnable(GL_DEPTH_TEST));

	return true;
}



void Application::Destroy() {
	SDL_GL_DeleteContext(mGLcontext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Application::Clear() {
	// render
	GL_CALL(glClearColor(0,0,0, 1.0f));
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Application::SwapFrameBuffer() {

	// Render ImGui
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// swap buffer
	SDL_GL_SwapWindow(mWindow);
}

void Application::NewImGuiFrame()
{
	// Start ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
}



void Application::LockCursor() {
	SetCursorMode(CursorMode::CURSOR_LOCKED);
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void Application::UnLockCursor() {
	SetCursorMode(CursorMode::CURSOR_FREE);
	SDL_SetRelativeMouseMode(SDL_FALSE);
}

void Application::GetWindowSize(int& width, int& height) const {
	width = mWidth;
	height = mHeight;
}

void Application::SetWindowSize(int width, int height) {
	mWidth = width;
	mHeight = height;
}

CursorMode Application::GetCursorMode() const {
	return mCursorMode;
}

void Application::SetCursorMode(CursorMode mode) {
	mCursorMode = mode;
}


void Application::ProcessInput() {

	float current = SDL_GetTicks() / 1000.0f;
	mDeltaTime = current - mLastTime;
	mLastTime = current;

	// Poll Events
	SDL_Event event;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&event)) {

		ImGui_ImplSDL2_ProcessEvent(&event);
		
		
		if (event.type == SDL_EventType::SDL_KEYDOWN) {
			if (mKeyDownFunc != nullptr) {
				//mKeyDownFunc(event.key.keysym.scancode);
				mKeyDownFunc(event.key.keysym.sym);
			}
		}
		if (event.type == SDL_EventType::SDL_MOUSEMOTION) {
			if (mMouseMotionFunc != nullptr ) {
				float x, y;
				if (mCursorMode == CursorMode::CURSOR_FREE) {
					x = event.motion.x;
					y = event.motion.y;
				}
				else {
					x = event.motion.xrel;
					y = event.motion.yrel;
				}
				mMouseMotionFunc(x, y);
			}
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (mMouseButtonDownFunc != nullptr) {
				auto t = event.button.button;
				int x = event.button.x;
				int y = event.button.y;
				mMouseButtonDownFunc(t, x, y);
			}
		}
		if (event.type == SDL_EventType::SDL_MOUSEWHEEL) {
			if (mMouseWheelFunc != nullptr) {
				mMouseWheelFunc(event.wheel.y);
			}
		}
		
		if (event.type == SDL_EventType::SDL_WINDOWEVENT) {
			//window resize 
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				if (mWindowResizeFunc != nullptr) {
					int width = event.window.data1;
					int height = event.window.data2;
					mWindowResizeFunc(width, height);
				}
			}
		}
		else if (event.type == SDL_QUIT) {
			SDL_DestroyWindow(mWindow);
			SDL_Quit();
		}

	}
	// smooth keyboard
	if (mKeyPressedFunc != nullptr) {
		mKeyPressedFunc(state);
	}
}

void Application::SetWindowResizeFunc(WindowResizeFunc func) {
	mWindowResizeFunc = func;
}

void Application::SetKeyDownFunc(KeyDownFunc func) {
	mKeyDownFunc = func;
}

void Application::SetKeyPressedFunc(KeyPressedFunc func) {
	mKeyPressedFunc = func;
}

void Application::SetMouseWheelFunc(MouseWheelFunc func) {
	mMouseWheelFunc = func;
}

void Application::SetMouseButtonDownFunc(MouseButtonDownFunc func) {
	mMouseButtonDownFunc = func;
}

void Application::SetMouseMotioFunc(MouseMotionFunc func) {
	mMouseMotionFunc = func;
}

Application* Application::GetInstance() {
	if (mInstance == nullptr) {
		mInstance = new Application();
	}
	return mInstance;
}

Application::Application() {}

