#include <memory>
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include "Application.h"
#include "Debug.h"
Application* Application::mInstance = nullptr;


bool Application::IsRunning() const {
	return mIsRunning;
}

void Application::Close() {
	mIsRunning = false;
}

void Application::TEST(const char* text) {
	std::cout << text << std::endl;
}

bool Application::Init(const char* title, const int& width, const int& height) {


	mWidth = width;
	mHeight = height;
	if (SDL_Init(SDL_INIT_VIDEO ) < 0) {
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
		spdlog::error("Fail to create SDL window");
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
	return true;
	//LockCursor();
}

void Application::Update() {
	
}

void Application::Destroy() {
	SDL_GL_DeleteContext(mGLcontext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
	
}

void Application::Render() {
	// render
	GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	SDL_GL_SwapWindow(mWindow);
}

void Application::SetWindowSize(int width, int height) {
	mWidth = width;
	mHeight = height;
}


void Application::ProcessInput() {
	// Poll Events
	SDL_Event event;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			SDL_DestroyWindow(mWindow);
			SDL_Quit();
			exit(-3);
		}
		// key down
		if (event.type == SDL_KEYDOWN) {
			if (mKeyDownFunc != nullptr) {
				mKeyDownFunc(event.key.keysym);
			}
		}
		if (event.type == SDL_EventType::SDL_MOUSEWHEEL) {
			if (mMouseWheel != nullptr) {
				mMouseWheel(event.wheel.y);
			}
		
		}
		if (event.type == SDL_WINDOWEVENT) {
			//window resize 
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				if (mWindowResizeFunc != nullptr) {
					int width = event.window.data1;
					int height = event.window.data2;
					mWindowResizeFunc(width, height);
				}
			}
		}
		//processMouseInput(event);
	}
	// smooth keyboard
	//processKeyboardInput(state, deltaTime);
}

void Application::SetWindowResizeFunc(WindowResizeFunc func) {
	mWindowResizeFunc = func;
}

void Application::SetKeyDownFunc(KeyDownFunc func) {
	mKeyDownFunc = func;
}

void Application::SetMouseWheelFunc(MouseWheelFunc func) {
	mMouseWheel = func;
}

Application* Application::GetInstance() {
	if (mInstance == nullptr) {
		mInstance = new Application();
	}
	return mInstance;
}

Application::~Application() {}
Application::Application() {}

