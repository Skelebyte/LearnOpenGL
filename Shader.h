#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <stdbool.h>
#include "libs/glad/glad.h"
#include "Utils.h"

#define DEFAULT_VERTEX_SHADER_SRC readFile("shaders/Default.vert", "rb");
#define DEFAULT_FRAGMENT_SHADER_SRC readFile("shaders/Default.frag", "rb");

#define DEFAULT_VERTEX_SHADER_PATH "shaders/Default.vert"
#define DEFAULT_FRAGMENT_SHADER_PATH "shaders/Default.frag"

typedef struct Shader {
    unsigned int id;
} Shader;

Shader newShader(const char* vertexShaderPath, const char* fragmentShaderPath);
void useShader(Shader shader);
void setBool(Shader shader, const char* name, bool value);
void setInt(Shader shader, const char* name, int value);
void setFloat(Shader shader, const char* name, float value);

#endif
