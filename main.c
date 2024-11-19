#define GLFW_INCLUDE_NONE // remove "OpenGL is already included (Line: 4) error" caused by GLFW and Glad
#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "libs/glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "libs/stb_image.h"
#include "Shader.h"

#define WIDTH 800
#define HEIGHT 600

void setup() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    stbi_set_flip_vertically_on_load(true);
}
void cleanup(GLFWwindow* window) {
    printf("shutting down...\n");
    glfwDestroyWindow(window);
    glfwTerminate();
}
bool isWireframe = false;
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
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

    Shader shader = newShader(DEFAULT_VERTEX_SHADER_PATH, DEFAULT_FRAGMENT_SHADER_PATH);

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
    glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glad_glEnableVertexAttribArray(0);
    // color attribute
    glad_glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glad_glEnableVertexAttribArray(1);
    // texture coords attribute
    glad_glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
    glad_glEnableVertexAttribArray(2);

    unsigned int texture;
    glad_glGenTextures(1, &texture);
    glad_glBindTexture(GL_TEXTURE_2D, texture);

    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load("data/SkelebyteSkull.png", &width, &height, &nrChannels, 0); // need to create a utils thing to load
                                                                                                 // everything other than .png files with
                                                                                                 // GL_RGB (GL_RGBA for .png)


    if(data) {
        glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glad_glGenerateMipmap(GL_TEXTURE_2D);


        stbi_image_free(data);
    } else {
        printf("failed to read image...\n");
    }



    glfwSetKeyCallback(window, keyCallback);


    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents(); // register input/closing input

        // rendering...
        glad_glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glad_glClear(GL_COLOR_BUFFER_BIT);



        useShader(shader);
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glad_glGetUniformLocation(shader.id, "ourColor");
        glad_glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);




        glad_glBindTexture(GL_TEXTURE_2D, texture);

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
