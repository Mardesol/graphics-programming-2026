#version 330 core

// (todo) 03.X: Add the in variables here
in vec3 Normal;
in vec3 Position;

out vec4 FragColor;

uniform vec3 Color = vec3(1);

void main()
{
	vec3 Color = Position;
	vec3 c = Color * dot(normalize(Normal), vec3(1));

	FragColor = vec4(c, 1) ;
}
