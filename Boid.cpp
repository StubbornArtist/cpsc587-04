#include "Boid.h"

Boid::Boid(vec3 p, vec3 v) {
	setPosition(p);
	setVelocity(v);
	force = vec3(0.0f);
	updateOrientation();
}
void Boid::setVelocity(vec3 v) {
	velocity = v;
}
vec3 Boid::getVelocity() {
	return velocity;
}
void Boid::setPosition(vec3 p) {
	position = p;
}
vec3 Boid::getPosition() {
	return position;
}
void Boid::addToForce(vec3 fc) {
	force += fc;
}
vec3 Boid::getForce() {
	return force;
}
void Boid::setForce(vec3 f) {
	force = f;
}
void Boid::clearForce() {
	force = vec3(0.0f);
}
void Boid::setUp(vec3 u) {
	up = u;
}
void Boid::setHead(vec3 h) {
	head = h;
}
void Boid::setRight(vec3 r) {
	right = r;
}
mat3 Boid :: getOrientation() {
	return mat3(head, up, right);
}

void Boid::updateOrientation() {

	//calculate tangent vector
	vec3 t = normalize(velocity);
	vec3 temp = normalize((force - (dot(t, force) * t)) - vec3(0.0f, 9.81f, 0.0f));
	//calculate binormal vector
	vec3 b = normalize(cross(temp, t));
	//calculate normal vector
	vec3 n = cross(t, b);

	setHead(t);
	setRight(b);
	setUp(n);

}
