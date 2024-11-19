#define GLFW_INCLUDE_NONE // remove "OpenGL is already included (Line: 4) error" caused by GLFW and Glad
#include <stdio.h>
#include <stddef.h>
#include <GLFW/glfw3.h>
#include "libs/glad/glad.h"
#include "Utils.h"

#define WIDTH 800
#define HEIGHT 600

void setup() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
void shutdown() {
    glfwTerminate();
}

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
};

int main() {
    setup();
    printf("Hi, mum!\n");

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hi, mum!", NULL, NULL);
    if(window == NULL) {
        printf("Failed to create window!\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD!\n");
        return 2;
    }

    glad_glViewport(0, 0, WIDTH, HEIGHT);

    unsigned int vbo;
    glad_glGenBuffers(1, &vbo);
    glad_glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glad_glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const char* vertexShaderSource = readFile("shaders/Default.vert", "rb");
    unsigned int vertexShader;
    vertexShader = glad_glCreateShader(GL_VERTEX_SHADER);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents(); // register input/closing input

        // rendering...
        glad_glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glad_glClear(GL_COLOR_BUFFER_BIT);

        // game update...

        glfwSwapBuffers(window);
    }

    shutdown();
    return 0;
}
