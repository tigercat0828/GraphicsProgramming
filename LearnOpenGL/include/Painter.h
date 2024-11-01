#pragma once
#include "OGL/VAO.h"
#include "OGL/VBO.h"
#include "glm/glm.hpp"
#include "Color.h"
class Painter {
public:
	Painter() = default;

	static void Init();


	/// <summary>
	/// Draw the parallelogram expanded by the vectors AB, AC
	/// </summary>
	static void DrawQuad(glm::vec3 a, glm::vec3 b, glm::vec3 c);
	static void DrawTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c);
	static void DrawLine(glm::vec3 a, glm::vec3 b);
	static void DrawLine();
	static void DrawPoint(glm::vec3 a);
	static void SetColor(glm::vec3 color);
	
private:
	inline static glm::vec3 mColor = Color::WHITE;
	inline static VAO* sVAO = nullptr;
	inline static VBO* slineVBO = nullptr;
};
