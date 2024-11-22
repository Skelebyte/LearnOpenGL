#ifndef ENTITY_H
#define ENTITY_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../libs/glad/glad.h"
#include "Utils.h"



class Entity {
    public:
    bool active;
    vector3 position;
    rotation3 rotation;
    vector3 scale;
};

#endif
