#include "Shader.h"
#include <sstream>
#include <glad/glad.h>
#include <iostream>
#include <fstream>

Shader::Shader(const char* path, unsigned int type) {
	std::ifstream ifs(path);

	std::string content;

	content.assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

	id = glCreateShader(type);

	const char* source = content.c_str();

	glShaderSource(id, 1, &source, NULL);

	glCompileShader(id);

	int success;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

Shader::~Shader()
{
	glDeleteShader(id);
}