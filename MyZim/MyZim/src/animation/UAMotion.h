#pragma once
class UAMotion
{
private:
	float* const velocity;
	float* const realVelocity;
	const float maxVelocity, friction;
public:
	float* const acceleration;

	UAMotion(int dimensions, float maxVelocity, float friction);
	UAMotion(float maxVelocity, float friction);

	float update(int dimension, float elapsedTime);
	float update(float elapsedTime);
	void stop(int dimension);
	void stop();
	float getVelocity(int dimension);
	float getVelocity();
	float getRealVelocity(int dimension);
	float getRealVelocity();
	void setVelocity(int dimension, float velocity);
	void setVelocity(float velocity);
	void addVelocity(int dimension, float velocity);
	void addVelocity(float velocity);
};

