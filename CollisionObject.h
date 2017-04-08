#pragma once
#include <glm/common.hpp>
#include <glm/glm.hpp>

using namespace glm;

class CollisionObject {

private:
	vec3 normal;
	vec3 point;

public:
	CollisionObject(vec3 n, vec3 p);
	vec3 getNormal();
	void setNormal(vec3 norm);
	vec3 getPoint();
	void setPoint(vec3 p);

};
