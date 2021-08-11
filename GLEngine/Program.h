#pragma once
#include <vector>
#include "Shader.h"
#include <string>
#include <glm/glm.hpp>

class Program
{
public:
	unsigned int id;
	Program(std::vector<Shader> shaders);
	~Program();
	void Use();

	void setB1(const std::string& name, bool a);
	void setF1(const std::string& name, float a);
	void setI1(const std::string& name, int a);

	void setB2(const std::string& name, bool a, bool b);
	void setF2(const std::string& name, float a, float b);
	void setI2(const std::string& name, int a, int b);

	void setB3(const std::string& name, bool a, bool b, bool c);
	void setF3(const std::string& name, float a, float b, float c);
	void setI3(const std::string& name, int a, int b, int c);

	void setB4(const std::string& name, bool a, bool b, bool c, bool d);
	void setF4(const std::string& name, float a, float b, float c, float d);
	void setI4(const std::string& name, int a, int b, int c, int d);

	void setM4(const std::string& name, glm::mat4 matrix);
};

