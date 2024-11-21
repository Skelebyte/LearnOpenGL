#include "../include/Utils.h"
using namespace std;

const char* readFile(const char* path) {
    std::ifstream file;

    file.open(path, std::ios::binary | std::ios::ate);

    if(file.fail()) {
        cout<<"Failed to read file: "<<path<<endl;
        return NULL;
    }
    streamsize size = (streamsize)file.tellg();
    file.seekg(0, ios::beg);
    char* buffer = new char[size + 1];
    if(!file.read(buffer, size)) {
        cout<<"Failed to read file: "<<path<<endl;
        delete[] buffer;
        return NULL;
    }
    buffer[size] = '\0';

    file.close();

    return buffer;

}

void checkIfShaderCompileSuccess(unsigned int shader, const char* desc) {
    int success;
    char infoLog[512];
    glad_glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glad_glGetShaderInfoLog(shader, 512, NULL, infoLog);
        cout<<desc<<": "<<infoLog<<endl;
    }
}
void checkIfShaderProgramLinkSuccess(unsigned int shaderProgram)  {
    int success;
    char infoLog[512];
    glad_glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glad_glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        cout<<"Shader Link: "<<infoLog<<endl;
    }
}
