#ifndef DEFINES_H
#define DEFINES_H

#include <glm/glm.hpp>


/* --- VECTOR3 --- */
#define VEC3 glm::vec3
#define VEC3_FORWARD glm::vec3(0.0f, 0.0f, -1.0f)
#define VEC3_BACKWARD glm::vec3(0.0f, 0.0f, 1.0f)
#define VEC3_UP glm::vec3(0.0f, 1.0f, 0.0f)
#define VEC3_DOWN glm::vec3(0.0f, -1.0f, 0.0f)
#define VEC3_RIGHT glm::vec3(1.0f, 0.0f, 0.0f)
#define VEC3_LEFT glm::vec3(-1.0f, 0.0f, 0.0f)

#define VEC3_TO_STRING(VEC3) (to_string(VEC3.x) + ", " + to_string(VEC3.y) + ", " + to_string(VEC3.z))
/* --- END --- */

#define VEC2 glm::vec2
#define VEC2_UP glm::vec2(0.0f, 1.0f)
#define VEC2_DOWN glm::vec2(0.0f, -1.0f)
#define VEC2_RIGHT glm::vec2(1.0f, 0.0f)
#define VEC2_LEFT glm::vec2(-1.0f, 0.0f)

#define VEC2_TO_VEC3(VEC2) (VEC3(VEC2.x, VEC2.y, 0.0f))
#define VEC2_TO_STRING(VEC2) (to_string(VEC2.x) + ", " + to_string(VEC2.y))
/* --- VECTOR2 --- */


#endif
