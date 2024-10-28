#pragma once

// #define DEBUG
#ifdef DEBUG
#define GL_CALL(func) func; CheckGLError();
#define INPUT_CHK(func); func;
#else
#define GL_CALL(func) func;
#define INPUT_CHK(func); ;
#endif

void CheckGLError();
void PrintInfo();