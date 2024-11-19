#include "../Utils.h"

char* readFile(const char* path, char* style) {
    FILE* file;
    file = fopen(path, style);
    if(file == NULL) {
        printf("Failed to read file from: %s\n", path);
        // segfault, crash program.
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);
    char* buffer = (char*)malloc((fileSize + 1) * sizeof(char));
    int i = 0;
    int j;
    while((j = fgetc(file)) != EOF) {
        buffer[i] = j;
        i++;
    }

    buffer[i] = '\0';

    rewind(file);
    fclose(file);

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
