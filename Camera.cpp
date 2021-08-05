#include "Camera.h"
#include <imgui.h>
#include <string>

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::LookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 worldUp)
{
    glm::vec3 zaxis = glm::normalize(target - pos);

    glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
    glm::vec3 yaxis = glm::cross(zaxis, xaxis);

    glm::mat4 translation = glm::mat4(1.0f); // Identity matrix by default
    translation[3][0] = -pos.x; // Third column, first row
    translation[3][1] = -pos.y;
    translation[3][2] = -pos.z;
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0][0] = xaxis.x; // First column, first row
    rotation[1][0] = xaxis.y;
    rotation[2][0] = xaxis.z;
    rotation[0][1] = yaxis.x; // First column, second row
    rotation[1][1] = yaxis.y;
    rotation[2][1] = yaxis.z;
    rotation[0][2] = zaxis.x; // First column, third row
    rotation[1][2] = zaxis.y;
    rotation[2][2] = zaxis.z;

    matrix = rotation * translation;
}

void Camera::Prep()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    lookVec = glm::normalize(direction);
    LookAt(position, position - lookVec);
}

void Camera::Uniform(Program& program, const char* uniformName)
{
	program.setM4(uniformName, matrix);
}
