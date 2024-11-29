#ifndef UTILS_H
#define UTILS_H

#include <glm/detail/qualifier.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <glm/glm.hpp>
#include "../libs/glad/glad.h"

using namespace std;



enum RotationOrder {
    XYZ,
    YXZ,
    ZXY,
    XZY,
    YZX,
    ZYX
};

class Vector3 {
    public:
    glm::vec3 glmVec3;

    public:
    Vector3() {
        glmVec3 = glm::vec3(0.0f, 0.0f, 0.0f);
    }
    Vector3(float x, float y, float z) {
        glmVec3 = glm::vec3(x, y, z);
    }

    const float x() {
        return glmVec3.x;
    }
    const float y() {
        return glmVec3.y;
    }
    const float z() {
        return glmVec3.z;
    }

    void setX(float value) {
        glmVec3.x = value;
    }
    void setY(float value) {
        glmVec3.y = value;
    }
    void setZ(float value) {
        glmVec3.z = value;
    }

    Vector3& operator+=(const Vector3 &value) {
        glmVec3 += value.glmVec3;
        return *this;
    }

    public:
    static Vector3 up() {
        return Vector3(0.0f, 1.0f, 0.0f);
    }
    static Vector3 down() {
        return Vector3(0.0f, -1.0f, 0.0f);
    }
    static Vector3 forward() {
        return Vector3(0.0f, 0.0f, -1.0f);
    }
    static Vector3 back() {
        return Vector3(0.0f, 0.0f, 1.0f);
    }
};


// class Rotation3 {
//     public:
//     Vector3 angles;
//     RotationOrder rotationOrder;
//     protected:
//     Vector3 axis;


//     public:
//     Rotation3& operator=(Rotation3 &target) {
//         if(this != &target) {
//             angles = target.angles;

//             axis.setX((target.angles.x() != 0) ? 1.0f : 0.0f);
//             axis.setY((target.angles.y() != 0) ? 1.0f : 0.0f);
//             axis.setZ((target.angles.z() != 0) ? 1.0f : 0.0f);
//         }
//         return *this;
//     }
//     Rotation3& operator+(Rotation3 &target) {
//         if(this != &target) {
//             angles.x() += target.angles.x();
//             angles.y() += target.angles.y();
//             angles.z() += target.angles.z();
//             axis.setX((target.angles.x() != 0) ? 1.0f : 0.0f);
//             axis.setY((target.angles.y() != 0) ? 1.0f : 0.0f);
//             axis.setZ((target.angles.z() != 0) ? 1.0f : 0.0f);
//         }
//         return *this;
//     }
//     Rotation3& operator-(Rotation3 &target) {
//         if(this != &target) {
//             angles.x() -= target.angles.x();
//             angles.y() -= target.angles.y();
//             angles.z() -= target.angles.z();

//             angles.setX((angles.x() >= 360.0f) ? angles.x() - 360.0f : angles.x());
//             angles.setY((angles.y() >= 360.0f) ? angles.y() - 360.0f : angles.y());
//             angles.setZ((angles.z() >= 360.0f) ? angles.z() - 360.0f : angles.z());

//             axis.setX((target.angles.x() != 0) ? 1.0f : 0.0f);
//             axis.setY((target.angles.y() != 0) ? 1.0f : 0.0f);
//             axis.setZ((target.angles.z() != 0) ? 1.0f : 0.0f);
//         }
//         return *this;
//     }
// };

const char* readFile(const char* path);
void checkIfShaderCompileSuccess(unsigned int shader, const char* desc);
void checkIfShaderProgramLinkSuccess(unsigned int shaderProgram);

enum Severity {
    INFO,
    MESSAGE,
    WARNING,
    ERROR,
    CRITICAL,
};

class Debug {
    public:
    static void log(string message, Severity severity) {
        time_t time = std::time(nullptr);
        tm* currentTime = localtime(&time);

        int hour = currentTime->tm_hour;
        int minute = currentTime->tm_min;
        int second = currentTime->tm_sec;
        string timeString = (to_string(hour) + ":" + to_string(minute) + ":" + to_string(second));

        int day = currentTime->tm_mday;
        int month = currentTime->tm_mon + 1;
        int year = currentTime->tm_year + 1900;
        string dateString = (to_string(year) + "-" + to_string(month) + "-" + to_string(day));

        string sev;

        switch(severity) {
            case Severity::INFO:
                sev = "INFO";
                break;
            case Severity::MESSAGE:
                sev = "MESSAGE";
                break;
            case Severity::WARNING:
                sev = "WARNING";
                break;
            case Severity::ERROR:
                sev = "ERROR";
                break;
            case Severity::CRITICAL:
                sev = "CRITICAL";
                break;
        }

        string line = timeString + " - [" + sev + "] " + message;

        writeFile(("data/logs/" + dateString + ".log").c_str(), line.c_str());
    }
    private:
    static void writeFile(const char* path, const char* content) {
        ofstream file;

        file.open(path, ios::app);
        file<<content<<endl;
        file.close();
    }
};


class File {
    public:
    static const char* readFile(string path) {
        Debug debug;
        std::ifstream file;

        file.open(path, std::ios::binary | std::ios::ate);

        if(file.fail()) {
            debug.log("Failed to read file: " + path + ".", Severity::ERROR);
            return NULL;
        }
        streamsize size = (streamsize)file.tellg();
        file.seekg(0, ios::beg);
        char* buffer = new char[size + 1];
        if(!file.read(buffer, size)) {
            debug.log("Failed to read file from path: " + path + ".", Severity::ERROR);
            delete[] buffer;
            return NULL;
        }
        buffer[size] = '\0';

        file.close();

        return buffer;
    }
    static void writeFile(const char* path, const char* content) {
        ofstream file;

        file.open(path, ios::app);
        file<<content<<endl;
        file.close();
    }
};






#endif
