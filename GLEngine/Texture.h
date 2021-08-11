#pragma once
#include <string>
class Texture
{
public:
	unsigned int id;
	Texture(const std::string path, int format);
	~Texture();
	void Bind(int activeTexture = 0);
};