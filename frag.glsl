#version 460 core

out vec4 FragColor;

uniform sampler2D tex1;

in vec3 Pos;
in vec3 Normal;
in vec3 Color;
in vec2 TexCoords;

void main() {
	FragColor = texture(tex1, TexCoords) * vec4(Color, 1);
}