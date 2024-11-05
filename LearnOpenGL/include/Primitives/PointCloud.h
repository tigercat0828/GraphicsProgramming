#pragma once
#include<vector>
#include<glm/glm.hpp>
#include "OGL/VAO.h"
#include "OGL/VBO.h"
#include "Shader.h"
#include "Modules/PLYfile.h"
class PointCloud {
public:
	PointCloud(const Shader& shader,std::vector<glm::vec3>&& positions, std::vector<glm::vec3>&& normals, std::vector<glm::vec3>&& colors);
	PointCloud(const Shader& shader,const PLYfile& ply);
private:
	void Initialize();
public:
	std::vector<glm::vec3> mPositions;
	std::vector<glm::vec3> mNormals;
	std::vector<glm::vec3> mColors;
	size_t mCount{ 0 };
public:
	void Render(const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj);
private:
	VAO mVAO;
	VBO mVBOposition;
	VBO mVBOcolor;
	VBO mVBOnormal;
	Shader mShader;
};