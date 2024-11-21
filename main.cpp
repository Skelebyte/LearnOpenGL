#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "libs/glad/glad.h"
#include "libs/stb_image.h"
#include "include/Shader.h"
#include "include/Utils.h"

using namespace std;

#define WIDTH 800
#define HEIGHT 600
#define uint unsigned int

void setUp() {
    cout<<"Setting up..."<<endl;
    if(glfwInit() == GLFW_FALSE) {
        cout<<"Failed to init GLFW!"<<endl;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    stbi_set_flip_vertically_on_load(true);
}
int cleanUp(GLFWwindow* window, uint vao, uint vbo, uint ebo) {
    cout<<"Cleaning up..."<<endl;
    glad_glDeleteVertexArrays(1, &vao);
    glad_glDeleteBuffers(1, &vbo);
    glad_glDeleteBuffers(1, &ebo);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

bool isWireframe = false;
void keyCallback(GLFWwindow*, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_F1 && action == GLFW_PRESS) {
        isWireframe = !isWireframe;
    }
}
float vertices[] = {
    // positions        // colors         // texture coords
    0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
    0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
};
unsigned int indices[] = { // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3 // second triangle
};
float textureCoords[] = {
    0.0f, 0.0f, // lower left corner
    1.0f, 0.0f, // lower right corner
    0.5f, 1.0f, // top corner
};

int main() {
    setUp();
    cout<<"Hi, mum!"<<endl;

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hi, mum!", NULL, NULL);
    if(window == NULL) {
        cout<<"Failed to create window!"<<endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout<<"Failed to init GLAD!"<<endl;
        glfwTerminate();
        return 2;
    }

    glad_glViewport(0, 0, WIDTH, HEIGHT);



    Shader shader = newShader(DEFAULT_VERTEX_SHADER_PATH, DEFAULT_FRAGMENT_SHADER_PATH);

    uint vao;
    uint vbo;
    uint ebo;
    glad_glGenVertexArrays(1, &vao);
    glad_glGenBuffers(1, &vbo);
    glad_glGenBuffers(1, &ebo);

    glad_glBindVertexArray(vao);

    glad_glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glad_glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glad_glEnableVertexAttribArray(0);
    // color attribute
    glad_glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glad_glEnableVertexAttribArray(1);
    // texture coord attribute
    glad_glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glad_glEnableVertexAttribArray(2);

    uint texture;
    glad_glGenTextures(1, &texture);
    glad_glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    unsigned char *data = stbi_load("data/SkelebyteSkull.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glad_glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout<<"Failed to load texture"<<endl;
    }
    stbi_image_free(data);

    glfwSetKeyCallback(window, keyCallback);

    while(!glfwWindowShouldClose(window)) {
        glad_glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glad_glClear(GL_COLOR_BUFFER_BIT);

        glad_glBindTexture(GL_TEXTURE_2D, texture);

        useShader(shader);
        glad_glBindVertexArray(vao);
        glad_glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);

        if(isWireframe) {
            glad_glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // draw in wireframe
        } else {
            glad_glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // draw with fill (not wireframe)
        }


        glfwPollEvents();
    }


    return cleanUp(window, vao, vbo, ebo);
}
