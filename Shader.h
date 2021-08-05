#pragma once
class Shader
{
public:
	unsigned int id;
	unsigned int type;

	Shader(const char* path, unsigned int type);
	~Shader();
};

