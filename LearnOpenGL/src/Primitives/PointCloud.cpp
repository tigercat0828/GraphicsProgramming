#include "Primitives/PointCloud.h"


PointCloud::PointCloud(const Shader& shader, std::vector<glm::vec3>&& positions, std::vector<glm::vec3>&& normals, std::vector<glm::vec3>&& colors):mShader(shader), mPositions(positions), mNormals(normals), mColors(colors)
{
	Initialize();
}

PointCloud::PointCloud(const Shader& shader, const PLYfile& ply) :mShader(shader), mPositions(ply.positions), mNormals(ply.normals), mColors(ply.colors)
{
	Initialize();
}

PointCloud::PointCloud(const Shader& shader,const std::vector<glm::vec3>& positions):mShader(shader), mPositions(positions) {
	size_t count = mPositions.size();
	mColors = std::vector<glm::vec3>(count,glm::vec3(255.0f,255.0f,255.0f));
	mNormals = std::vector<glm::vec3>(count, glm::vec3(0, 0, 0));
	Initialize();
}



void PointCloud::Initialize()
{
	mCount = mPositions.size();

	mVAO = VAO();
	mVAO.Bind();
	mVBOposition = VBO(mPositions.data(), mPositions.size() * sizeof(glm::vec3), GL_STATIC_DRAW);
	mVBOnormal = VBO(mNormals.data(), mNormals.size() * sizeof(glm::vec3), GL_STATIC_DRAW);
	mVBOcolor = VBO(mColors.data(), mColors.size() * sizeof(glm::vec3), GL_STATIC_DRAW);

	mVBOposition.Bind();
	mVAO.AttribPointer(0, 3, GL_FLOAT, sizeof(glm::vec3), (void*)0);

	mVBOnormal.Bind();
	mVAO.AttribPointer(1, 3, GL_FLOAT, sizeof(glm::vec3), (void*)0);

	mVBOcolor.Bind();
	mVAO.AttribPointer(2, 3, GL_FLOAT, sizeof(glm::vec3), (void*)0);

	mVBOcolor.Unbind();
	mVAO.Unbind();
}

void PointCloud::Render(const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj)
{
	mShader.Use();
	mShader.SetMat4("uModelMat", model);
	mShader.SetMat4("uViewMat", view);
	mShader.SetMat4("uProjMat", proj);
	mVAO.Bind();
	glDrawArrays(GL_POINTS, 0, mCount);
	mVAO.Unbind();
	mShader.Unuse();
}

