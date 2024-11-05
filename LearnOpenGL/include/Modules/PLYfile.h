#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include "OGL/VAO.h"
#include "OGL/VBO.h"
/// <summary>
/// format: (x,y,z,nx,ny,nz,r,g,b)
/// </summary>
class PLYfile {
public:
	size_t mCount{ 0 };
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> colors;
	PLYfile() = default;
	bool LoadFile(const std::string& filename);
	bool WriteTextFile(const std::string& filename);
};

/*
ply
format binary_little_endian 1.0
element vertex 207256
property float x
property float y
property float z
property float nx
property float ny
property float nz
property uchar red
property uchar green
property uchar blue
end_header
<binary>
*/