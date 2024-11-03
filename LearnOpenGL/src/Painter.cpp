#include "Painter.h"
#include "glm/gtc/type_ptr.hpp"
#include "Debug.h"
Painter::Painter(const Shader& shader)
{
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

void Painter::DrawQuad(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
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
void Painter::DrawTriangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
{
	mVertices[0] = a;
	mVertices[1] = b;
	mVertices[2] = c;
	mVAO.Bind();
	mVBO.Bind();

	mVBO.SubData(0, 3 * sizeof(glm::vec3), mVertices);
	GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 3));
	mVBO.Unbind();
	mVAO.Unbind();
}
void Painter::DrawLine(const glm::vec3& a, const glm::vec3& b)
{
	// todo use sub data to update vertice data
	mVertices[0] = a;
	mVertices[1] = b;
	mVAO.Bind();
	mVBO.Bind();
	mVBO.SubData(0, 2 * sizeof(glm::vec3), mVertices);
	GL_CALL(glDrawArrays(GL_LINES, 0, 2));
	mVBO.Unbind();
	mVAO.Unbind();
}
void Painter::DrawPoint(const glm::vec3& a)
{
	mVertices[0] = a;
	mVAO.Bind();
	mVBO.Bind();
	mVBO.SubData(0, sizeof(glm::vec3), mVertices);
	GL_CALL(glDrawArrays(GL_POINTS, 0, 1));
	mVBO.Unbind();
	mVAO.Unbind();
}
void Painter::Use() {
	mShader.Use();
}
void Painter::SetColor(const glm::vec3& color)
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

void Painter::SetMatMVP(const glm::mat4& modelMat, const glm::mat4& viewMat, const glm::mat4& projMat)
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


