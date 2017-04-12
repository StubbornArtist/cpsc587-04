#pragma once
#include<vector>
#include <random>
#include <iostream>
#include "Boid.h"
#include "CollisionObject.h"

using namespace std;
class BoidSystem {
private:
	vector<Boid *> boids;
	vector<CollisionObject *> colliders;
	float DT;
	float RA;
	float RC;
	float RG;
	float vMax;
	float fMax;
	float randomFloat(float lBound, float hBound);
public:
	BoidSystem(float DT, float RA, float RC, float RG, float vMax, float fMax);
	void simulate();
	void randomize(int flock_size, float yMax, float xMax, float yMin, float xMin);
	void addBoid(Boid * b);
	void addCollider(CollisionObject * c);
	void getBoidLocations(vector<float> * locationBuf);
	void getColliderPositions(vector<float> * colliderBuf);
	float getDeltaT();
};