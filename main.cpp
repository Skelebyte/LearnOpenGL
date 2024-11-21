#include <glm/ext/matrix_clip_space.hpp>
#include <glm/trigonometric.hpp>
#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "libs/glad/glad.h"
#include "include/Shader.h"
#include "include/Utils.h"
#include "include/Texture.h"

using namespace std;

int WIDTH = 800;
int HEIGHT = 600;
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
    // positions         // texture coords
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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
// worldspace positions of cubes
glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

int main() {
    setUp();
    cout<<"Hi, mum!"<<endl;

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearningOpenGL", NULL, NULL);
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


    glad_glEnable(GL_DEPTH_TEST);


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
    glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glad_glEnableVertexAttribArray(0);
    // texture coord attribute
    glad_glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glad_glEnableVertexAttribArray(1);

    uint texture = loadTexture("data/SkelebyteSkull.png", ImageType::PNG);

    glfwSetKeyCallback(window, keyCallback);

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

    glm::mat4 view;
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));


    while(!glfwWindowShouldClose(window)) {

        glfwGetWindowSize(window, &WIDTH, &HEIGHT);

        glad_glViewport(0, 0, WIDTH, HEIGHT);

        glad_glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glad_glBindTexture(GL_TEXTURE_2D, texture);

        useShader(shader);
        glad_glBindVertexArray(vao);
        for(uint i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = (float)glfwGetTime() * (20.0f * i);
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            setMat4(shader, "model", model);
            glad_glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glad_glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);

        if(isWireframe) {
            glad_glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // draw in wireframe
        } else {
            glad_glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // draw with fill (not wireframe)
        }

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 0.0f, 0.0f));
        int modelLocation = glad_glGetUniformLocation(shader.id, "model");
        glad_glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
        glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

        float radius = 00.0f;
        float speed = 0.5f;
        glm::mat4 view;
        float cameraX = sin(glfwGetTime() * speed) * radius;
        float cameraZ = cos(glfwGetTime() * speed) * radius;

        view = glm::lookAt(glm::vec3(cameraX, 0.0f, cameraZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        int viewLocation = glad_glGetUniformLocation(shader.id, "view");
        glad_glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));


        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.01f, 100.0f);
        int projectionLocation = glad_glGetUniformLocation(shader.id, "projection");
        glad_glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));



        glfwPollEvents();
    }


    return cleanUp(window, vao, vbo, ebo);
}
