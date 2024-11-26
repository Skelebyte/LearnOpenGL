// this file only contains the includes for all header files used in the project.

/* HAZRD HEADERS */
#include "Entity.h"
#include "Shader.h"
#include "Texture.h"
#include "Utils.h"
#include "Renderer.h"

/* EXTERNAL HEADERS */
// some external librarys are inside the libs directory, such as glad.
#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../libs/glad/glad.h"
#include "../libs/stb_image.h"
