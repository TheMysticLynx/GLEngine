#pragma once
#include <glm/glm.hpp>
#include "Program.h"

class Camera
{
public:
	glm::vec3 position = glm::vec3(0, 0, 0);
	float pitch = 0;
	float yaw = -90;

	glm::vec3 lookVec;
	glm::mat4 matrix;


	Camera();
	~Camera();

	void LookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 worldUp = glm::vec3(0,1,0));
	void Prep();
	void Uniform(Program& program, const char* uniformName);
};

