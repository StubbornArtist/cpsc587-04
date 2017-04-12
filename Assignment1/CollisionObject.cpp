#include "CollisionObject.h"

CollisionObject::CollisionObject(float r, vec3 c, bool inverted) {
	radius = r;
	center = c;
	CollisionObject::inverted = inverted;
}
bool CollisionObject::collides(vec3 p, vec3 d, float * t ) {
	
	vec3 l = p - center;

	float a = dot(d, d);
	float b = dot(2.0f * d, l);
	float c = dot(l, l) - (radius * radius);

	float equ = (b * b) - (4.0f * a * c);

	if (equ > 0.0f) {
		float  t1 = ((-b + sqrt(equ)) / (2.0f * a));
		float t2 = ((-b - sqrt(equ)) / (2.0f * a));
		if (t1 > t2) {
			*t = t2;
		}
		*t = t1;
		return true;
	}

	return false;
}

float CollisionObject :: getRadius() {
	return radius;
}

vec3 CollisionObject::getCenter() {
	return center;
}

bool CollisionObject::isInverted() {
	return inverted;
}