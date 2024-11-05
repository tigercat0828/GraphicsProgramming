#include "Modules/PLYfile.h"
#include "Debug.h"
bool PLYfile::LoadFile(const std::string& filename)
{
	std::filesystem::path filepath = std::filesystem::current_path() / "Assets" / filename;

	std::ifstream file(filepath, std::ios::binary);
	if (!file.is_open()) {
		spdlog::error("Failed to open file {}", filename);
		return false;
	}
	bool isHeaderEnded = false;
	std::string line;
	mCount = 0;
	while (std::getline(file, line)) {
		if (line.find("element vertex") != std::string::npos) {
			mCount = std::stoul(line.substr(line.find_last_of(" ") + 1));
		}
		else if (line == "end_header") {
			isHeaderEnded = true;
			break;
		}
	}
	if (!isHeaderEnded) {
		spdlog::error("Invalid .ply file {}", filename);
		return false;
	}

	positions.reserve(mCount);
	normals.reserve(mCount);
	colors.reserve(mCount);
	for (size_t i = 0; i < mCount; ++i) {
		float x, y, z, nx, ny, nz;
		unsigned char r, g, b;

		file.read(reinterpret_cast<char*>(&x), sizeof(float));
		file.read(reinterpret_cast<char*>(&y), sizeof(float));
		file.read(reinterpret_cast<char*>(&z), sizeof(float));
		file.read(reinterpret_cast<char*>(&nx), sizeof(float));
		file.read(reinterpret_cast<char*>(&ny), sizeof(float));
		file.read(reinterpret_cast<char*>(&nz), sizeof(float));
		file.read(reinterpret_cast<char*>(&r), sizeof(unsigned char));
		file.read(reinterpret_cast<char*>(&g), sizeof(unsigned char));
		file.read(reinterpret_cast<char*>(&b), sizeof(unsigned char));

		//printf("p %f %f %f\n", x, y, z);
		//printf("n %f %f %f\n", nx, ny, nz);
		//printf("c %u %u %u\n", r, g, b);

		positions.emplace_back(x, y, z);
		normals.emplace_back(nx, ny, nz);
		colors.emplace_back(r, g, b);
	}
	return true;
}

bool PLYfile::WriteTextFile(const std::string& filename)
{
	std::ofstream outFile(filename);
	if (!outFile) {
		spdlog::error("Failed to create file : {}", filename);
		return false;
	}

	return true;
}
