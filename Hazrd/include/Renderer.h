#include "../libs/glad/glad.h"
#include <sys/types.h>
#include <iostream>
using namespace std;


typedef struct BufferObjects {
    uint VAO = 1;
    uint VBO = 1;
    uint EBO = 2;
} BufferObjects;

class Renderer {
    public:
    static int numberOfTextures;

    public:
    static BufferObjects bindBuffersAndObjects(float vertices[], int verticesSize, const uint* indices, int indicesSize) {

        BufferObjects bo{0};

        glad_glGenVertexArrays(1, &bo.VAO);

        glad_glGenBuffers(1, &bo.VBO);

        glad_glGenBuffers(1, &bo.EBO);



        glad_glBindVertexArray(bo.VAO);

        glad_glBindBuffer(GL_ARRAY_BUFFER, bo.VBO);
        glad_glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

        glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.EBO);
        glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

        // position attribute
        glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glad_glEnableVertexAttribArray(0);
        // normal coord attribute
        glad_glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glad_glEnableVertexAttribArray(1);
        // texture coord attribute
        glad_glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glad_glEnableVertexAttribArray(2);

        return bo;

    }
};
