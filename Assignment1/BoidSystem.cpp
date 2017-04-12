#include "BoidSystem.h"

BoidSystem::BoidSystem(float DT, float RA, float RC, float RG, float vMax, float fMax) {
	boids = vector<Boid *>();
	BoidSystem :: DT = DT;
	BoidSystem :: RA = RA;
	BoidSystem :: RC = RC;
	BoidSystem :: RG = RG;
	BoidSystem::vMax = vMax;
	BoidSystem::fMax = fMax;
}
//Do one iteration of the simulation for each boid in the flock
void BoidSystem :: simulate() {
	for each(Boid * b in boids) {
		b->run(boids, colliders, RA, RC, RG, vMax, fMax, DT);
	}
}
//Create a specified number of boids at random positions with random velocities with maximum magnitude of sqrt(3)
void BoidSystem :: randomize(int flock_size, float yMax, float xMax, float yMin, float xMin) {
	for (int i = 0; i < flock_size; i++) {
		float x = randomFloat(xMax, xMin);
		float y = randomFloat(yMax, yMin);
		float vX = randomFloat(1.0f, -1.0f);
		float vY = randomFloat(1.0f, -1.0f);
		addBoid(new Boid(vec3(x, y, 0.0f), vec3(vX, vY, 0.0f)));
	}
	//add a wall that will encompass all boids in the flock
	addCollider(new CollisionObject((xMax - xMin)/2.0f, vec3(0.0f, 0.0f, 0.0f), true));
}
void BoidSystem :: addBoid(Boid * b) {
	boids.push_back(b);
}
void BoidSystem :: addCollider(CollisionObject * c) {
	colliders.push_back(c);
}
//Get the vertices that make up all the boids
void BoidSystem :: getBoidLocations(vector<float> * locationBuf) {
	locationBuf->clear();
	for (int i = 0; i < boids.size(); i++) {
		vec3 bPos = boids[i]->getPosition();
		float theta = boids[i]->getAngle();

		//rotate it so that it points in it's direction of movement and translate it to it's position on the screen
		vec3 v1 = rotateZ(vec3(0.0f, 2.0f, 0.0f), theta) + bPos;
		vec3 v2 = rotateZ(vec3(0.5f, 0.0f, 0.0f), theta) + bPos;
		vec3 v3 = rotateZ(vec3(-0.5f, 0.0f, 0.0f), theta) + bPos;

		locationBuf->push_back(v1.x);
		locationBuf->push_back(v1.y);
		locationBuf->push_back(v1.z);

		locationBuf->push_back(v2.x);
		locationBuf->push_back(v2.y);
		locationBuf->push_back(v2.z);

		locationBuf->push_back(v3.x);
		locationBuf->push_back(v3.y);
		locationBuf->push_back(v3.z);
	}

}
//Get the position of all collision objects in the scene
void BoidSystem::getColliderPositions(vector<float> * colliderBuf) {
	colliderBuf->clear();
	for (int i = 0; i < colliders.size(); i++) {
		CollisionObject * c = colliders[i];
		colliderBuf->push_back(c->getCenter().x);
		colliderBuf->push_back(c->getCenter().y);
		colliderBuf->push_back(c->getCenter().z);
	}

}

float BoidSystem :: getDeltaT() {
	return DT;
}
float BoidSystem :: randomFloat(float lBound, float hBound) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = hBound - lBound;
	float r = random * diff;
	return lBound + r;
}