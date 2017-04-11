#include "CollisionObject.h"

CollisionObject::CollisionObject(float r, vec3 c, bool inverted) {
	radius = r;
	center = c;
	CollisionObject::inverted = inverted;
}
bool CollisionObject::collides(vec3 r) {
	if ( inverted && length(r) >= radius) {
		return true;
	}
	else if (!inverted && length(r) <= radius) {
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