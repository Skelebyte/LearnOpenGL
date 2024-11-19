#include "../Shader.h"

Shader newShader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    Shader temp;

    unsigned int vertex;
    unsigned int fragment;

    vertex = glad_glCreateShader(GL_VERTEX_SHADER);
    const char* vSrc = readFile(vertexShaderPath);
    glad_glShaderSource(vertex, 1, &vSrc, NULL);
    glad_glCompileShader(vertex);
    checkIfShaderCompileSuccess(vertex, "Vertex Shader: ");

    fragment = glad_glCreateShader(GL_FRAGMENT_SHADER);
    const char* fSrc = readFile(fragmentShaderPath);
    glad_glShaderSource(fragment, 1, &fSrc, NULL);
    glad_glCompileShader(fragment);
    checkIfShaderCompileSuccess(fragment, "Fragment Shader: ");

    temp.id = glad_glCreateProgram();
    glad_glAttachShader(temp.id, vertex);
    glad_glAttachShader(temp.id, fragment);

    glad_glLinkProgram(temp.id);
    checkIfShaderProgramLinkSuccess(temp.id);

    glad_glDeleteShader(vertex);
    glad_glDeleteShader(fragment);


    return temp;
}

void useShader(Shader shader) {
    glad_glUseProgram(shader.id);
}

void setBool(Shader shader, const char* name, bool value) {
    glad_glUniform1i(glad_glGetUniformLocation(shader.id, name), (int)value);
}

void setInt(Shader shader, const char* name, int value) {
    glad_glUniform1i(glad_glGetUniformLocation(shader.id, name), value);
}

void setFloat(Shader shader, const char* name, float value) {
    glad_glUniform1f(glad_glGetUniformLocation(shader.id, name), value);
}
