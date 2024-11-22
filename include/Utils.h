#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
#include "../libs/glad/glad.h"

using namespace std;

#define vector3 glm::vec3

enum RotationOrder {
    XYZ,
    YXZ,
    ZXY,
    XZY,
    YZX,
    ZYX
};

class rotation3 {
    public:
    vector3 angles;
    RotationOrder rotationOrder;
    protected:
    vector3 axis;


    public:
    rotation3& operator=(const rotation3 &target) {
        if(this != &target) {
            angles = target.angles;

            axis.x = (target.angles.x != 0) ? 1.0f : 0.0f;
            axis.y = (target.angles.y != 0) ? 1.0f : 0.0f;
            axis.z = (target.angles.z != 0) ? 1.0f : 0.0f;
        }
        return *this;
    }
    rotation3& operator+(const rotation3 &target) {
        if(this != &target) {
            angles.x += target.angles.x;
            angles.y += target.angles.y;
            angles.z += target.angles.z;

            axis.x = (target.angles.x != 0) ? 1.0f : 0.0f;
            axis.y = (target.angles.y != 0) ? 1.0f : 0.0f;
            axis.z = (target.angles.z != 0) ? 1.0f : 0.0f;
        }
        return *this;
    }
    rotation3& operator-(const rotation3 &target) {
        if(this != &target) {
            angles.x -= target.angles.x;
            angles.y -= target.angles.y;
            angles.z -= target.angles.z;

            angles.x = (angles.x >= 360.0f) ? angles.x - 360.0f : angles.x;
            angles.y = (angles.y >= 360.0f) ? angles.y - 360.0f : angles.y;
            angles.z = (angles.z >= 360.0f) ? angles.z - 360.0f : angles.z;

            axis.x = (target.angles.x != 0) ? 1.0f : 0.0f;
            axis.y = (target.angles.y != 0) ? 1.0f : 0.0f;
            axis.z = (target.angles.z != 0) ? 1.0f : 0.0f;
        }
        return *this;
    }
};

const char* readFile(const char* path);
void checkIfShaderCompileSuccess(unsigned int shader, const char* desc);
void checkIfShaderProgramLinkSuccess(unsigned int shaderProgram);

#endif
