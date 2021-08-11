#include "Mesh.h"

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <unsigned int>& indices, std::vector <Texture>& textures)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	VAO.Bind();
	VBO VBO(vertices);
	EBO EBO(indices);
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}


void Mesh::Draw(Program& program, Camera& camera)
{
	program.Use();
	VAO.Bind();

	//// Keep track of how many of each type of textures we have
	//unsigned int numDiffuse = 0;
	//unsigned int numSpecular = 0;

	//for (unsigned int i = 0; i < textures.size(); i++)
	//{
	//	std::string num;
	//	std::string type = textures[i].type;
	//	if (type == "diffuse")
	//	{
	//		num = std::to_string(numDiffuse++);
	//	}
	//	else if (type == "specular")
	//	{
	//		num = std::to_string(numSpecular++);
	//	}
	//	textures[i].texUnit(shader, (type + num).c_str(), i);
	//	textures[i].Bind();
	//}

	for (unsigned int i = 0; i < textures.size(); i++) {
		program.setI1("tex" + i, i);
		textures[i].Bind(i);
	}

	camera.Prep(CameraPrepMode::YawPitch);
	camera.Uniform(program, "view");

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}