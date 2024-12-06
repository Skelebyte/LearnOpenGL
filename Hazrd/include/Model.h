#ifndef MODEL_H
#define MODEL_H

#include <climits>
#include <cstddef>
#include <iostream>
#include <fstream>
#include "../libs/json.hpp"
#include "../libs/glad/glad.h"
#include "Defines.h"
#include "Entity.h"
#include "Material.h"
#include "Utils.h"
#include "Texture.h"
using namespace std;
using json = nlohmann::json;

enum ModelFormat {
    OBJ,
    GLTF,
    FBX,
};

typedef struct Vertex {
    VEC3 position;
    VEC3 normal;
    VEC2 textureCoords;
} Vertex;

class Model {
    public:
    vector<Vertex> vertices;
    vector<uint> indices;
    Material material;

    public:
    Model() {}
    Model(vector<Vertex> v, vector<uint> i, Material m) {
        vertices = v;
        indices = i;
        material = m;
    }

    void draw(Shader shader) {
        material.drawMaterial(shader);
    }

};



#endif
