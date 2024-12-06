// this file only contains the includes for all header files used in the project.

/* HAZRD HEADERS */
#include "include/Entity.h"
#include "include/Shader.h"
#include "include/Texture.h"
#include "include/Utils.h"
#include "include/Renderer.h"
#include "include/Input.h"
#include "include/GameObjects.h"
#include "include/Defines.h"
#include "include/Model.h"
#include "include/Material.h"

#define HAZRD_VERSION "0.1.0"

/* EXTERNAL HEADERS */
// some external librarys are inside the libs directory, such as glad.
#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION
#define GLM_ENABLE_EXPERIMENTAL
#define CGLTF_IMPLEMENTATION
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "libs/glad/glad.h"
#include "libs/stb_image.h"
#include "libs/json.hpp"

typedef struct Application {
    void startFunction();
    void updateFunction();

    // window i think...

} Application;



class Hazrd {
    private:
    static int frames;
    protected:
    static double fps;
    // Should be set to a value such as 1.0 / 999.0. always divide by 1.0 because its second / frame target
    static double updateCap;

    public:
    static void run() {

    }


};
