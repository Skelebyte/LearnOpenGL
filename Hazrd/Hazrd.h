// this file only contains the includes for all header files used in the project.

/* HAZRD HEADERS */
#include "include/Entity.h"
#include "include/Shader.h"
#include "include/Texture.h"
#include "include/Utils.h"
#include "include/Renderer.h"
#include "include/Input.h"
#include "include/GameObjects.h"
#include "include/Vector3.h"

#define HAZRD_VERSION "0.1.0"

/* EXTERNAL HEADERS */
// some external librarys are inside the libs directory, such as glad.
#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION
#define GLM_ENABLE_EXPERIMENTAL
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "libs/glad/glad.h"
#include "libs/stb_image.h"
