#include "Boid.h"

Boid::Boid(vec3 p, vec3 v) {
	setPosition(p);
	setVelocity(v);
	updateAngle();
	clearAcceleration();
}

void Boid::run(vec2 mousePos, vector<Boid *> boids, vector<CollisionObject *> colliders, float rA, float rC, float rG, float maxSpeed, float maxForce, float dT) {
	
	vec3 avoidForce = avoid(boids, rA, maxSpeed, maxForce);
	vec3 cohesionForce = cohesion(boids, rC, maxSpeed, maxForce);
	vec3 gatherForce = gathering(boids, rG, maxSpeed, maxForce);
	vec3 obstacleForce = obstacles(colliders, rA, maxSpeed, maxForce);
	vec3 mouse = seek(vec3(mousePos, 0.0f), maxSpeed, maxForce);

	avoidForce *= 1.5f;
	cohesionForce *= 0.8f;
	gatherForce *= 1.0f;
	obstacleForce *= 1.5f;
	mouse *= 0.5f;

	addToAcceleration(avoidForce + cohesionForce + gatherForce + mouse);

	vec3 prevV = velocity;

	velocity += acceleration * dT;
	velocity = limit(velocity, maxSpeed);
	position += velocity * dT;
	updateAngle();
	updateBank(prevV);
	clearAcceleration();

}
vec3 Boid::followMouse(vec2 mousePos, float maxSpeed, float maxForce) {
	vec3 v = vec3(0.0f);
	vec3 dir = position - vec3(mousePos, 0.0f);
	float d = length(dir);
	if (d > 0) {
		v = -normalize(dir) / d;
	}
	if (length(v) > 0) {
		v = ((normalize(v) * maxSpeed) - velocity);
		v = limit(v, maxForce);
	}
	return v;
}
vec3 Boid::avoid(vector<Boid *> boids, float rA, float maxSpeed, float maxForce) {
	vec3 v = vec3(0.0f);
	int count = 0;


	for each(Boid * b in boids) {
		vec3 dir = position - b->getPosition();
		float d = length(dir);
		if ((d < rA) && d > 0) {
			v += (normalize(dir) / d);
			count++;
		}
	}

	if (count > 0) {
		v /= (float)count;
	}

	if (length(v) > 0.0f) {
		v = ((normalize(v) * maxSpeed) - velocity);
		v = limit(v, maxForce);
	}

	return v;
}

vec3 Boid::cohesion(vector<Boid *> boids, float rC, float maxSpeed, float maxForce) {
	vec3 p = vec3(0.0f);
	int count = 0;
	for each (Boid * b in boids) {
		float d = length(position - b->getPosition());

		if (d < rC && d > 0) {
			p += b->getPosition();
			count++;
		}
	}

	if (count > 0) {
		p /= count;
		return seek(p, maxSpeed, maxForce);
	}
	return vec3(0.0f);
}

vec3 Boid::gathering(vector<Boid *> boids, float rG, float maxSpeed, float maxForce) {

	vec3 v = vec3(0.0f);
	int count = 0;

	for each (Boid * b in boids) {
		vec3 dir = position - b->getPosition();
		float d = length(dir);
		if (d < rG && d > 0) {
			v += b->getVelocity();
			count++;
		}
	}

	if (count > 0) {
		v /= (float)count;
		v = (normalize(v) * maxSpeed) - velocity;
		v = limit(v, maxForce);
		return v;
	}

	return vec3(0.0f);
}

vec3 Boid::obstacles(vector<CollisionObject *> colliders, float rA, float maxSpeed, float maxForce) {
	vec3 v = vec3(0.0f);
	for each(CollisionObject * collider in colliders) {
		vec3 p = collider->closestPoint(position);
		vec3 dir = position - p;
		float d = length(dir);
		if (d < rA && d > 0) {
			vec3 w = position - p;
			v += normalize(dir)/d;
		}
	}
	return v;
}
vec3 Boid::seek(vec3 p, float maxSpeed, float maxForce) {
	vec3 dir = normalize(p - position) * maxSpeed;
	return limit((dir - velocity) , maxForce);
}

vec3 Boid::limit(vec3 p, float max) {
	if (length(p) > max) {
		vec3 p2 = normalize(p) * max;
		return p2;
	}
	return p;
}
void Boid::addToAcceleration(vec3 a) {
	acceleration += a;
}
vec3 Boid::getAcceleration() {
	return acceleration;
}
void Boid::clearAcceleration() {
	acceleration = vec3(0.0f);
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
void Boid::updateAngle() {
	vec3 vN = normalize(velocity);
	theta = -atan2f(vN.x, vN.y);
}
float Boid::getAngle() {
	return theta;
}

void Boid::updateBank(vec3 prevVelocity) {
	vec3 vN = normalize(velocity);
	vec3 pN = normalize(prevVelocity);
	float a1 = -atan2f(vN.x, vN.y);
	float a2 = -atan2f(pN.x, pN.y);
	if (a1 - a2 > 3.14f) {
		if (a1 < a2) {
			a1 += 2 * 3.14f;
		}
		else {
			a2 += 2 * 3.14f;
		}
	}
	phi = a1 - a2;
}
float Boid::getBank() {
	return phi;
}