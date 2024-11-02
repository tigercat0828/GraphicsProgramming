#include "Painter.h"
#include "glm/gtc/type_ptr.hpp"
#include "Debug.h"
Painter::Painter()
{
	Shader shader("xyzUrgb.vert", "xyzUrgb.frag");
	mShader = shader;
	SetColor(Color::White);
	mVAO = VAO();
	mVBO = VBO(mVertices, sizeof(mVertices), GL_DYNAMIC_DRAW);
	mVAO.Bind();
	mVBO.Bind();
	mVAO.AttribPointer(0, 3, GL_FLOAT, sizeof(glm::vec3), (void*)0);
	mVBO.Unbind();
	mVAO.Unbind();
}

void Painter::DrawQuad(glm::vec3 a, glm::vec3 b, glm::vec3 c) 
{
}
void Painter::DrawAxis()
{
	SetColor(Color::Red);
	DrawLine(glm::vec3(0, 0, 0), glm::vec3(10, 0, 0));
	SetColor(Color::Green);
	DrawLine(glm::vec3(0, 0, 0), glm::vec3(0, 10, 0));
	SetColor(Color::Blue);
	DrawLine(glm::vec3(0, 0, 0), glm::vec3(0, 0, 10));
}
void Painter::DrawTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	mShader.Use();
	mVertices[0] = a;
	mVertices[1] = b;
	mVertices[2] = c;
	mVAO.Bind();
	mVBO.Bind();
	mVBO.SubData(0, 3 * sizeof(glm::vec3), mVertices);
	GL_CALL();
	glDrawArrays(GL_TRIANGLES, 0, 9);
}
void Painter::DrawLine(glm::vec3 a, glm::vec3 b) 
{
	// todo use sub data to update vertice data
	mShader.Use();
	mVertices[0] = a;
	mVertices[1] = b;
	mVAO.Bind();
	mVBO.Bind();
	mVBO.SubData(0,2*sizeof(glm::vec3),mVertices);
	GL_CALL(glDrawArrays(GL_LINES, 0, 6));
	mVBO.Unbind();
	mVAO.Unbind();
}
void Painter::DrawPoint(glm::vec3 a)
{
}
void Painter::SetColor(glm::vec3 color)
{
	mColor = color;
	mShader.Use();
	mShader.SetVec3("uColor", mColor);
}

void Painter::SetPointSize(float size)
{
	mPointSize = size;
	GL_CALL(glPointSize(size));
}

void Painter::SetLineWidth(float width)
{
	mLineWidth = width;
	GL_CALL(glLineWidth(width));
}

void Painter::SetMVPMat(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat)
{
	mShader.Use();
	mShader.SetMat4("uProjMat", projMat);
	mShader.SetMat4("uViewMat", viewMat);
	mShader.SetMat4("uModelMat", modelMat);
	mShader.Unuse();
}

void Painter::ReleaseGLResource()
{
	mShader.Delete();
	mVAO.Delete();
	mVBO.Delete();
}


