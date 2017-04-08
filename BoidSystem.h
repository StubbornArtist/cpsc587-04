#pragma once
#include<vector>
#include <random>
#include <iostream>
#include "Boid.h"
#include "CollisionObject.h"

#define FMAX 0.03f
#define VMAX 0.25f

using namespace std;
class BoidSystem {
private:
	vector<Boid *> boids;
	vector<CollisionObject *> colliders;
	float DT;
	float RA;
	float RC;
	float RG;
	float forceAvoid(float d);
	float forceCohesion(float d);
	float forceGather(float d);
	float randomFloat(float lBound, float hBound);
	vec3 vAve(Boid * curBoid);
	void clamp(vec3 * f, vec3 max);
public:
	BoidSystem(float DT, float RA, float RC, float RG);
	void simulate();
	void randomize(int flock_size);
	void addBoid(Boid * b);
	void addCollider(CollisionObject * c);
	void getBoidLocations(vector<float> * locationBuf);
};