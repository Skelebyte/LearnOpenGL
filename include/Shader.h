#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <stdbool.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../libs/glad/glad.h"
#include "Utils.h"

#define DEFAULT_VERTEX_SHADER_SRC File::readFile("shaders/Default.vert", "rb");
#define DEFAULT_FRAGMENT_SHADER_SRC File::readFile("shaders/Default.frag", "rb");

#define DEFAULT_VERTEX_SHADER_PATH "shaders/Default.vert"
#define DEFAULT_FRAGMENT_SHADER_PATH "shaders/Default.frag"


class Shader {
    public:
    uint id;
    public:
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
        uint vertex;
        uint fragment;

        vertex = glad_glCreateShader(GL_VERTEX_SHADER);
        const char* vSrc = File::readFile(vertexShaderPath);
        glad_glShaderSource(vertex, 1, &vSrc, NULL);
        glad_glCompileShader(vertex);
        checkIfShaderCompileSuccess(vertex, "Vertex Shader: ");

        fragment = glad_glCreateShader(GL_FRAGMENT_SHADER);
        const char* fSrc = File::readFile(fragmentShaderPath);
        glad_glShaderSource(fragment, 1, &fSrc, NULL);
        glad_glCompileShader(fragment);
        checkIfShaderCompileSuccess(fragment, "Fragment Shader: ");

        id = glad_glCreateProgram();
        glad_glAttachShader(id, vertex);
        glad_glAttachShader(id, fragment);

        glad_glLinkProgram(id);
        checkIfShaderProgramLinkSuccess(id);

        glad_glDeleteShader(vertex);
        glad_glDeleteShader(fragment);
    }

    void use() {
        glad_glUseProgram(id);
    }
    void setBool(const char* name, bool value) {
        glad_glUniform1i(glad_glGetUniformLocation(id, name), (int)value);
    }
    void setInt(const char* name, int value) {
        glad_glUniform1i(glad_glGetUniformLocation(id, name), value);
    }
    void setFloat(const char* name, float value) {
        glad_glUniform1f(glad_glGetUniformLocation(id, name), value);
    }
    void setMat4(const char* name, glm::mat4 value) {
        glad_glUniformMatrix4fv(glad_glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(value));
    }

    private:
    void checkIfShaderCompileSuccess(uint shader, const char* desc) {
        int success;
        char infoLog[512];
        glad_glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glad_glGetShaderInfoLog(shader, 512, NULL, infoLog);
            Debug::log("Failed to compile shader: " + (string) infoLog, Severity::CRITICAL);
        }
    }
    void checkIfShaderProgramLinkSuccess(uint shaderProgram)  {
        int success;
        char infoLog[512];
        glad_glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if(!success) {
            glad_glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            Debug::log("Failed to link shader: " + (string) infoLog, Severity::CRITICAL);
        }
    }


};

#endif
