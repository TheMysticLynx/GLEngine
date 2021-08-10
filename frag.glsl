#version 460 core

out vec4 FragColor;

uniform sampler2D tex1;

uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform float specStrength;

in vec3 Pos;
in vec3 Normal;
in vec3 Color;
in vec2 TexCoords;

in vec3 FragPos;

vec3 calcColor() {
	vec3 norm = normalize(Normal);

	vec3 lightDir = normalize(lightPos - FragPos);

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specStrength * spec * lightColor;

	float diff = max(dot(norm, lightDir), 0);
	vec3 diffuse = diff * lightColor;

	return Color * (ambientColor + diffuse + specular);
}

void main() {
	FragColor = vec4(texture(tex1, TexCoords).xyz * calcColor(), 1);
}