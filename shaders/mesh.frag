#version 430 core

out vec4 color;

in vec3 N;
in vec3 V;
in vec3 L;

// Gooch properties
uniform float r = 0.4;
uniform sampler2D image;

void main(void)
{    			
	/*
	vec3 diffuse = vec3(rc, bc, gc);
	vec3 kcool = vec3(0, 0, b) + alpha * diffuse; 
	vec3 kwarm = vec3(y, y, 0) + beta * diffuse;

	vec3 warm = (1 -(1 - dot(L, N)) / 2) * kwarm ;
	vec3 cool = (1 - dot(L, N)) / 2 * kcool;
	
	color = vec4(cool + warm, 1);
	*/
	float diff = dot(N, L);
	vec2 coord = vec2( diff, pow( abs( dot(N,V) ), r) );
	
	color = texture(image, coord);//vec2(diff, diff));
}
