#pragma once
#include "OGL/VAO.h"
#include "OGL/VBO.h"
#include "glm/glm.hpp"
#include "Color.h"
#include "Shader.h"
class Painter {
public:
	Painter(const Shader& shader);
	/// <summary>
	/// Draw the parallelogram expanded by the vectors AB, AC
	/// </summary>
	void DrawQuad(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) ;
	void DrawAxis();
	void DrawTriangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) ;
	void DrawLine(const glm::vec3& a, const glm::vec3& b) ;
	void DrawPoint(const glm::vec3& a);
	void Use();
	void SetColor(const glm::vec3& color);
	void SetPointSize(float size);
	void SetLineWidth(float width);
	void SetMatMVP(const glm::mat4& modelMat, const glm::mat4& viewMat, const glm::mat4& projMat);
	void ReleaseGLResource();
private:
	glm::vec3 mColor{ Color::Orange };
	glm::vec3 mVertices[4] = {
		glm::vec3(0,0,0), 
		glm::vec3(3,3,3), 
		glm::vec3(0,0,0),												
		glm::vec3(0,0,0), 
	};
	float mPointSize{ 1 };
	float mLineWidth{ 1 };
	Shader mShader;
	VAO mVAO;
	VBO mVBO;
};
