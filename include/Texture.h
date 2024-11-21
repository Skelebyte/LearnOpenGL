#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include "../libs/glad/glad.h"
#include "../libs/stb_image.h"
#include "Shader.h"
#include "Utils.h"

#define MISSING_TEXTURE_PINK "data/engine/MissingTexture_Pink.png"

enum ImageType {
    PNG = 0,
    JPG = 1,
};

unsigned int loadTexture(const char* path, ImageType type);

#endif
