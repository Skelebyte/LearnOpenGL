#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include "../libs/glad/glad.h"
#include "../libs/stb_image.h"
#include "Shader.h"
#include "Utils.h"

#define MISSING_TEXTURE_PINK "data/engine/MissingTexture_Pink.png"

enum ImageFormat {
    PNG = 0,
    JPG = 1,
};

class Texture {
    public:
    uint id;
    string path;
    ImageFormat format;

    public:
    void load(string path, ImageFormat type) {
        uint texture;
        glad_glGenTextures(1, &texture);
        glad_glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
        // set the texture wrapping parameters
        glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
        glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            if(type == ImageFormat::PNG) {
                glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            } else {
                glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            }
            glad_glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            Debug::log("Failed to load texture: " + path + ".", Severity::WARNING);
            data = stbi_load(MISSING_TEXTURE_PINK, &width, &height, &nrChannels, 0);
            if(data) {
                glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glad_glGenerateMipmap(GL_TEXTURE_2D);
            } else {
                cout<<"Failed to load missing texture! Did you move or rename data/engine/MissingTexture_Pink.png?"<<endl;
            }
        }
        stbi_image_free(data);


        id = texture;
        path = path;
        format = type;
    }

};

#endif
