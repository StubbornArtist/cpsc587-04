#include "CollisionObject.h"

CollisionObject::CollisionObject(vec3 n, vec3 p) {
	normal = n;
	point = p;
}
void CollisionObject::setNormal(vec3 norm) {
	normal = norm;
}

vec3 CollisionObject::getNormal() {
	return normal;
}

void CollisionObject::setPoint(vec3 p) {
	point = p;
}

vec3 CollisionObject::getPoint() {
	return point;
}

vec3 CollisionObject::closestPoint(vec3 p) {
	return (dot(point - p, normal) / dot(normal, normal)) * normal;
}