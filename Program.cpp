#include "Program.h"
#include <glad/glad.h>
#include <iostream>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

Program::Program(std::vector<Shader> shaders)
{
	id = glCreateProgram();
	std::vector<Shader>::iterator itt = shaders.begin();
	do {
		glAttachShader(id, (*itt).id);
		itt++;
	} while (itt != shaders.end());

	glLinkProgram(id);
	int success;

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

Program::~Program() {
	glDeleteProgram(id);
}

void Program::Use()
{
	glUseProgram(id);
}

void Program::setB1(const std::string& name, bool a)
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), a);
}

void Program::setF1(const std::string& name, float a)
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), a);
}

void Program::setI1(const std::string& name, int a)
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), a);
}

void Program::setB2(const std::string& name, bool a, bool b)
{
	glUniform2i(glGetUniformLocation(id, name.c_str()), a, b);
}

void Program::setF2(const std::string& name, float a, float b)
{
	glUniform2f(glGetUniformLocation(id, name.c_str()), a, b);
}

void Program::setI2(const std::string& name, int a, int b)
{
	glUniform2i(glGetUniformLocation(id, name.c_str()), a, b);
}


void Program::setB3(const std::string& name, bool a, bool b, bool c)
{
	glUniform3i(glGetUniformLocation(id, name.c_str()), a, b, c);
}

void Program::setF3(const std::string& name, float a, float b, float c)
{
	glUniform3f(glGetUniformLocation(id, name.c_str()), a, b, c);
}

void Program::setI3(const std::string& name, int a, int b, int c)
{
	glUniform3i(glGetUniformLocation(id, name.c_str()), a, b, c);
}


void Program::setB4(const std::string& name, bool a, bool b, bool c, bool d)
{
	glUniform4i(glGetUniformLocation(id, name.c_str()), a, b, c, d);
}

void Program::setF4(const std::string& name, float a, float b, float c, float d)
{
	glUniform4f(glGetUniformLocation(id, name.c_str()), a, b, c, d);
}

void Program::setI4(const std::string& name, int a, int b, int c, int d)
{
	glUniform4i(glGetUniformLocation(id, name.c_str()), a, b, c, d);
}

void Program::setM4(const std::string& name, glm::mat4 matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}
