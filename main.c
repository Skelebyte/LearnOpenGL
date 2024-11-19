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
void cleanup(GLFWwindow* window) {
    printf("shutting down...\n");
    glfwDestroyWindow(window);
    glfwTerminate();
    printf("Done!\n");
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
        glfwTerminate();
        return 2;
    }

    glad_glViewport(0, 0, WIDTH, HEIGHT);



    const char* vertexShaderSource = readFile("shaders/Default.vert", "rb");
    unsigned int vertexShader;
    vertexShader = glad_glCreateShader(GL_VERTEX_SHADER);
    glad_glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glad_glCompileShader(vertexShader);
    checkIfShaderCompileSuccess(vertexShader, "Vertex shader: ");

    const char* fragmentShaderSource = readFile("shaders/Default.frag", "rb");
    unsigned int fragmentShader;
    fragmentShader = glad_glCreateShader(GL_FRAGMENT_SHADER);
    glad_glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glad_glCompileShader(fragmentShader);
    checkIfShaderCompileSuccess(fragmentShader, "Fragment shader: ");

    unsigned int shaderProgram;
    shaderProgram = glad_glCreateProgram();

    // Attach shaders to the shader program
    glad_glAttachShader(shaderProgram, vertexShader);
    glad_glAttachShader(shaderProgram, fragmentShader);
    glad_glLinkProgram(shaderProgram);
    checkIfShaderProgramLinkSuccess(shaderProgram);

    glad_glUseProgram(shaderProgram);
    glad_glDeleteShader(vertexShader);
    glad_glDeleteShader(fragmentShader);

    unsigned int vao;
    glad_glGenVertexArrays(1, &vao);

    unsigned int vbo;
    glad_glGenBuffers(1, &vbo);
    glad_glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glad_glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glad_glBindVertexArray(vao);
    glad_glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glad_glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



    glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glad_glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents(); // register input/closing input

        // rendering...
        glad_glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glad_glClear(GL_COLOR_BUFFER_BIT);


        glad_glUseProgram(shaderProgram);
        glad_glBindVertexArray(vao);
        glad_glDrawArrays(GL_TRIANGLES, 0, 3);

        // game update...


        glfwSwapBuffers(window);
    }

    //glfwTerminate();

    cleanup(window);
    return 0;
}
