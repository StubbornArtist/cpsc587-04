#include "Boid.h"

Boid::Boid(vec3 p, vec3 v) {
	setPosition(p);
	setVelocity(v);
	updateAngle();
	clearAcceleration();
}
//Apply avoidance, gathering, and cohesive forces
void Boid::run(vector<Boid *> boids, vector<CollisionObject *> colliders, float rA, float rC, float rG, float maxSpeed, float maxForce, float dT) {
	
	vec3 avoidForce = avoid(boids, rA, maxSpeed, maxForce);
	vec3 cohesionForce = cohesion(boids, rC, maxSpeed, maxForce);
	vec3 gatherForce = gathering(boids, rG, maxSpeed, maxForce);
	vec3 obstacleForce = obstacles(colliders, rA, maxSpeed, maxForce);

	//give each force a weight
	avoidForce *= 1.3f;
	cohesionForce *= 0.7f;
	gatherForce *= 0.8f;
	obstacleForce *= 0.3f;

	//add this force the the acceleration
	addToAcceleration(avoidForce + cohesionForce + gatherForce + obstacleForce);

	//update the velocity and then the position accordingly
	velocity += acceleration * dT;
	velocity = limit(velocity, maxSpeed);
	position += velocity * dT;
	//update the boids orientation
	updateAngle();
	//clear the acceleration for next simulation step
	clearAcceleration();
}

//Apply a repsulsive force between all boids that are within radius rA to this boid
vec3 Boid::avoid(vector<Boid *> boids, float rA, float maxSpeed, float maxForce) {
	vec3 v = vec3(0.0f);
	int count = 0;


	for (int i = 0; i < boids.size(); i++) {
		Boid * b = boids[i];
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
//Apply a force that will move this boid towards the general area of all other neighbouring boids within the radius rC
vec3 Boid::cohesion(vector<Boid *> boids, float rC, float maxSpeed, float maxForce) {
	vec3 p = vec3(0.0f);
	int count = 0;
	for (int i = 0; i < boids.size(); i++) {
		Boid * b = boids[i];
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
//Apply a force which will make this boid match the average velocity of all neighbouring boids within a distance of rG from it
vec3 Boid::gathering(vector<Boid *> boids, float rG, float maxSpeed, float maxForce) {
	//velocity sum
	vec3 v = vec3(0.0f);
	int count = 0;

	for (int i = 0; i < boids.size(); i++) {
		Boid * b = boids[i];
		vec3 dir = position - b->getPosition();
		float d = length(dir);
		if (d < rG && d > 0) {
			//add neighbour velocity to sum
			v += b->getVelocity();
			count++;
		}
	}

	//average the velocity
	if (count > 0) {
		v /= (float)count;
		v = (normalize(v) * maxSpeed) - velocity;
		v = limit(v, maxForce);
		return v;
	}

	return vec3(0.0f);
}
//Apply a force from a sphere which increases as the bid gets closer to it (acts as walls for this simulation)
vec3 Boid::obstacles(vector<CollisionObject *> colliders, float rA, float maxSpeed, float maxForce) {
	vec3 v = vec3(0.0f);
	for (int i = 0; i < colliders.size(); i++) {
		CollisionObject * collider = colliders[i];
		vec3 c = collider->getCenter();
		float d = collider->getRadius() - length(position - c);
		//force points towards the center of the sphere 
		v += normalize(c - position) / (d * d);
	}
	if (length(v) > 0) {
		v = (normalize(v) * maxSpeed) - velocity;
		v = limit(v, maxForce);
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
//Determine the angle of the boid based upon it's normalized velocity vector
void Boid::updateAngle() {
	vec3 vN = normalize(velocity);
	theta = -atan2f(vN.x, vN.y);
}
float Boid::getAngle() {
	return theta;
}

