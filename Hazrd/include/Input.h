#ifndef INPUT_H
#define INPUT_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include "Utils.h"
#include "Defines.h"

using namespace std;

#define IS_MOUSE_BIND 1
#define DISABLE_CURSOR 1

enum Keys {
    KEY_UNDEFINED = -1,

    // Mouse Buttons
    MOUSE_LEFT = 0,
    MOUSE_RIGHT = 1,
    MOUSE_MIDDLE = 2,

    // letters
    KEY_A = 65,
    KEY_B = 66,
    KEY_C = 67,
    KEY_D = 68,
    KEY_E = 69,
    KEY_F = 70,
    KEY_G = 71,
    KEY_H = 72,
    KEY_I = 73,
    KEY_J = 74,
    KEY_K = 75,
    KEY_L = 76,
    KEY_M = 77,
    KEY_N = 78,
    KEY_O = 79,
    KEY_P = 80,
    KEY_Q = 81,
    KEY_R = 82,
    KEY_S = 83,
    KEY_T = 84,
    KEY_U = 85,
    KEY_V = 86,
    KEY_W = 87,
    KEY_X = 88,
    KEY_Y = 89,
    KEY_Z = 90,

    // numbers

    // function keys
    KEY_F1 = 290,
    KEY_F2 = 291,
    KEY_F3 = 292,
    KEY_F4 = 293,
    KEY_F5 = 294,
    KEY_F6 = 295,
    KEY_F7 = 296,
    KEY_F8 = 297,
    KEY_F9 = 298,
    KEY_F10 = 299,
    KEY_F11 = 300,
    KEY_F12 = 301,

    // arrow keys
    KEY_RIGHT = 262,
    KEY_LEFT = 263,
    KEY_DOWN = 264,
    KEY_UP = 265,


};

enum KeyAction {
    RELEASE = 0,
    PRESS = 1,
    HOLD = 2,
};

class Bind {

    public:
    Keys key;
    // How the key needs to be pressed in order to be active
    KeyAction action = KeyAction::PRESS;

    // Do not manually set this value.
    bool active;

    // Do not manually set this value
    bool pressed;

    // Do not manually set this value
    bool isMouse;


    public:
    Bind(Keys k, KeyAction ka, int isMouseInput = 0) {
        key = k;
        action = ka;
        if(isMouseInput != 0) {
            isMouse = true;
        }
    }

    bool isActive() {
        if(active == true && pressed == true) {
            if(action != KeyAction::HOLD) {
                active = false;
            }
            return pressed;
        }
        return false;
    };
};

class Input {

    public:
    static void checkInput(GLFWwindow* window, Bind& bind) {
        switch(bind.action) {
            case KeyAction::PRESS:
                checkInputPress(window, bind);
                break;
            case KeyAction::RELEASE:
                checkInputRelease(window, bind);
                break;
            case KeyAction::HOLD:
                checkInputHold(window, bind);
        };
    }

    static void showCursor(GLFWwindow* window) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    static void hideCursor(GLFWwindow* window, int shouldDisable = 0) {
        if(shouldDisable != 0) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        }
    }

    static VEC2 getMousePosition(GLFWwindow* window) {
        double x;
        double y;

        glfwGetCursorPos(window, &x, &y);

        return VEC2((float)x, (float)y);

    }

    static void setMousePosition(GLFWwindow* window, VEC2 position) {
        glfwSetCursorPos(window, position.x, position.y);
    }

    private:
    // Check if key is pressed/is down
    static void checkInputPress(GLFWwindow* window, Bind& bind) {

        if(bind.isMouse == 1) {
            if(glfwGetMouseButton(window, bind.key) == GLFW_PRESS && !bind.pressed) {
                bind.active = true;
                bind.pressed = true;
            }
            if(glfwGetMouseButton(window, bind.key) == GLFW_RELEASE && bind.pressed) {
                bind.active = false;
                bind.pressed = false;
            }
            return;
        }

        if(glfwGetKey(window, bind.key) == GLFW_PRESS && !bind.pressed) {
            bind.active = true;
            bind.pressed = true;
        }
        if(glfwGetKey(window, bind.key) == GLFW_RELEASE && bind.pressed) {
            bind.active = false;
            bind.pressed = false;
        }
    }
    // Check if key is released/is up
    static void checkInputRelease(GLFWwindow* window, Bind& bind) {

        if(bind.isMouse == 1) { // glfwGetMouseButton
            if(glfwGetMouseButton(window, bind.key) == GLFW_PRESS && bind.pressed) {
                bind.active = false;
                bind.pressed = false;
            }
            if(glfwGetMouseButton(window, bind.key) == GLFW_RELEASE && !bind.pressed) {
                bind.active = true;
                bind.pressed = true;
            }
            return;
        }

        if(glfwGetKey(window, bind.key) == GLFW_PRESS && bind.pressed) {
            bind.active = false;
            bind.pressed = false;
        }
        if(glfwGetKey(window, bind.key) == GLFW_RELEASE && !bind.pressed) {
            bind.active = true;
            bind.pressed = true;
        }
    }
    // Check if key is being held down
    static void checkInputHold(GLFWwindow* window, Bind& bind) {

        if(bind.isMouse == 1) { // glfwGetMouseButton
            if(glfwGetMouseButton(window, bind.key) == GLFW_PRESS && !bind.pressed) {
                bind.active = true;
                bind.pressed = true;
            }
            if(glfwGetMouseButton(window, bind.key) == GLFW_RELEASE && bind.pressed) {
                bind.active = false;
                bind.pressed = false;
            }
            return;
        }

        if(glfwGetKey(window, bind.key) == GLFW_PRESS && !bind.pressed) {
            bind.active = true;
            bind.pressed = true;
        }
        if(glfwGetKey(window, bind.key) == GLFW_RELEASE && bind.pressed) {
            bind.active = false;
            bind.pressed = false;
        }
    }
};

/*
if(glfwGetKey(window, bind.key) == GLFW_PRESS && !bind.pressed) {
    bind.pressed = true;
}
if(glfwGetKey(window, bind.key) == GLFW_RELEASE && bind.pressed) {
    bind.pressed = true;
}
*/


#endif
