#pragma once
#include "OGL/VAO.h"
#include "OGL/VBO.h"
#include "glm/glm.hpp"
#include "Color.h"
#include "Shader.h"
class Painter {
public:
	Painter();
	/// <summary>
	/// Draw the parallelogram expanded by the vectors AB, AC
	/// </summary>
	void DrawQuad(glm::vec3 a, glm::vec3 b, glm::vec3 c) ;
	void DrawTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c) ;
	void DrawLine(glm::vec3 a, glm::vec3 b) ;
	void DrawPoint(glm::vec3 a) ;
	void SetColor(glm::vec3 color);
	void SetPointSize(float size);
	void SetLineWidth(float width);
	void SetMVPMat(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat);
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
