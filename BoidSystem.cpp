#include "BoidSystem.h"

BoidSystem::BoidSystem(float DT, float RA, float RC, float RG) {
	boids = vector<Boid *>();
	BoidSystem :: DT = DT;
	BoidSystem :: RA = RA;
	BoidSystem :: RC = RC;
	BoidSystem :: RG = RG;
}
void BoidSystem :: simulate() {

	//calculate forces of repulsion, cohesion, and gathering for each pair of boids  
	for (int i = 0; i < boids.size(); i++) {
		Boid * curB = boids.at(i);
		vec3 vA = vAve(curB);
		for (int j = i + 1; j < boids.size(); j++) {
			Boid * b = boids.at(j);
			vec3 dir = curB->getPosition() - b->getPosition();
			float d = length(dir);
			//if they are overlapping pretend they have a slight seperation to avoid division by zero later
			//d = (d == 0.0f) ? FLT_EPSILON : d;
			vec3 f = vec3(0.0f);
			if (d < RA) f += forceAvoid(d) * dir *(1 / d);
			else if (d < RC) f += forceCohesion(d) * (vA - curB->getVelocity());
			else if (d < RG) f += -forceGather(d) * dir * (1 / d);
			curB->addToForce(f);
			b->addToForce(-f);
		}
	}
	//update velocity and position based upon calculated forces
	for each (Boid * b in boids) {
		vec3 v = (b->getVelocity() + b->getForce() * (float)DT);
		b->setVelocity(v);
		b->setPosition(b->getPosition() + b->getVelocity() * (float)DT);
		b->updateOrientation();
		b->clearForce();
	}
}

void BoidSystem::randomize(int flock_size) {
	for (int i = 0; i < flock_size; i++) {
		float x = randomFloat(50.0f, -50.0f);
		float y = randomFloat(50.0f, -50.0f);
		float z = randomFloat(10.0f, -10.0f);
		float vX = randomFloat(5.0f, -5.0f);
		float vY = randomFloat(5.0f, -5.0f);
		float vZ = randomFloat(1.0f, -1.0f);
		Boid * b = new Boid(vec3(x, y, z), vec3(vX, vY, vZ));
		b->updateOrientation();
		addBoid(b);
	}
}
void BoidSystem::addBoid(Boid * b) {
	boids.push_back(b);
}

void BoidSystem :: addCollider(CollisionObject * c) {
	colliders.push_back(c);
}
void BoidSystem::getBoidLocations(vector<float> * locationBuf) {
	for each (Boid * b in boids) {
		vec4 bPos = vec4(b->getPosition(), 1.0f);
		mat4 or = b->getOrientation();

		vec4 v1 = or * vec4(bPos.x, bPos.y + 1.0f, bPos.z, 1.0f);
		vec4 v2 = or * vec4(bPos.x + 1.0f, bPos.y, bPos.z, 1.0f);
		vec4 v3 = or * vec4(bPos.x - 1.0f, bPos.y, bPos.z, 1.0f);

		locationBuf->push_back(v1.x);
		locationBuf->push_back(v1.y);
		locationBuf->push_back(v1.z);

		locationBuf->push_back(v2.x);
		locationBuf->push_back(v2.y);
		locationBuf->push_back(v2.z);

		locationBuf->push_back(v3.x);
		locationBuf->push_back(v3.y);
		locationBuf->push_back(v3.z);

		/*
		vec4 p1 = or * (bPos+ vec4(0.0f, -0.5f, -0.5f, 0.0f));
		vec4 p2 = or *(bPos + vec4(0.5f, -0.5f, 0.0f, 0.0f));
		vec4 p3 = or *(bPos + vec4(0.0f, 0.5f, 0.5f, 0.0f));
		vec4 p4 = or *(bPos + vec4(-0.5f, -0.5f, 0.0f, 0.0f));

		//first triangle
		locationBuf->push_back(p1.x);
		locationBuf->push_back(p1.y);
		locationBuf->push_back(p1.z);

		locationBuf->push_back(p3.x);
		locationBuf->push_back(p3.y);
		locationBuf->push_back(p3.z);

		locationBuf->push_back(p2.x);
		locationBuf->push_back(p2.y);
		locationBuf->push_back(p2.z);

		//second triangle
		locationBuf->push_back(p4.x);
		locationBuf->push_back(p4.y);
		locationBuf->push_back(p4.z);

		locationBuf->push_back(p3.x);
		locationBuf->push_back(p3.y);
		locationBuf->push_back(p3.z);

		locationBuf->push_back(p1.x);
		locationBuf->push_back(p1.y);
		locationBuf->push_back(p1.z);

		//third triangle
		locationBuf->push_back(p4.x);
		locationBuf->push_back(p4.y);
		locationBuf->push_back(p4.z);

		locationBuf->push_back(p3.x);
		locationBuf->push_back(p3.y);
		locationBuf->push_back(p3.z);

		locationBuf->push_back(p2.x);
		locationBuf->push_back(p2.y);
		locationBuf->push_back(p2.z);


		//fourth triangle
		locationBuf->push_back(p2.x);
		locationBuf->push_back(p2.y);
		locationBuf->push_back(p2.z);

		locationBuf->push_back(p1.x);
		locationBuf->push_back(p1.y);
		locationBuf->push_back(p1.z);

		locationBuf->push_back(p4.x);
		locationBuf->push_back(p4.y);
		locationBuf->push_back(p4.z);
		*/
	}

}
vec3 BoidSystem:: vAve(Boid * curBoid) {
	vec3 v = vec3(0.0f);
	for each(Boid * b in boids) {
		float d = length(b->getPosition() - curBoid->getPosition());
		if(d < RC) v += b->getVelocity();
	}

	v /= (float)boids.size();
	return v;
}
float BoidSystem :: forceAvoid(float d) {
	float f = 1 / (d * d);

	if (f > FMAX) return (float)FMAX;
	return f;
}

float BoidSystem::forceCohesion(float d) {
	float f = 0.1f * d * d;

	if (f > FMAX) return (float)FMAX;
	return f;
}
float BoidSystem::forceGather(float d) {
	float f = 0.1f * d * d;

	if (f > FMAX) return (float)FMAX;
	return f;
}

float BoidSystem:: randomFloat(float lBound, float hBound) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = hBound - lBound;
	float r = random * diff;
	return lBound + r;
}

void BoidSystem::clamp(vec3 * f, vec3 max) {
	if (abs(f->x) > max.x) {
		f->x = sign(f->x) * max.x;
	}
	if (abs(f->y) > max.y) {
		f->y = sign(f->y) * max.y;
	}
	if (abs(f->z) > max.z) {

	}
}