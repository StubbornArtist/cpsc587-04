/*Ashley Currie 10159991*/

//remove before submission
#define _CRT_SECURE_NO_WARNINGS
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Shader.h"
#include "Geometry.h"
#include "BoidSystem.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include <math.h>
#include <time.h>

//add before submission
/*
#define GLFW_INCLUDE_GLCOREARB
#define GL_GLEXT_PROTOTYPES
*/
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#define WIDTH 1000
#define HEIGHT 1000
#define M_PI 3.14
#define FLOCK_SIZE 200
#define DT 0.1f

using namespace std;
using namespace glm;


float x;
float y;
// reports GLFW errors
void ErrorCallback(int error, const char* description)
{
	cout << "GLFW ERROR " << error << ":" << endl;
	cout << description << endl;
}
//Query opengl version and renderer information
void QueryGLVersion()
{
	string version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
	string glslver = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
}
//A key callback function to switch between simulations
void keys(GLFWwindow * window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {

	}
}

//Perform a single draw of the vertices contained in the given Geometry using the given Shader 
void drawScene(Geometry * g, Shader * sh, mat4 mvp, GLFWwindow * w) {
	glClearColor(0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glUseProgram(sh->getProgram());

	glUniformMatrix4fv(sh->getMVPNum(), 1, GL_FALSE, value_ptr(mvp));

	g->draw(GL_TRIANGLES);
	glUseProgram(0);
	glfwSwapBuffers(w);

}

void fillColourBuffer(int num, vec3 colour, vector<float> * buf) {
	for (int i = 0; i < num; i++) {
		buf->push_back(colour.r);
		buf->push_back(colour.g);
		buf->push_back(colour.b);
	}
}
//Initialize GLFW and the main window
//Set the error and key callback functions
GLFWwindow * initScene() {
	// initialize the GLFW windowing system
	if (!glfwInit()) {
		cout << "ERROR: GLFW failed to initilize, TERMINATING" << endl;
	}
	glfwSetErrorCallback(ErrorCallback);
	GLFWwindow * w = 0;
	// attempt to create a window with an OpenGL 4.1 core profile context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	w = glfwCreateWindow(WIDTH, HEIGHT, "CPSC 587 Assignment 3", 0, 0);
	glfwMakeContextCurrent(w);
	glfwSetKeyCallback(w, keys);
	glEnable(GL_DEPTH_TEST);
	QueryGLVersion();

	//remove before submission
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	return w;
}
//Cleanup then terminate the program
void destroyScene(Geometry * g, Shader * s, GLFWwindow * w) {
	s->destroy();
	g->destroy();
	glfwDestroyWindow(w);
	glfwTerminate();
}

// PROGRAM ENTRY POINT
int main(int argc, char *argv[])
{
	GLFWwindow * window = initScene();
	Shader * sh = new Shader("vertex.glsl", "fragment.glsl");
	Geometry * g = new Geometry();
	BoidSystem * sys = new BoidSystem(DT, 2.0f, 25.0f, 25.0f);
	mat4 mvp;
	vector<float> vertices;
	vector<float> colours;

	//set up the view and projection matrices
	mvp = glm::perspective((75 * (float)M_PI / 180), (float)(WIDTH / HEIGHT), 100.0f, 0.1f) *
		lookAt(vec3(0.0f, 0.0f, -30.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	fillColourBuffer(FLOCK_SIZE * 3, vec3(0.439216f, 0.858824f, 0.576471f), &colours);
	g->reloadColours(colours);

	sys->randomize(FLOCK_SIZE);
	sys->getBoidLocations(&vertices);
	sys->addCollider(new CollisionObject(vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 25.0f, 0.0f)));
	sys->addCollider(new CollisionObject(vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, -25.0f, 0.0f)));
	sys->addCollider(new CollisionObject(vec3(-1.0f, 0.0f, 0.0f), vec3(25.0f, 0.0f, 0.0f)));
	sys->addCollider(new CollisionObject(vec3(1.0f, 0.0f, 0.0f), vec3(-25.0f, 0.0f, 0.0f)));
	g->reloadVertices(vertices);
	clock_t diff = 0.0f;
	clock_t start = clock();
	while (!glfwWindowShouldClose(window))
	{	
		if (diff > (float)DT) {
			sys->simulate();
			vertices.clear();
			sys->getBoidLocations(&vertices);
			g->reloadVertices(vertices);
			diff -= (float)DT;
			start = clock();
		}

		//draw the vertices
		drawScene(g, sh, mvp, window);
		//check for key events
		glfwPollEvents();

		diff += clock() - start;
		start = clock();
	}
	//cleanup then terminate
	destroyScene(g, sh, window);
	return 0;
}
