#define GLFW_INCLUDE_NONE // remove "OpenGL is already included (Line: 4) error" caused by GLFW and Glad
#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include <stdbool.h>
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
bool isWireframe = false;
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_F1 && action == GLFW_PRESS) {
        isWireframe = !isWireframe;
    }
}


float vertices[] = {
    // positions        // colors
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
    0.0f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // top
};
unsigned int indices[] = { // note that we start from 0!
    0, 1, 2, // first triangle
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

    glad_glBindVertexArray(vao);

    glad_glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glad_glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



    unsigned int ebo;
    glad_glGenBuffers(1, &ebo);

    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
    (void*)0);
    glad_glEnableVertexAttribArray(0);
    // color attribute
    glad_glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
    (void*)(3* sizeof(float)));
    glad_glEnableVertexAttribArray(1);




    glfwSetKeyCallback(window, keyCallback);



    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents(); // register input/closing input

        // rendering...
        glad_glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glad_glClear(GL_COLOR_BUFFER_BIT);



        glad_glUseProgram(shaderProgram);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glad_glGetUniformLocation(shaderProgram, "ourColor");
        glad_glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        glad_glBindVertexArray(vao);
        glad_glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glad_glBindVertexArray(0);

        // glad_glDrawArrays(GL_TRIANGLES, 0, 3);

        // game update...
        if(isWireframe) {
            glad_glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // draw in wireframe
        } else {
            glad_glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // draw with fill (not wireframe)
        }


        glfwSwapBuffers(window);
    }

    //glfwTerminate();

    cleanup(window);
    return 0;
}
