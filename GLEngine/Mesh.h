#pragma once

#include<string>

#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"Texture.h"

class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <unsigned int> indices;
	std::vector <Texture> textures;

	glm::vec3 position;
	glm::vec3 rotation;

	VAO VAO;

	Mesh(std::vector <Vertex>& vertices, std::vector <unsigned int>& indices, std::vector <Texture>& textures);
	void Draw(Program& program, Camera& camera);
};