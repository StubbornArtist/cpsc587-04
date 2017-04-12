#pragma once
#include <glm/common.hpp>
#include <glm/glm.hpp>

using namespace glm;

class CollisionObject {

private:
	float radius;
	vec3 center;
	bool inverted;

public:
	CollisionObject(float r, vec3 c, bool inverted);
	bool collides(vec3 p, vec3 d, float * t);
	float getRadius();
	vec3 getCenter();
	bool isInverted();

};
