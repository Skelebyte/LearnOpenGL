#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec3 FragPosition;
out vec3 Normal;
out vec2 TexCoord;

// uniform mat4 transform;

uniform mat4 model;

// cameraMatrix is projection * view
uniform mat4 cameraMatrix;

void main()
{
    gl_Position = cameraMatrix * model * vec4(aPos, 1.0);
    FragPosition = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
