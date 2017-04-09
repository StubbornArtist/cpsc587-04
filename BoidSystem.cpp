#include "BoidSystem.h"

BoidSystem::BoidSystem(float DT, float RA, float RC, float RG) {
	boids = vector<Boid *>();
	BoidSystem :: DT = DT;
	BoidSystem :: RA = RA;
	BoidSystem :: RC = RC;
	BoidSystem :: RG = RG;
}
void BoidSystem::simulate() {
	for each(Boid * b in boids) {
		b->run(boids, colliders, RA, RC, RG, FMAX, VMAX, DT);
	}
}

void BoidSystem::randomize(int flock_size) {
	for (int i = 0; i < flock_size; i++) {
		float x = randomFloat(30.0f, -30.0f);
		float y = randomFloat(30.0f, -30.0f);
		Boid * b = new Boid(vec3(x, y, 0.0f), vec3(0.0f, 1.0f, 0.0f));
		addBoid(b);
	}
}
void BoidSystem::addBoid(Boid * b) {
	boids.push_back(b);
}
void BoidSystem :: addCollider(CollisionObject * c) {
	colliders.push_back(c);
}
void BoidSystem::getBoidLocations(vector<float> * locationBuf) {
	for each (Boid * b in boids) {
		vec2 bPos = vec2(b->getPosition().x, b->getPosition().y);
		float theta = b->getAngle();

		vec2 v1 = rotate(vec2(0.0f, 0.5f), theta) + bPos;
		vec2 v2 = rotate(vec2(0.25f, 0.0f), theta) + bPos;
		vec2 v3 = rotate(vec2(- 0.25f, 0.0f), theta) + bPos;

		locationBuf->push_back(v1.x);
		locationBuf->push_back(v1.y);
		locationBuf->push_back(0.0f);

		locationBuf->push_back(v2.x);
		locationBuf->push_back(v2.y);
		locationBuf->push_back(0.0f);

		locationBuf->push_back(v3.x);
		locationBuf->push_back(v3.y);
		locationBuf->push_back(0.0f);
	}

}

float BoidSystem::randomFloat(float lBound, float hBound) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = hBound - lBound;
	float r = random * diff;
	return lBound + r;
}