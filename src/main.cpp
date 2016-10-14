
#include "GL/glew.h"
#include <cstdlib>
#include <cstdio>
#include <GLFW/glfw3.h>
#include <iostream>
#include "SceneShader.h"

double mouse_old_x, mouse_old_y;
int mouse_buttons = 0;
float rotate_x = 0.0, rotate_y = 0.0;
float translate_z = -1.0;

int width = 1024;
int height = 1024;
GLFWwindow* window;

SceneShader shader;

void keyboard( unsigned char key, int x, int y )
{
	float factor = 0.05f;

	float value = -1;
	
	switch (key)
	{
		case (27):
			exit(EXIT_FAILURE);
		case (GLFW_KEY_X):
			rotate_y += 1.0f;
			break;
		case (GLFW_KEY_Z):
			rotate_y -=  1.0f;
			break;
		case (GLFW_KEY_A):
			shader.updateLightPositionX(-factor);
			break;
		case (GLFW_KEY_D):
			shader.updateLightPositionX(factor);
			break;
		case (GLFW_KEY_S):
			shader.updateLightPositionY(-factor);
			break;
		case (GLFW_KEY_W):
			shader.updateLightPositionY(factor);
			break;
		case (GLFW_KEY_Q):
			shader.updateLightPositionZ(-factor);				
			break;
		case (GLFW_KEY_E):
			shader.updateLightPositionZ(factor);				
			break;			
		case (GLFW_KEY_1):
		case (GLFW_KEY_2):
			value = shader.b;	// initialize to shader value 
			break;
		case (GLFW_KEY_3):
		case (GLFW_KEY_4):
			value = shader.y;
			break;
		case (GLFW_KEY_5):
		case (GLFW_KEY_6):
			value = shader.alpha;
			break;
		case (GLFW_KEY_7):
		case (GLFW_KEY_8):
			value = shader.beta;
			break;;
		case (GLFW_KEY_9):
		case (GLFW_KEY_0):
			value = shader.rc;
			break;
		case (GLFW_KEY_U):
		case (GLFW_KEY_I):
			value = shader.bc;
			break;
		case (GLFW_KEY_O):
		case (GLFW_KEY_P):
			value = shader.gc;
			break;
		default:
			break;
	}
	switch (key)
	{
		case (GLFW_KEY_1):
		case (GLFW_KEY_3):
		case (GLFW_KEY_5):
		case (GLFW_KEY_7):
		case (GLFW_KEY_9):
		case (GLFW_KEY_U):
		case (GLFW_KEY_O):
			value -= 0.01;		
			if (value < 0)		// perform clamping on the new value
				value = 0;
			break;
		default:		
			value += 0.01;
			if (value > 1)		// perform clamping on the new value
				value = 1;
		break;	
	}
	
	switch (key)	// assign the new value to the correct variable
	{	
		case (GLFW_KEY_1):
		case (GLFW_KEY_2):
			shader.b = value;
			printf("b value: %f\n", shader.b);
			break;
		case (GLFW_KEY_3):
		case (GLFW_KEY_4):
			shader.y = value;
			printf("y value: %f\n", shader.y);
			break;
		case (GLFW_KEY_5):
		case (GLFW_KEY_6):
			shader.alpha = value;
			printf("alpha value: %f\n", shader.alpha);
			break;
		case (GLFW_KEY_7):
		case (GLFW_KEY_8):
			shader.beta = value;
			printf("beta value: %f\n", shader.beta);
			break;
		case (GLFW_KEY_9):
		case (GLFW_KEY_0):
			shader.rc = value;
			printf("rc value: %f\n", shader.rc);
			break;
		case (GLFW_KEY_U):
		case (GLFW_KEY_I):
			shader.bc = value;
			printf("bc value: %f\n", shader.bc);
			break;
		case (GLFW_KEY_O):
		case (GLFW_KEY_P):
			shader.gc = value;
			printf("gc value: %f\n", shader.gc);
			break;
		default:
			break;	
	}
}


void mouse( GLFWwindow* window, int button, int action, int mods )
{
	if (action == GLFW_PRESS)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		mouse_old_x = x;
		mouse_old_y = y;
	}
}

void motion( GLFWwindow* w, double x, double y )
{

	double dx, dy;
	dx = (x - mouse_old_x);
	dy = (y - mouse_old_y);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1))
	{
		rotate_x += dy * 0.5f;
		rotate_y += dx * 0.5f;
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2))
	{
		translate_z += dy * 0.03f;
	}

	mouse_old_x = x;
	mouse_old_y = y;
}

void scroll( GLFWwindow* w, double x, double y )
{
	double dy;
	dy = (x - y);
	translate_z += dy * 0.03f;
}

void render( )
{
	GLfloat color[] = {0.3215f, 0.3411f, 0.4352f, 1.0f};
	const GLfloat zero = 1.0f;

	glClearBufferfv(GL_COLOR, 0, color);
	glClearBufferfv(GL_DEPTH, 0, &zero);
	glEnable(GL_DEPTH_TEST);

	shader.setRotationY(rotate_y);
	shader.setZTranslation( translate_z );

	shader.render();

	glDisable(GL_DEPTH_TEST);
}

void reshape( GLFWwindow* w, int widthX, int heightY )
{
	width = widthX;
	height = heightY;
	glViewport(0, 0, width, height);
}

static void error_callback( int error, const char* description )
{
	fputs(description, stderr);
}

static void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods )
{	
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, GL_TRUE);
		
		keyboard(key, 0, 0);		
	}
}

void startGlew( )
{
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong */
		fprintf(stderr, "Error: %s \n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* vendor = glGetString(GL_VENDOR); // vendor name string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	// GLSL version string
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major); // get integer (only if gl version > 3)
	glGetIntegerv(GL_MINOR_VERSION, &minor); // get dot integer (only if gl version > 3)
	printf("OpenGL on %s %s\n", vendor, renderer);
	printf("OpenGL version supported %s\n", version);
	printf("GLSL version supported %s\n", glslVersion);
	printf("GL version major, minor: %i.%i\n", major, minor);

	shader.startup();
}

int main( int argc, char**argv )
{

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_SAMPLES, 16);

	window = glfwCreateWindow(width, height, "OpenGL Window", NULL, NULL);

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse);
	glfwSetCursorPosCallback(window, motion);
	glfwSetScrollCallback(window, scroll);
	glfwSetWindowSizeCallback(window, reshape);

	startGlew();

	while ( !glfwWindowShouldClose(window) )
	{
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float) height;
		shader.setAspectRatio(ratio);

		render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}
