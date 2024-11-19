#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "libs/glad/glad.h"

using namespace std;

char* readFile(const char* path, char* style);
void checkIfShaderCompileSuccess(unsigned int shader, const char* desc);
void checkIfShaderProgramLinkSuccess(unsigned int shaderProgram);

#endif
