#include "../Utils.h"
using namespace std;

const char* readFile(const char* path) {
    std::ifstream file;

    file.open(path);

    if(file.fail()) {
        cout<<"Failed to read file: "<<path<<endl;
        return NULL;
    }

    char* buffer;
    int i = 0;
    int j;
    while((j = file.get()) != EOF) {
        buffer[i] = j;
        i++;
    }
    buffer[i] = '\0';

    file>>buffer;
    file.close();

    return buffer;

}

void checkIfShaderCompileSuccess(unsigned int shader, const char* desc) {
    int success;
    char infoLog[512];
    glad_glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glad_glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("%s: %s\n", desc, infoLog);
    }
}
void checkIfShaderProgramLinkSuccess(unsigned int shaderProgram)  {
    int success;
    char infoLog[512];
    glad_glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glad_glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("Shader Link: %s", infoLog);
    }
}
