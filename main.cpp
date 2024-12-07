
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/geometric.hpp>
#include <iostream>
#include <unistd.h>
#include "Hazrd/Hazrd.h"
#include "Hazrd/include/Defines.h"
#include "Hazrd/include/Input.h"
#include "Hazrd/include/Material.h"
#include "Hazrd/include/Texture.h"

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
}
float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};



uint indices[] = { // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3 // second triangle
};

// worldspace positions of cubes
glm::vec3 cubePositions[] = {
    glm::vec3( 1.0f,  1.0f,  1.0f),
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
    // glad_glEnable(GL_CULL_FACE);
    // glad_glCullFace(GL_FRONT);
    // glad_glFrontFace(GL_CCW);


    shader = Shader(DEFAULT_VERTEX_SHADER_PATH, DEFAULT_FRAGMENT_SHADER_PATH);
    camera = EditorCamera3D(window, shader);
    camera.position = VEC3(1.0f, 1.0f, 1.0f);


    BufferObjects bufferObjects = Renderer::bindBuffersAndObjects(vertices, sizeof(vertices), indices, sizeof(indices));

    Texture texture;
    texture.load("data/textures/alita1.jpg", ImageFormat::JPG);

    Texture noTexture;
    noTexture.load("data/engine/NoTexture_Grey.png", ImageFormat::PNG);
    Texture noTextureSpecular;
    noTextureSpecular.load("data/engine/NoTexture_Specular.png", ImageFormat::PNG);
    cout<<GL_TEXTURE0 + noTextureSpecular.id<<" <-- spec notexture + texture0"<<endl;
    cout<<GL_TEXTURE0<<" <-- texture0"<<endl;

    // Model model = Model::load("data/models/defaults/cube/Cube.obj", ModelFormat::OBJ);



    // Material lightMaterial = Material("data/engine/NoTexture_White.png", ImageFormat::PNG);
    // Material cubeMaterial = Material();
    //
    Bind moveLight = Bind(Keys::KEY_E, KeyAction::HOLD);

    while(!glfwWindowShouldClose(window)) {
        Input::checkInput(window, moveLight);

        glfwGetWindowSize(window, &WIDTH, &HEIGHT);

        input(window);

        glad_glViewport(0, 0, WIDTH, HEIGHT);

        VEC3 ambientColor = VEC3(0.1f, 0.1f, 0.1f);

        glad_glClearColor(ambientColor.x, ambientColor.y, ambientColor.z, 1.0f);

        glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        shader.setVec3("cameraPosition", camera.position);


        // shader.setVec3("light.position", VEC3(-0.2f, -1.0f, -0.3f));
        shader.setVec3("light.ambient", VEC3(0.1f, 0.1f, 0.1f));
        shader.setVec3("light.diffuse", VEC3(1.0f, 1.0f, 1.0f));
        shader.setVec3("light.specular", VEC3(1.0f, 1.0f, 1.0f));
        shader.setFloat("light.constant", 1.0f);
        shader.setFloat("light.linear", 0.09f);
        shader.setFloat("light.quadratic", 0.032f);


        // A note about the texture loading for meshes...
        /*
            it looks like if i do glad_glBindTexture() before i draw the mesh with glad_glDrawArrays
            it will give the mesh drawn that texture, which is nice.
        */
        shader.setInt("material.texture", texture.id);
        shader.setVec3("material.baseColor", VEC3(1.0f, 1.0f, 1.0f));
        shader.setInt("material.specular", noTextureSpecular.id);
        shader.setFloat("material.shininess", 32.0f);



        if(moveLight.isActive()) {
            shader.setVec3("light.position", camera.position);
        }

        glad_glBindVertexArray(bufferObjects.VAO);
        for(uint i = 0; i < 10; i++) {
            if(i == 0) {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = (float)glfwGetTime() * (20.0f * i);
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                shader.setMat4("model", model);
                // shader.setVec3("objectColor", VEC3(100.0f, 100.0f, 100.0f));

                glad_glActiveTexture(GL_TEXTURE0 + texture.id);
                glad_glBindTexture(GL_TEXTURE_2D, texture.id);
                glad_glActiveTexture(GL_TEXTURE0 + noTextureSpecular.id); // <-- only works if i have multiple shaders and meshes with their own shader (which is the plan)
                glad_glBindTexture(GL_TEXTURE_2D, noTextureSpecular.id);
                glad_glDrawArrays(GL_TRIANGLES, 0, 36);
            } else {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = (float)glfwGetTime() * (20.0f * i);
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                shader.setMat4("model", model);
                // shader.setVec3("objectColor", VEC3(1.0f, 1.0f, 0.31f));
                shader.setInt("material.texture", noTexture.id);

                glad_glActiveTexture(GL_TEXTURE0 + noTexture.id); // <-- only works if i have multiple shaders and meshes with their own shader (which is the plan)
                glad_glBindTexture(GL_TEXTURE_2D, noTexture.id);
                glad_glActiveTexture(GL_TEXTURE0 + noTextureSpecular.id); // <-- only works if i have multiple shaders and meshes with their own shader (which is the plan)
                glad_glBindTexture(GL_TEXTURE_2D, noTextureSpecular.id);

                glad_glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }



        glfwSwapBuffers(window);

        camera.updateCamera(WIDTH, HEIGHT, "cameraMatrix");

        glad_glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwPollEvents();


    }
    return cleanUp(window, bufferObjects);
}
