#include "UAMotion.h"
#include <algorithm>

UAMotion::UAMotion(int dimensions, float maxVelocity, float friction) :
	velocity(new float[dimensions] { 0 }),
	realVelocity(new float[dimensions] { 0 }),
	maxVelocity(maxVelocity),
	friction(friction),
	acceleration(new float[dimensions] { 0 }) {

}

UAMotion::UAMotion(float maxVelocity, float friction) : UAMotion(1, maxVelocity, friction) {

}

float UAMotion::update(int dimension, float elapsedTime) {
	float acceleration = this->acceleration[dimension], velocity = this->realVelocity[dimension], length = 0;

	if (acceleration != 0) {
		if (acceleration > 0)
			acceleration -= friction;
		else
			acceleration += friction;

		if (acceleration == 0 || (velocity == maxVelocity && acceleration > 0)
			|| (velocity == -maxVelocity && acceleration < 0))
			length += velocity * elapsedTime;
		else {
			float reachMax;

			if (acceleration > 0)
				reachMax = (maxVelocity - velocity) / acceleration;
			else
				reachMax = (-maxVelocity - velocity) / acceleration;

			if (reachMax >= elapsedTime) {
				length += velocity * elapsedTime + acceleration * elapsedTime * elapsedTime / 2.f;
				this->realVelocity[dimension] += acceleration * elapsedTime;

				if (velocity > maxVelocity)
					this->realVelocity[dimension] = maxVelocity;
				else if (velocity < -maxVelocity)
					this->realVelocity[dimension] = -maxVelocity;
			} else {
				length += velocity * reachMax + acceleration * reachMax * reachMax / 2.f;

				if (acceleration > 0)
					this->realVelocity[dimension] = maxVelocity;
				else
					this->realVelocity[dimension] = -maxVelocity;

				length += velocity * reachMax;
			}
		}
	} else if (velocity != 0) {
		float friction = (velocity > 0) ? -this->friction : this->friction;
		float reachZero = -velocity / friction;

		if (reachZero >= elapsedTime) {
			length += velocity * elapsedTime + friction * elapsedTime * elapsedTime / 2.f;
			this->realVelocity[dimension] += friction * elapsedTime;
		}
		else {
			length += velocity * reachZero + friction * reachZero * reachZero / 2.f;
			this->realVelocity[dimension] = 0;
		}
	}
	return length;
}

float UAMotion::update(float elapsedTime) {
	return update(1, elapsedTime);
}

void UAMotion::stop(int dimension) {
	acceleration[dimension] = 0;
	velocity[dimension] = 0;
}

void UAMotion::stop() {
	stop(0);
}

float UAMotion::getVelocity(int dimension) {
	return this->velocity[dimension];
}

float UAMotion::getVelocity() {
	return getVelocity(0);
}

float UAMotion::getRealVelocity(int dimension) {
	return this->realVelocity[dimension];
}

float UAMotion::getRealVelocity() {
	return getRealVelocity(0);
}

void UAMotion::setVelocity(int dimension, float velocity) {
	this->velocity[dimension] = velocity;
	this->realVelocity[dimension] = std::clamp(velocity, -maxVelocity, maxVelocity);
}

void UAMotion::setVelocity(float velocity) {
	setVelocity(0, velocity);
}

void UAMotion::addVelocity(int dimension, float velocity) {
	this->velocity[dimension] += velocity;
	this->realVelocity[dimension] = std::clamp(this->velocity[dimension] , -maxVelocity, maxVelocity);
}

void UAMotion::addVelocity(float velocity) {
	addVelocity(0, velocity);
}