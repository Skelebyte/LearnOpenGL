#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "libs/glad/glad.h"

using namespace std;

const char* readFile(const char* path);
void checkIfShaderCompileSuccess(unsigned int shader, const char* desc);
void checkIfShaderProgramLinkSuccess(unsigned int shaderProgram);

#endif
