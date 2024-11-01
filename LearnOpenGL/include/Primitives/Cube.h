#pragma once
#include "Transform.h"
#include "OGL/VAO.h"
#include "Shader.h"
class Cube {
public:
	Transform transform;

	Cube() = default;
	Cube(Transform transform);

	void Render(const Shader& shader) const;

public:
	static void InitGL();
	static void ReleaseGLResource();

private:
	static float CubeVertices[180];
	inline static VAO* sVAO = nullptr;
	inline static VBO* sVBO = nullptr;
};

