#pragma once
#include <string>
#include <assert.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>


// #define DEBUG
#ifdef DEBUG
#define GL_CALL(func); func; CheckError();
#else
#define GL_CALL(func); func;
#endif

void CheckError();
void PrintInfo();