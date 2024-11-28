#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <glm/glm.hpp>
#include "../libs/glad/glad.h"
#include "Debug.h"

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
    protected:
    glm::vec3 position;

    public:
    const float x() {
        return position.x;
    }
    const float y() {
        return position.y;
    }
    const float z() {
        return position.z;
    }

    void setX(float value) {
        position.x = value;
    }
    void setY(float value) {
        position.y = value;
    }
    void setZ(float value) {
        position.z = value;
    }

    Vector3& operator+=(const Vector3 &value) {
        position += value.position;
        return *this;
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
