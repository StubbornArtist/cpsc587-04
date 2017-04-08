#pragma once
//remove before submission
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<vector>
#include <glm/common.hpp>
#include <glm/glm.hpp>


#define VERTEX_INDEX  0
#define COLOUR_INDEX 1
#define POS_INDEX 2
using namespace std;
using namespace glm;

class Geometry {
private:
	GLuint vertexArray;
	GLuint vertexBuffer;
	GLuint colourBuffer;
	GLuint positionBuffer;
	GLuint modelMatrixBuffer;
	int verticeCount;
	int instanceCount;
public:
	Geometry(bool instanced);
	void initialize();
	void initializeInstanced();
	void reloadVertices(vector<float> vertices);
	void reloadColours(vector<float> colours);
	void reloadPositions(vector<float> positions);
	void draw(GLenum mode);
	void drawInstanced(GLenum mode);
	void destroy();
};