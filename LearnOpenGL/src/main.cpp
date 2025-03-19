#include <iostream>
#include "AllInclude.h"
#include "Vec3RW.h"
#include "Primitives/Skeleton.h"
using namespace std;
using namespace glm;

static void OnResize(int width, int height);
static void OnKeyDown(SDL_Keycode keycode);
static void OnKeyPressed(const Uint8* state);
static void OnMouseWheel(float wheelY);
static void OnMouseMotion(float x, float y);
static void OnMouseButtonDown(Uint8 button, int x, int y);

CameraBase camera(glm::vec3(3, 3, 3), -30, -90);
int main(int argc, char** argv) {

	APP->TEST("Launch!!");
	if (APP->Init("Main", 1440, 900)) {
		APP->SetWindowResizeFunc(OnResize);
		APP->SetKeyDownFunc(OnKeyDown);
		APP->SetKeyPressedFunc(OnKeyPressed);
		APP->SetMouseWheelFunc(OnMouseWheel);
		APP->SetMouseButtonDownFunc(OnMouseButtonDown);
		APP->SetMouseMotioFunc(OnMouseMotion);
		APP->LockCursor();
		PrintInfo();
	}
	else {
		exit(-1);
	}
	// Laod Textures
	Texture texture("wall.jpg");
	// Compile Shaders
	Shader painterShader("Painter.vert", "Painter.frag");
	Shader pointCloudShader("PointCloud.vert", "PointCloud.frag");
	Shader skeletonShader("skeleton.vert", "skeleton.frag");


	auto edges = Vec3RW::Load("C:\\Users\\Tigercat\\Desktop\\skeleton.bin");
	Skeleton skeleton(skeletonShader, edges);
	//skeleton.PrintEdges();

	// Load Files
	string plyfile = "input.ply";
	PLYfile ply;
	if (!ply.LoadFile(plyfile)) spdlog::error("failed to load .ply file {}", plyfile);
	
	GL_CALL(glPointSize(2.0f));
	// GameObjects
	Painter painter(painterShader);
	painter.SetLineWidth(3);

	
	//PointCloud cloud(pointCloudShader, ply);
	Vec3RW rw;
	
	//std::vector<glm::vec3> points = rw.Read("C:\\Repository\\AdTree\\data\\tree1.xyz");
	std::vector<glm::vec3> points = rw.Read("C:\\Repository\\AdTree\\data\\tree7.xyz");

	//std::vector<glm::vec3> points = rw.Read("C:\\Users\\Tigercat\\Downloads\\tree7_centralize.xyz");
	//std::vector<glm::vec3> points = rw.Read("C:\\Users\\Tigercat\\Downloads\\tree1.xyz");
	//Lille_2.xyz
	//std::vector<glm::vec3> points = rw.Read("C:\\Users\\Tigercat\\Downloads\\Lille_2.xyz");
	/*for (auto v : points) {
		printf("%f %f %f\n",v.x,v.y,v.z);
	}*/
	PointCloud cloud(pointCloudShader,points);


	// TODO : tracked ball camera, L-system


	int width, height;
	APP->GetWindowSize(width, height);

	while (APP->IsRunning()) {
		APP->ProcessInput();
		APP->Clear();
		APP->NewImGuiFrame();

		ImGui::Begin("FPS Counter");
		ImGui::Text("FPS: %.0f", 1 / APP->GetDeltaTime());
		ImGui::End();

		mat4 modelMat = mat4(1.0);
		mat4 viewMat = mat4(1.0);
		mat4 projMat = mat4(1.0);
		viewMat = camera.GetViewMatrix();
		projMat = camera.GetProjMatrix(width, height);

		painter.SetMatMVP(modelMat, viewMat, projMat);
		painter.Use();
		//painter.DrawAxis();
		cloud.Render(modelMat, viewMat, projMat);
		skeleton.Draw(modelMat, viewMat, projMat);


		APP->SwapFrameBuffer();
	}

	painter.ReleaseGLResource();
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
