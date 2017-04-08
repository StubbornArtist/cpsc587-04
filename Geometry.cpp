#include "Geometry.h"

Geometry::Geometry(bool instanced) {
	vertexArray = 0;
	vertexBuffer = 0;
	colourBuffer = 0;
	positionBuffer = 0;
	modelMatrixBuffer = 0;
	verticeCount = 0;
	instanceCount = 0;
	initialize();
}
void Geometry::initialize() {
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &colourBuffer);

	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(VERTEX_INDEX);

	glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
	glVertexAttribPointer(COLOUR_INDEX, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(COLOUR_INDEX);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Geometry::initializeInstanced() {
	
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &colourBuffer);
	glGenBuffers(1, &positionBuffer);

	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(VERTEX_INDEX);
	glVertexAttribDivisor(VERTEX_INDEX, 1);

	glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
	glVertexAttribPointer(COLOUR_INDEX, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(COLOUR_INDEX);

	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glVertexAttribPointer(POS_INDEX, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(POS_INDEX);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
//change the vertices
void Geometry::reloadVertices(vector<float> vertices) {
	verticeCount = vertices.size() / 3;
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}
//change the colours
void Geometry::reloadColours(vector<float> colours) {
	glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
	glBufferData(GL_ARRAY_BUFFER, colours.size() * sizeof(float), colours.data(), GL_STATIC_DRAW);
}

void Geometry::reloadPositions(vector<float> positions) {
	instanceCount = positions.size() / 3;
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);
}
//draw vertices in given colours
void Geometry::draw(GLenum mode) {
	glBindVertexArray(vertexArray);
	glDrawArrays(mode, 0, verticeCount);
	glBindVertexArray(0);
}
void Geometry::drawInstanced(GLenum mode) {
	glBindVertexArray(vertexArray);
	glDrawArraysInstanced(mode, 0, verticeCount, instanceCount);
	glBindVertexArray(0);
}
void Geometry::destroy() {
	glDeleteVertexArrays(1, &vertexArray);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &colourBuffer);
	glDeleteBuffers(1, &positionBuffer);
}