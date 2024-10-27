#pragma once

// #define DEBUG
#ifdef DEBUG
#define GL_CALL(func) func; CheckError();
#else
#define GL_CALL(func) func;
#endif

void CheckError();
void PrintInfo();