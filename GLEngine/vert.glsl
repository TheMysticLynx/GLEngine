#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexCoords;

out vec3 Pos;
out vec3 Normal;
out vec3 Color;
out vec2 TexCoords;

out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
	gl_Position = proj * view * model * vec4(aPos, 1);
	FragPos = (model * vec4(aPos, 1)).xyz;
	Pos = aPos;
	Normal = aNormal;
	Color = aColor;
	TexCoords = aTexCoords;
}