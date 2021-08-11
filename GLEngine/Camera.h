#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Program.h"

enum CameraPrepMode {
	YawPitch,
	XYZ,
	XZY,
	Quaternion
};

class Camera
{
public:
	glm::vec3 position = glm::vec3(0);
	glm::vec3 rotation = glm::vec3(0);
	glm::fquat quaternion = glm::fquat();

	float pitch = 0;
	float yaw = -90;

	glm::vec3 lookVec;
	glm::mat4 matrix;


	Camera();
	~Camera();

	void LookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 worldUp = glm::vec3(0,1,0));
	void Prep(CameraPrepMode mode);
	void Uniform(Program& program, const char* uniformName);
};

