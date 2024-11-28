#include "../libs/glad/glad.h"
#include <sys/types.h>
#include <iostream>
using namespace std;

// class BufferObjects {
//     public:
//     BufferObjects(const void* vertices, const void* indices) {
//         uint vao;
//         uint vbo;
//         uint ebo;

//         glad_glGenVertexArrays(1, &vao);
//         glad_glGenBuffers(1, &vbo);
//         glad_glGenBuffers(1, &ebo);

//         glad_glBindVertexArray(vao);

//         glad_glBindBuffer(GL_ARRAY_BUFFER, vbo);
//         glad_glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//         glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//         glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//         // position attribute
//         glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//         glad_glEnableVertexAttribArray(0);
//         // texture coord attribute
//         glad_glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//         glad_glEnableVertexAttribArray(1);

//         VAO = vao;
//         VBO = vbo;
//         EBO = ebo;

//         cout<<"bound stuff!"<<endl;
//     }
//     uint VAO;
//     uint VBO;
//     uint EBO;
// };

typedef struct BufferObjects {
    uint VAO = 1;
    uint VBO = 1;
    uint EBO = 2;
} BufferObjects;

class Renderer {
    public:
    static int numberOfTextures;
};

inline BufferObjects bindBuffersAndObjects(float vertices[], int verticesSize, const uint* indices, int indicesSize) {

    cout<<indices[1]<<endl;

    BufferObjects bo{0};

    glad_glGenVertexArrays(1, &bo.VAO);
    std::cout << "Generated VAO: " << bo.VAO << "\n";

    glad_glGenBuffers(1, &bo.VBO);
    std::cout << "Generated VBO: " << bo.VBO << "\n";

    glad_glGenBuffers(1, &bo.EBO);
    std::cout << "Generated EBO: " << bo.EBO << "\n";



    glad_glBindVertexArray(bo.VAO);

    glad_glBindBuffer(GL_ARRAY_BUFFER, bo.VBO);
    glad_glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.EBO);
    glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

    // position attribute
    glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glad_glEnableVertexAttribArray(0);
    // texture coord attribute
    glad_glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glad_glEnableVertexAttribArray(1);

    cout<<"bound stuff!"<<endl;


    // GLint currentVAO, currentVBO, currentEBO;
    // glad_glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVAO);
    // glad_glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currentVBO);
    // glad_glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &currentEBO);
    // std::cout << "VAO: " << currentVAO << ", VBO: " << currentVBO << ", EBO: " << currentEBO << "\n";

    return bo;

}
