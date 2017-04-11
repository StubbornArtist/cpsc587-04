#pragma once
#include <glm/common.hpp>
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include <vector>
#include "CollisionObject.h"
using namespace glm;
using namespace std;
class Boid {

private:
	vec3 velocity;
	vec3 position;
	vec3 acceleration;
	float theta;
	float phi;
	vec3 limit(vec3 p, float max);
	vec3 obstacles(vector<CollisionObject *> colliders, float rA, float maxSpeed, float maxForce);
	vec3 avoid(vector<Boid *> boids, float rA, float maxSpeed, float maxForce);
	vec3 cohesion(vector<Boid *> boids,float rC, float maxSpeed, float maxForce);
	vec3 gathering(vector<Boid *> boids, float rG, float maxSpeed, float maxForce);
	vec3 seek(vec3 p, float maxSpeed,  float maxForce);
	vec3 followMouse(vec2 mousePos, float maxSpeed, float maxForce);
public:
	Boid(vec3 p, vec3 v);
	void setVelocity(vec3 v);
	vec3 getVelocity();
	void setPosition(vec3 p);
	vec3 getPosition();
	vec3 getAcceleration();
	void addToAcceleration(vec3 a);
	void clearAcceleration();
	void updateAngle();
	float getAngle();
	void run(vec2 mousePos, vector<Boid *> boids, vector<CollisionObject *> colliders, float rA, float rC, float rG, float maxSpeed, float maxForce, float dT);
};
