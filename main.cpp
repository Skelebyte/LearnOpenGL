
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/geometric.hpp>
#include <iostream>
#include <unistd.h>
#include "Hazrd/Hazrd.h"
#include "Hazrd/include/GameObjects.h"

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



EditorCamera3D camera;
Shader shader;
// Camera3D camera;

// Bind wireframe = Bind(Keys::KEY_F1, KeyAction::PRESS);
// Bind textureMode = Bind(Keys::KEY_F2, KeyAction::PRESS);
// Bind cameraMode = Bind(Keys::KEY_F3, KeyAction::PRESS);

// float speed = 0.05f;
// float sens = 100.0f;
// Bind moveUp = Bind(Keys::KEY_Q, KeyAction::HOLD);
// Bind moveDown = Bind(Keys::KEY_E, KeyAction::HOLD);
// Bind moveForward = Bind(Keys::KEY_W, KeyAction::HOLD);
// Bind moveBackward = Bind(Keys::KEY_S, KeyAction::HOLD);
// Bind moveLeft = Bind(Keys::KEY_A, KeyAction::HOLD);
// Bind moveRight = Bind(Keys::KEY_D, KeyAction::HOLD);
// Bind look = Bind(Keys::MOUSE_RIGHT, KeyAction::HOLD, IS_MOUSE_BIND);


