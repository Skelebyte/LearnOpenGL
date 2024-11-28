
#include <iostream>
#include <unistd.h>
#include "include/Hazrd.h"

using namespace std;

int WIDTH = 800;
int HEIGHT = 600;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);



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
int cleanUp(GLFWwindow* window, BufferObjects objects) {
    cout<<"Cleaning up..."<<endl;
    glad_glDeleteVertexArrays(1, &objects.VAO);
    glad_glDeleteBuffers(1, &objects.VBO);
    glad_glDeleteBuffers(1, &objects.EBO);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

bool isWireframe = false;
bool noTextureMode = false;
bool pressed;

Bind* wireframe = new Bind(Keys::KEY_F1, KeyAction::PRESS);
Bind* textureMode = new Bind(Keys::KEY_F2, KeyAction::PRESS);

void input(GLFWwindow* window) {
    Input.checkInput(window, wireframe);
    Input.checkInput(window, textureMode);

    if(wireframe->isActive()) {
        isWireframe = !isWireframe;
    }
    if(textureMode->isActive()) {
        noTextureMode = !noTextureMode;
    }

    // if(glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS && !pressed) {
    //     isWireframe = !isWireframe;
    //     pressed = true;
    // }
    // if(glfwGetKey(window, GLFW_KEY_F1) == GLFW_RELEASE && pressed) {
    //     pressed = false;
    // }

    // if(glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS && !pressed) {
    //     noTextureMode = !noTextureMode;
    //     pressed = true;
    // }
    // if(glfwGetKey(window, GLFW_KEY_F2) == GLFW_RELEASE && pressed) {
    //     pressed = false;
    // }
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
uint indices[] = { // note that we start from 0!
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


    Shader* shader = new Shader(DEFAULT_VERTEX_SHADER_PATH, DEFAULT_FRAGMENT_SHADER_PATH);



    BufferObjects bufferObjects = bindBuffersAndObjects(vertices, sizeof(vertices), indices, sizeof(indices));


    uint texture = Texture::load("data/dude.png", ImageType::PNG);
    uint noTexture = Texture::load("data/engine/NoTexture_Grey.png", ImageType::PNG);


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

        input(window);

        glad_glViewport(0, 0, WIDTH, HEIGHT);

        glad_glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        shader->use();
        glad_glBindVertexArray(bufferObjects.VAO);
        for(uint i = 0; i < 10; i++) {
            if(i == 0) {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = (float)glfwGetTime() * (20.0f * i);
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                shader->setMat4("model", model);
                glad_glBindTexture(GL_TEXTURE_2D, texture);
                glad_glDrawArrays(GL_TRIANGLES, 0, 36);
            } else {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = (float)glfwGetTime() * (20.0f * i);
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                shader->setMat4("model", model);
                glad_glBindTexture(GL_TEXTURE_2D, noTexture);
                glad_glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }


        glfwSwapBuffers(window);

        if(isWireframe) {
            glad_glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // draw in wireframe
        } else {
            glad_glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // draw with fill (not wireframe)
        }
        // if(noTextureMode) {
        //     glad_glBindTexture(GL_TEXTURE_2D, noTexture);
        // } else {
        //     glad_glBindTexture(GL_TEXTURE_2D, texture);
        // }

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 0.0f, 0.0f));
        int modelLocation = glad_glGetUniformLocation(shader->id, "model");
        glad_glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));



        float radius = 10.0f;
        float speed = 0.5f;
        glm::mat4 view;
        float cameraX = sin(glfwGetTime() * speed) * radius;
        float cameraZ = cos(glfwGetTime() * speed) * radius;

        view = glm::lookAt(glm::vec3(cameraX, 0.0f, cameraZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        int viewLocation = glad_glGetUniformLocation(shader->id, "view");
        glad_glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));


        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.01f, 100.0f);
        int projectionLocation = glad_glGetUniformLocation(shader->id, "projection");
        glad_glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

        glfwPollEvents();

    }


    return cleanUp(window, bufferObjects);
}
