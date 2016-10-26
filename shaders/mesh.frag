#version 430 core

out vec4 color;

in vec3 N;
in vec3 V;
in vec3 L;

uniform float r = 1;
uniform sampler2D image;

void main(void)
{
	float u = (1 + dot(L, N)) / 2;
	float v = 1 - pow( (1 + dot(N,V) ) / 2, r);

	vec2 coord = vec2( u, v);
	
	color = texture(image, coord);
}