void input(GLFWwindow* window) {
    // Input::checkInput(window, wireframe);
    // Input::checkInput(window, textureMode);
    // Input::checkInput(window, cameraMode);

    // Input::checkInput(window, moveUp);
    // Input::checkInput(window, moveDown);
    // Input::checkInput(window, moveForward);
    // Input::checkInput(window, moveBackward);
    // Input::checkInput(window, moveLeft);
    // Input::checkInput(window, moveRight);
    // Input::checkInput(window, look);

    // if(wireframe.isActive()) {
    //     isWireframe = !isWireframe;
    //     Debug::log("Toggle wireframe", Severity::INFO);
    // }
    // if(textureMode.isActive()) {
    //     noTextureMode = !noTextureMode;
    // }
    // if(cameraMode.isActive()) {
    //     isPerspective = !isPerspective;
    // }

    // // Up/Down
    // if(moveUp.isActive()) {
    //     camera.position += camera.cameraUp * speed;
    // }
    // if(moveDown.isActive()) {
    //     camera.position -= camera.cameraUp * speed;
    // }

    // // Forwards/Backwards
    // if(moveForward.isActive()) {
    //     camera.position += camera.orientation * speed;
    // }
    // if(moveBackward.isActive()) {
    //     camera.position -= camera.orientation * speed;
    // }

    // // Left/Right
    // if(moveLeft.isActive()) {
    //     camera.position -= glm::normalize(glm::cross(camera.orientation, camera.cameraUp)) * speed;
    // }
    // if(moveRight.isActive()) {
    //     camera.position += glm::normalize(glm::cross(camera.orientation, camera.cameraUp)) * speed;
    // }

    // if(look.isActive()) {
    //     Input::hideCursor(window);
    //     VECTOR3 mousePos = Input::getMousePosition(window);


    //     float rotX = sens * (mousePos.y - ((float)HEIGHT / 2)) / (float)HEIGHT;
    //     float rotY = sens * (mousePos.x - ((float)WIDTH / 2)) / (float)WIDTH;

    //     VECTOR3 newOrientation = glm::rotate(camera.orientation, glm::radians(-rotX), glm::normalize(glm::cross(camera.orientation, camera.cameraUp)));

    //     if(abs(glm::angle(newOrientation, camera.cameraUp) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
    //         camera.orientation = newOrientation;
    //     }

    //     camera.orientation = glm::rotate(camera.orientation, glm::radians(-rotY), camera.cameraUp);

    //     Input::setMousePosition(window, VECTOR3((float)WIDTH / 2, (float)HEIGHT / 2, 0.0f));
    // } else {
    //     Input::showCursor(window);
    // }
}
float vertices[] = {
    // back face
	-0.5f, -0.5f, -0.5f,
	0.0f, 0.0f, // bottom-left
	0.5f, 0.5f, -0.5f,
	1.0f, 1.0f, // top-right
	0.5f, -0.5f, -0.5f,
	1.0f, 0.0f, // bottom-right
	0.5f, 0.5f, -0.5f,
	1.0f, 1.0f, // top-right
	-0.5f, -0.5f, -0.5f,
	0.0f, 0.0f, // bottom-left
	-0.5f, 0.5f, -0.5f,
	0.0f, 1.0f, // top-left
	// front face
	-0.5f, -0.5f, 0.5f,
	0.0f, 0.0f, // bottom-left
	0.5f, -0.5f, 0.5f,
	1.0f, 0.0f, // bottom-right
	0.5f, 0.5f, 0.5f,
	1.0f, 1.0f, // top-right
	0.5f, 0.5f, 0.5f,
	1.0f, 1.0f, // top-right
	-0.5f, 0.5f, 0.5f,
	0.0f, 1.0f, // top-left
	-0.5f, -0.5f, 0.5f,
	0.0f, 0.0f, // bottom-left
	// left face
	-0.5f, 0.5f, 0.5f,
	1.0f, 0.0f, // top-right
	-0.5f, 0.5f, -0.5f,
	1.0f, 1.0f, // top-left
	-0.5f, -0.5f, -0.5f,
	0.0f, 1.0f, // bottom-left
	-0.5f, -0.5f, -0.5f,
	0.0f, 1.0f, // bottom-left
	-0.5f, -0.5f, 0.5f,
	0.0f, 0.0f, // bottom-right
	-0.5f, 0.5f, 0.5f,
	1.0f, 0.0f, // top-right
	// right face
	0.5f, 0.5f, 0.5f,
	1.0f, 0.0f, // top-left
	0.5f, -0.5f, -0.5f,
	0.0f, 1.0f, // bottom-right
	0.5f, 0.5f, -0.5f,
	1.0f, 1.0f, // top-right
	0.5f, -0.5f, -0.5f,
	0.0f, 1.0f, // bottom-right
	0.5f, 0.5f, 0.5f,
	1.0f, 0.0f, // top-left
	0.5f, -0.5f, 0.5f,
	0.0f, 0.0f, // bottom-left
	// bottom face
	-0.5f, -0.5f, -0.5f,
	0.0f, 1.0f, // top-right
	0.5f, -0.5f, -0.5f,
	1.0f, 1.0f, // top-left
	0.5f, -0.5f, 0.5f,
	1.0f, 0.0f, // bottom-left
	0.5f, -0.5f, 0.5f,
	1.0f, 0.0f, // bottom-left
	-0.5f, -0.5f, 0.5f,
	0.0f, 0.0f, // bottom-right
	-0.5f, -0.5f, -0.5f,
	0.0f, 1.0f, // top-right
	// top face
	-0.5f, 0.5f, -0.5f,
	0.0f, 1.0f, // top-left
	0.5f, 0.5f, 0.5f,
	1.0f, 0.0f, // bottom-right
	0.5f, 0.5f, -0.5f,
	1.0f, 1.0f, // top-right
	0.5f, 0.5f, 0.5f,
	1.0f, 0.0f, // bottom-right
	-0.5f, 0.5f, -0.5f,
	0.0f, 1.0f, // top-left
	-0.5f, 0.5f, 0.5f,
	0.0f, 0.0f // bottom-left
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
    glad_glEnable(GL_CULL_FACE);
    glad_glCullFace(GL_BACK);
    glad_glFrontFace(GL_CCW);


    shader = Shader(DEFAULT_VERTEX_SHADER_PATH, DEFAULT_FRAGMENT_SHADER_PATH);
    camera = EditorCamera3D(window, shader);
    // camera = Camera3D(shader);
    // camera.mode = CameraMode::PERSPECTIVE;


    BufferObjects bufferObjects = bindBuffersAndObjects(vertices, sizeof(vertices), indices, sizeof(indices));


    uint texture = Texture::load("data/textures/alita1.jpg", ImageType::JPG);
    uint noTexture = Texture::load("data/engine/NoTexture_Grey.png", ImageType::PNG);




    // camera.position.z = 10;

    while(!glfwWindowShouldClose(window)) {

        glfwGetWindowSize(window, &WIDTH, &HEIGHT);

        input(window);

        glad_glViewport(0, 0, WIDTH, HEIGHT);

        glad_glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        shader.use();
        glad_glBindVertexArray(bufferObjects.VAO);
        for(uint i = 0; i < 10; i++) {
            if(i == 0) {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = (float)glfwGetTime() * (20.0f * i);
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                shader.setMat4("model", model);
                glad_glBindTexture(GL_TEXTURE_2D, texture);
                glad_glDrawArrays(GL_TRIANGLES, 0, 36);
            } else {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = (float)glfwGetTime() * (20.0f * i);
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                shader.setMat4("model", model);
                glad_glBindTexture(GL_TEXTURE_2D, noTexture);
                glad_glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }


        glfwSwapBuffers(window);

        camera.updateCamera(WIDTH, HEIGHT, "cameraMatrix");

        // if(isWireframe) {
        //     glad_glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // draw in wireframe
        // } else {
        //     glad_glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // draw with fill (not wireframe)
        // }
        // if(isPerspective) {
        //     camera.mode = CameraMode::PERSPECTIVE;
        // } else {
        //     camera.mode = CameraMode::ORTHOGRAPHIC;
        // }


        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 0.0f, 0.0f));
        int modelLocation = glad_glGetUniformLocation(shader.id, "model");
        glad_glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

        // camera.updateCamera(WIDTH, HEIGHT, "cameraMatrix");


        glfwPollEvents();





    }


    return cleanUp(window, bufferObjects);
}
