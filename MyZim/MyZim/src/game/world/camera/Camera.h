#pragma once
#include "../World.h"
#include "../../../animation/UAMotion.h"

class World;

class Camera
{
private:
	const static float YAW_MAXVELOCITY;
	const static float YAW_FRICTION;
	const static float YAW_ACCELERATION;

	const static float PITCH_MIN;
	const static float PITCH_MAX;

	const static float ROT_MANUAL_VELOCITY;
	const static float ROT_MANUAL_VELOCITY_POW;

	const static float POS_MAXVELOCITY;
	const static float POS_FRICTION;
	const static float POS_ACCELERATION;
	const static float POS_ZOOM_INFLUENCE;
	const static float POS_Y;

	const static float ZOOM_MIN;
	const static float ZOOM_MAX;
	const static float ZOOM_MAXVELOCITY;
	const static float ZOOM_VELOCITY;
	const static float ZOOM_FRICTION;

	UAMotion* yawMotion = new UAMotion(YAW_MAXVELOCITY, YAW_FRICTION);
	glm::vec2* yawVec = new glm::vec2();
	glm::vec3* rotVec = new glm::vec3();
	float yaw = 0, pitch = 0;

	UAMotion* worldLocMotion = new UAMotion(2, POS_MAXVELOCITY, POS_FRICTION);
	glm::vec3* worldLoc = new glm::vec3();
	float posManualFactor = 1;

	UAMotion* zoomMotion = new UAMotion(ZOOM_MAXVELOCITY, ZOOM_FRICTION);
	float zoom;
	float zoomInfluence;

	glm::vec3* loc = new glm::vec3();
	bool dirty = true;

	glm::ivec3* anchor = new glm::ivec3();

	glm::mat4x4* projectionMatrix = new glm::mat4x4();
	glm::mat4x4* viewMatrix = new glm::mat4x4();
	float fov = 70, nearPlane = 0.1f, farPlane = 1000;

	void setYaw(float yaw);
	void setPitch(float pitch);
	void setZoom(float zoom);
	void moveHorizontally(float xOffset);
	void moveVertically(float zOffset);
	void updateWorldLocVector();
	void updateLocVector();
	void updateRotVector();
	void updateHorizontalAcceleration();
	void updateVerticalAcceleration();
	const void updateProjectionMatrix();
	void updateViewMatrix();
public:
	World* world;
	Window* window;

	Camera(World* world, float x, float z, float zoom, float yaw, float pitch);
};

enum CameraMode { NORMAL, ROTATING, MOVING };