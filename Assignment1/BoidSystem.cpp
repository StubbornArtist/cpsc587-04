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
	for (int i = 0; i < boids.size(); i++) {
		boids[i]->run(mousePos,boids, colliders, RA, RC, RG, vMax, fMax, DT);
	}
}
void BoidSystem :: randomize(int flock_size, float yMax, float xMax, float yMin, float xMin) {
	for (int i = 0; i < flock_size; i++) {
		float x = randomFloat(xMax, xMin);
		float y = randomFloat(yMax, yMin);
		float vX = randomFloat(1.0f, -1.0f);
		float vY = randomFloat(1.0f, -1.0f);
		addBoid(new Boid(vec3(x, y, 0.0f), vec3(vX, vY, 0.0f)));
		//addCollider(new CollisionObject(((xMax + 20.0f) - (xMin - 20.0f))/2.0f, vec3(0.0f, 0.0f, 0.0f), true));
		addCollider(new CollisionObject(2.0f, vec3(0.0f, 0.0f, 0.0f), false));
	}
}
void BoidSystem :: addBoid(Boid * b) {
	boids.push_back(b);
}
void BoidSystem :: addCollider(CollisionObject * c) {
	colliders.push_back(c);
}
void BoidSystem :: getBoidLocations(vector<float> * locationBuf) {
	for (int i = 0; i < boids.size(); i++) {
		vec3 bPos = boids[i]->getPosition();
		float theta = boids[i]->getAngle();

		vec3 v1 = rotateZ(vec3(0.0f, 1.0f, 0.0f), theta) + bPos;
		vec3 v2 = rotateZ(vec3(0.25f, 0.0f, 0.0f), theta) + bPos;
		vec3 v3 = rotateZ(vec3(-0.25f, 0.0f, 0.0f), theta) + bPos;

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