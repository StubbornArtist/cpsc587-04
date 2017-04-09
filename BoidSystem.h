#pragma once
#include<vector>
#include <random>
#include <iostream>
#include "Boid.h"
#include "CollisionObject.h"

#define FMAX 0.5f
#define VMAX 15.0f

using namespace std;
class BoidSystem {
private:
	vector<Boid *> boids;
	vector<CollisionObject *> colliders;
	float DT;
	float RA;
	float RC;
	float RG;
	float randomFloat(float lBound, float hBound);
public:
	BoidSystem(float DT, float RA, float RC, float RG);
	void simulate();
	void randomize(int flock_size);
	void addBoid(Boid * b);
	void addCollider(CollisionObject * c);
	void getBoidLocations(vector<float> * locationBuf);
};