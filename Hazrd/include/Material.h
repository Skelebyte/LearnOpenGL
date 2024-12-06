#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"
#include "Defines.h"
class Material {
    public:
    Texture texture;
    Texture specular;
    VEC3 color;
    int shininess = 32;

    public:
    Material() {
        texture.load("data/engine/NoTexture_Grey.png", ImageFormat::PNG);
        specular.load("data/engine/NoTexture_Black.png", ImageFormat::PNG);
        color = VEC3(1.0f, 1.0f, 1.0f);
    }
    Material(string texturePath, ImageFormat format) {
        texture.load(texturePath, format);
        color = VEC3(1.0f, 1.0f, 1.0f);
    }

    void drawMaterial(Shader shader) {

    }

};

#endif
