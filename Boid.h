#pragma once
#include <glm/common.hpp>
#include <glm/glm.hpp>


using namespace glm;
class Boid {

private:
	vec3 velocity;
	vec3 position;
	vec3 force;
	vec3 up;
	vec3 head;
	vec3 right;
public:
	Boid(vec3 p, vec3 v);
	void setVelocity(vec3 v);
	vec3 getVelocity();
	void setPosition(vec3 p);
	vec3 getPosition();
	void addToForce(vec3 fc);
	void setForce(vec3 f);
	vec3 getForce();
	void clearForce();
	void setUp(vec3 u);
	void setHead(vec3 h);
	void setRight(vec3 r);
	mat3 getOrientation();
	void updateOrientation();
};
