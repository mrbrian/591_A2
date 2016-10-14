#version 430 core

out vec4 color;

in vec3 N;
in vec3 V;
in vec3 L;

// Gooch properties
uniform float b = 0.4;
uniform float y = 0.4;
uniform float alpha = 0.2;
uniform float beta = 0.6;
uniform float rc = 0.0;
uniform float bc = 0.0;
uniform float gc = 1.0;

uniform sampler2D image;

void main(void)
{    			
	
	vec3 diffuse = vec3(rc, bc, gc);
	vec3 kcool = vec3(0, 0, b) + alpha * diffuse; 
	vec3 kwarm = vec3(y, y, 0) + beta * diffuse;

	vec3 warm = (1 -(1 - dot(L, N)) / 2) * kwarm ;
	vec3 cool = (1 - dot(L, N)) / 2 * kcool;
	
	//color = vec4(cool + warm, 1);
	
	float diff = dot(N, L);
	//vec2 coord = vec2( exp(dot(n,v), r), diff );
	
	color = texture(image, vec2(diff, diff));
}
