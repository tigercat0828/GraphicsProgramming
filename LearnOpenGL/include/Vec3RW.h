#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Vec3RW {
public:
    // Method to read 3D vectors from a file
    std::vector<glm::vec3> Read(const std::string& filename) {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return {};
        }

        std::vector<glm::vec3> position; // Temporary vector to store the read data
        float x, y, z;
        while (inputFile >> x >> y >> z) {
            position.emplace_back(x, y, z); // Use emplace_back with the constructor
        }
        inputFile.close();
        return position;
    }
    // Method to write 3D vectors to a file
    static void Write(const std::string& filename, const std::vector<glm::vec3>& vec) {
        std::ofstream outputFile(filename);
        if (!outputFile.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return;
        }

        for (const auto& v : vec) {
            outputFile << v.x << " " << v.y << " " << v.z << std::endl;
        }

        outputFile.close();
    }

    static void Save(const std::vector<glm::vec3>& vec, const std::string& filename) {
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile) {
            std::cerr << "Error opening file for writing: " << filename << std::endl;
            return;
        }

        size_t size = vec.size();
        outFile.write(reinterpret_cast<const char*>(&size), sizeof(size)); // Write size of the vector
        outFile.write(reinterpret_cast<const char*>(vec.data()), size * sizeof(glm::vec3)); // Write vector data

        outFile.close();
    }


    static std::vector<glm::vec3> Load(const std::string& filename) {
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile) {
            std::cerr << "Error opening file for reading: " << filename << std::endl;
            return {};
        }

        size_t size;
        inFile.read(reinterpret_cast<char*>(&size), sizeof(size)); // Read size of the vector

        std::vector<glm::vec3> vec(size);
        inFile.read(reinterpret_cast<char*>(vec.data()), size * sizeof(glm::vec3)); // Read vector data

        inFile.close();
        return vec;
    }
    
};
