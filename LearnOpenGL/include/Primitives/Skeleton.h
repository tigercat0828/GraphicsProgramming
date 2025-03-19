#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "Shader.h"
#include "OGL/VAO.h"
#include "OGL/VBO.h"

class Skeleton {
public:
    std::vector<glm::vec3> edgePoints;
    VAO mVAO;
    VBO mVBO;
    Shader mShader;
    void PrintEdges() {
        for (int i = 0; i < edgePoints.size(); i += 2) {
            printf("[%f, %f, %f], [%f, %f, %f]\n",
                edgePoints[i].x, edgePoints[i].y, edgePoints[i].z,
                edgePoints[i + 1].x, edgePoints[i + 1].y, edgePoints[i + 1].z
            );
        }
    }
    Skeleton(const Shader& shader, const std::vector<glm::vec3>& edge_points) : mShader(shader),edgePoints(edge_points)  {
        mVAO = VAO();
        
        mVAO.Bind();
        mVBO = VBO(edgePoints.data(), edgePoints.size() * sizeof(glm::vec3), GL_STATIC_DRAW);

        mVBO.Bind();
        mVAO.AttribPointer(0, 3, GL_FLOAT, sizeof(glm::vec3), (void*)0);

        mVBO.Unbind();
        mVAO.Unbind();
    }

    void Draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj) {

        mShader.Use();
        mShader.SetMat4("uModelMat", model);
        mShader.SetMat4("uViewMat", view);
        mShader.SetMat4("uProjMat", proj);
        mVAO.Bind();
        glDrawArrays(GL_LINES, 0, edgePoints.size());
        mVAO.Unbind();
        mShader.Unuse();
    }
};
