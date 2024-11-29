#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include "Entity.h"
#include "Shader.h"
#include "Input.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

enum CameraMode {
    PERSPECTIVE = 0,
    ORTHOGRAPHIC = 1,
};

class Camera3D : public Entity {
    public:
    glm::mat4 view;
    int viewLocation;
    glm::mat4 projection;
    int projectionLocation;

    float fov = 70.0f;
    float farClippingPlane = 100000.0f;
    float nearClippingPlane = 0.01f;
    CameraMode mode = CameraMode::PERSPECTIVE;

    Shader shader;

    VECTOR3 orientation = FORWARD;
    VECTOR3 cameraUp = UP;

    public:
    Camera3D() {}
    Camera3D(Shader &m_shader) {
        shader = m_shader;
    }
    void updateCamera(int w, int h, const char* uniform) {
        view = glm::mat4(1.0f);
        projection = glm::mat4(1.0f);

        view = glm::lookAt(position, position + orientation, cameraUp);
        if(mode == CameraMode::PERSPECTIVE) {
            projection = glm::perspective(glm::radians(fov), (float)w / (float)h, nearClippingPlane, farClippingPlane);
        } else {
            projection = glm::ortho(0.0f, (float)w / fov, 0.0f, (float)h / fov, nearClippingPlane, farClippingPlane);
        }

        glad_glUniformMatrix4fv(glad_glGetUniformLocation(shader.id, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
    }
};

class EditorCamera3D : public Entity {
    public:
    glm::mat4 view;
    int viewLocation;
    glm::mat4 projection;
    int projectionLocation;

    float fov = 70.0f;
    float farClippingPlane = 100000.0f;
    float nearClippingPlane = 0.01f;
    CameraMode mode = CameraMode::PERSPECTIVE;

    Shader shader;
    GLFWwindow* window;
    bool isWireframe = false;
    bool noTextureMode = false;
    bool isPerspective = true;

    VECTOR3 orientation = FORWARD;
    VECTOR3 cameraUp = UP;


    Bind wireframe = Bind(Keys::KEY_F1, KeyAction::PRESS);
    Bind cameraMode = Bind(Keys::KEY_F3, KeyAction::PRESS);

    float speed = 0.05f;
    float sens = 100.0f;
    Bind moveUp = Bind(Keys::KEY_Q, KeyAction::HOLD);
    Bind moveDown = Bind(Keys::KEY_E, KeyAction::HOLD);
    Bind moveForward = Bind(Keys::KEY_W, KeyAction::HOLD);
    Bind moveBackward = Bind(Keys::KEY_S, KeyAction::HOLD);
    Bind moveLeft = Bind(Keys::KEY_A, KeyAction::HOLD);
    Bind moveRight = Bind(Keys::KEY_D, KeyAction::HOLD);
    Bind look = Bind(Keys::MOUSE_RIGHT, KeyAction::HOLD, IS_MOUSE_BIND);

    public:
    EditorCamera3D() {}
    EditorCamera3D(GLFWwindow* glfwWindow, Shader &m_shader) {
        shader = m_shader;
        window = glfwWindow;
    }
    void updateCamera(int w, int h, const char* uniform) {
        view = glm::mat4(1.0f);
        projection = glm::mat4(1.0f);

        view = glm::lookAt(position, position + orientation, cameraUp);
        if(mode == CameraMode::PERSPECTIVE) {
            projection = glm::perspective(glm::radians(fov), (float)w / (float)h, nearClippingPlane, farClippingPlane);
        } else {
            projection = glm::ortho(0.0f, (float)w / fov, 0.0f, (float)h / fov, nearClippingPlane, farClippingPlane);
        }

        glad_glUniformMatrix4fv(glad_glGetUniformLocation(shader.id, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));

        cameraInput(w, h);

        if(isWireframe) {
            glad_glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // draw in wireframe
        } else {
            glad_glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // draw with fill (not wireframe)
        }
        if(isPerspective) {
            mode = CameraMode::PERSPECTIVE;
        } else {
            mode = CameraMode::ORTHOGRAPHIC;
        }


    }
    private:
    void cameraInput(int w, int h) {

        Input::checkInput(window, wireframe);
        Input::checkInput(window, cameraMode);

        Input::checkInput(window, moveUp);
        Input::checkInput(window, moveDown);
        Input::checkInput(window, moveForward);
        Input::checkInput(window, moveBackward);
        Input::checkInput(window, moveLeft);
        Input::checkInput(window, moveRight);
        Input::checkInput(window, look);

        if(wireframe.isActive()) {
            isWireframe = !isWireframe;
        }

        if(cameraMode.isActive()) {
            isPerspective = !isPerspective;
        }

        // Up/Down
        if(moveUp.isActive()) {
            position += cameraUp * speed;
        }
        if(moveDown.isActive()) {
            position -= cameraUp * speed;
        }

        // Forwards/Backwards
        if(moveForward.isActive()) {
            position += orientation * speed;
        }
        if(moveBackward.isActive()) {
            position -= orientation * speed;
        }

        // Left/Right
        if(moveLeft.isActive()) {
            position -= glm::normalize(glm::cross(orientation, cameraUp)) * speed;
        }
        if(moveRight.isActive()) {
            position += glm::normalize(glm::cross(orientation, cameraUp)) * speed;
        }

        if(look.isActive()) {
            Input::hideCursor(window);
            VECTOR3 mousePos = Input::getMousePosition(window);


            float rotX = sens * (mousePos.y - ((float)h / 2)) / (float)h;
            float rotY = sens * (mousePos.x - ((float)w / 2)) / (float)w;

            VECTOR3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, cameraUp)));

            if(abs(glm::angle(newOrientation, cameraUp) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
                orientation = newOrientation;
            }

            orientation = glm::rotate(orientation, glm::radians(-rotY), cameraUp);

            Input::setMousePosition(window, VECTOR3((float)w / 2, (float)h / 2, 0.0f));
        } else {
            Input::showCursor(window);
        }
    }
};

/*
view = glm::lookAt(glm::vec3(val1, 0, val2), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
viewLocation = glad_glGetUniformLocation(shader->id, "view");
glad_glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

projection = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.01f, 100.0f);
projectionLocation = glad_glGetUniformLocation(shader->id, "projection");
glad_glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
*/

#endif
