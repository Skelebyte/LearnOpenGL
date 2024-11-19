#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "libs/glad/glad.h"

char* readFile(const char* path, char* style);

#endif
