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
//void BoidSystem :: simulate() {
	//for each(Boid * b in boids) {
		//b->run(boids, colliders, RA, RC, RG, vMax, fMax, DT);
	//}
//}
void BoidSystem::simulate(vec2 mousePos) {
	for each(Boid * b in boids) {
		b->run(mousePos,boids, colliders, RA, RC, RG, vMax, fMax, DT);
	}
}
void BoidSystem :: randomize(int flock_size, float yMax, float xMax, float yMin, float xMin) {
	for (int i = 0; i < flock_size; i++) {
		float x = randomFloat(xMax, xMin);
		float y = randomFloat(yMax, yMin);
		float vX = randomFloat(1.0f, -1.0f);
		float vY = randomFloat(1.0f, -1.0f);
		addBoid(new Boid(vec3(x, y, 0.0f), vec3(vX, vY, 0.0f)));
		addCollider(new CollisionObject(vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, yMax, 0.0f)));
		addCollider(new CollisionObject(vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, yMin, 0.0f)));
		addCollider(new CollisionObject(vec3(-1.0f, 0.0f, 0.0f), vec3(xMax, 0.0f, 0.0f)));
		addCollider(new CollisionObject(vec3(1.0f, 0.0f, 0.0f), vec3(xMin, 0.0f, 0.0f)));
	}
}
void BoidSystem :: addBoid(Boid * b) {
	boids.push_back(b);
}
void BoidSystem :: addCollider(CollisionObject * c) {
	colliders.push_back(c);
}
void BoidSystem :: getBoidLocations(vector<float> * locationBuf) {
	for each (Boid * b in boids) {
		vec3 bPos = b->getPosition();
		float theta = b->getAngle();
		float phi = b->getBank();

		vec3 v1 = rotateY(vec3(0.0f, 1.0f, 0.0f), phi);
		v1 = rotateZ(v1, theta) + bPos;
		vec3 v2 = rotateY(vec3(0.5f, 0.0f, 0.0f), phi);
		v2 = rotateZ(v2, theta) + bPos;
		vec3 v3 = rotateY(vec3(-0.5f, 0.0f, 0.0f), phi);
		v3 = rotateZ(v3, theta) + bPos;

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

float BoidSystem :: randomFloat(float lBound, float hBound) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = hBound - lBound;
	float r = random * diff;
	return lBound + r;
}