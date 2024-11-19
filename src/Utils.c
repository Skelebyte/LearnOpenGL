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
