#ifndef ENTITY_H
#define ENTITY_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../libs/glad/glad.h"
#include "Utils.h"
#include "Vector3.h"


class Entity {
    public:
    bool active;
    VECTOR3 position;
    // Rotation3 rotation;
    // vector3 scale;

    public:
    Entity() {
        active = true;
        position = VECTOR3(0.0f, 0.0f, 0.0f);
    }
};

#endif
