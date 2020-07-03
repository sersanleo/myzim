#include "Camera.h"

#include <glm/gtx/transform.hpp>

const float Camera::YAW_MAXVELOCITY = glm::radians<float>(105);
const float Camera::YAW_FRICTION = glm::radians<float>(800);
const float Camera::YAW_ACCELERATION = glm::radians<float>(3000) + YAW_FRICTION;

const float Camera::PITCH_MIN = glm::radians<float>(2);
const float Camera::PITCH_MAX = glm::radians<float>(90);

const float Camera::ROT_MANUAL_VELOCITY = glm::radians<float>(0.01f); // VARIAR SEGÚN RESOLUCIÓN
const float Camera::ROT_MANUAL_VELOCITY_POW = 1.775f;

const float Camera::POS_MAXVELOCITY = 3.5f;
const float Camera::POS_FRICTION = 10;
const float Camera::POS_ACCELERATION = 40 + POS_FRICTION;
const float Camera::POS_ZOOM_INFLUENCE = 3.5f;
const float Camera::POS_Y = 1;

const float Camera::ZOOM_MIN = 0;
const float Camera::ZOOM_MAX = 16;
const float Camera::ZOOM_MAXVELOCITY = 20;
const float Camera::ZOOM_VELOCITY = 4;
const float Camera::ZOOM_FRICTION = 25;

Camera::Camera(World* world, float x, float z, float zoom, float yaw, float pitch) {
	this->world = world;
	this->window = world->screen->window;

	setYaw(yaw);
	setPitch(pitch);
	setZoom(zoom);
	this->worldLoc = new glm::vec3(x, POS_Y, z);
}

void Camera::setYaw(float yaw) {
	this->yaw = glm::mod(yaw, glm::two_pi<float>());
	//yawVec.setRotationVector(rot);
	//updateRotVector();
	dirty = true;
}

void Camera::setPitch(float pitch) {
	this->pitch = glm::clamp(pitch, PITCH_MIN, PITCH_MAX);
	//updateRotVector();
	dirty = true;
}

void Camera::setZoom(float zoom) {
	if (zoom <= ZOOM_MIN) {
		this->zoom = ZOOM_MIN;
		zoomMotion->stop();
	} else if (zoom >= ZOOM_MAX) {
		this->zoom = ZOOM_MAX;
		zoomMotion->stop();
	} else
		this->zoom = zoom;

	this->zoomInfluence = (zoom - ZOOM_MIN) * POS_ZOOM_INFLUENCE / ZOOM_MAX + 1;
	dirty = true;
}

/*void Camera::moveHorizontally(float xOffset) {
	worldLoc.addXZ(yawVec.x, yawVec.y, xOffset);
	dirty = true;
}

void Camera::moveVertically(float zOffset) {
	worldLoc.addXZ(yawVec.y, -yawVec.x, zOffset);
	dirty = true;
}

void Camera::updateWorldLocVector() {
}

void Camera::updateLocVector() {
	loc.set(worldLoc.x, world.terrain.getHeight(worldLoc.x, worldLoc.z) + worldLoc.y, worldLoc.z).add(rotVec, zoom);
	float minHeight = world.terrain.getHeight(loc.x, loc.z) + POS_Y;
	if (loc.y < minHeight)
		loc.y = minHeight;
	dirty = false;
}

void Camera::updateRotVector() {
	rotVec.set(0, 0, 1).rotateAroundXAxis(-pitch).rotateAroundYAxis(yawVec.x, -yawVec.y);
}

void Camera::updateHorizontalAcceleration() {
	worldLocMotion.acceleration[0] = 0;
	if (left) {
		if (!right)
			worldLocMotion.acceleration[0] = -POS_ACCELERATION;
	} else if (right)
		worldLocMotion.acceleration[0] = POS_ACCELERATION;
}

void Camera::updateVerticalAcceleration() {
	worldLocMotion.acceleration[1] = 0;
	if (down) {
		if (!up)
			worldLocMotion.acceleration[1] = -POS_ACCELERATION;
	} else if (up)
		worldLocMotion.acceleration[1] = POS_ACCELERATION;
}

void Camera::updateProjectionMatrix() {
	this.projectionMatrix = Matrix4f.perspective(fov, (float) window.getWidth() / window.getHeight(), nearPlane,
			farPlane);
	// shader.loadProjectionMatrix(Matrix4f.orthographic(0, 10, 0, 10 * (float)
	// this.height / this.width, 0.01f, 1000));
	shader.loadProjectionMatrix(this.projectionMatrix);
}

void Camera::updateViewMatrix() {
	this.viewMatrix = new Matrix4f().rotateAroundXAxis(pitch).rotateAroundYAxis(yaw).translate(-loc.x, -loc.y,
			-loc.z);
	shader.loadViewMatrix(this.viewMatrix);
}

void Camera::updateTransformationMatrix(Matrix4f m) {
	shader.loadTransformationMatrix(m);
}

void Camera::start() {
	shader.use();
}

void Camera::stop() {
	shader.unbind();
}

void Camera::onResize(int width, int height) {
	posManualFactor = 4 * POS_MAXVELOCITY / Math.min(width, height);
	shader.use();
	updateProjectionMatrix();
	shader.unbind();
}

void Camera::onCursorPos(int oldX, int oldY, int newX, int newY) {
	switch (mode) {
	case ROTATING:
		int offsetX = newX - oldX, offsetY = newY - oldY;
		float velocityX, velocityY;

		if (offsetX < 0)
			velocityX = (float) -Math.pow(-offsetX, ROT_MANUAL_VELOCITY_POW);
		else
			velocityX = (float) Math.pow(offsetX, ROT_MANUAL_VELOCITY_POW);
		setYaw(yaw + ROT_MANUAL_VELOCITY * velocityX);

		if (offsetY < 0)
			velocityY = (float) -Math.pow(-offsetY, ROT_MANUAL_VELOCITY_POW);
		else
			velocityY = (float) Math.pow(offsetY, ROT_MANUAL_VELOCITY_POW);
		setPitch(pitch - ROT_MANUAL_VELOCITY * velocityY);
		break;
	case MOVING:
		worldLocMotion.acceleration[0] = POS_FRICTION;
		worldLocMotion.acceleration[1] = POS_FRICTION;
		worldLocMotion.setVelocity(0, (newX - anchor.x) * posManualFactor);
		worldLocMotion.setVelocity(1, -(newY - anchor.y) * posManualFactor);
		break;
	default:
		break;
	}
}

void Camera::onMouseButton(int button, int action, int x, int y) {
	switch (button) {
	case GLFW_MOUSE_BUTTON_MIDDLE:
		if (action == GLFW_PRESS) {
			mode = CameraMode.ROTATING;
			glfwSetInputMode(window.id, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		} else if (action == GLFW_RELEASE) {
			mode = CameraMode.NORMAL;
			glfwSetInputMode(window.id, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		if (action == GLFW_PRESS) {
			mode = CameraMode.MOVING;
			anchor.set(x, y);
			up = false;
			down = false;
			left = false;
			right = false;
		} else if (action == GLFW_RELEASE) {
			mode = CameraMode.NORMAL;
			worldLocMotion.acceleration[0] = 0;
			worldLocMotion.acceleration[1] = 0;
		}
		break;
	case GLFW_MOUSE_BUTTON_LEFT:
		MousePicker mousePicker = new MousePicker(this);
		mousePicker.calculateMouseRay(x, y);
		break;
	}
}

void Camera::onKey(int key, int action) {
	switch (key) {
	case GLFW_KEY_COMMA:
		if (action == GLFW_PRESS)
			yawMotion.acceleration[0] += YAW_ACCELERATION;
		else if (action == GLFW_RELEASE)
			yawMotion.acceleration[0] -= YAW_ACCELERATION;
		break;

	case GLFW_KEY_PERIOD:
		if (action == GLFW_PRESS)
			yawMotion.acceleration[0] -= YAW_ACCELERATION;
		else if (action == GLFW_RELEASE)
			yawMotion.acceleration[0] += YAW_ACCELERATION;
		break;
	}

	if (mode != CameraMode.MOVING)
		switch (key) {
		case GLFW_KEY_W:
			if (action == GLFW_PRESS)
				up = true;
			else if (action == GLFW_RELEASE)
				up = false;
			updateVerticalAcceleration();
			break;

		case GLFW_KEY_A:
			if (action == GLFW_PRESS)
				left = true;
			else if (action == GLFW_RELEASE)
				left = false;
			updateHorizontalAcceleration();
			break;

		case GLFW_KEY_S:
			if (action == GLFW_PRESS)
				down = true;
			else if (action == GLFW_RELEASE)
				down = false;
			updateVerticalAcceleration();
			break;

		case GLFW_KEY_D:
			if (action == GLFW_PRESS)
				right = true;
			else if (action == GLFW_RELEASE)
				right = false;
			updateHorizontalAcceleration();
			break;
		}
}

void Camera::onScroll(float xOffset, float yOffset) {
	float velocity = zoomMotion.getRealVelocity();
	if ((velocity > 0 && yOffset > 0) || (velocity < 0 && yOffset < 0))
		velocity = 0;
	zoomMotion.setVelocity(velocity - yOffset * ZOOM_VELOCITY);
}

void Camera::update(float elapsedTime) {
	float yawOffset = yawMotion.update(elapsedTime);
	if (yawOffset != 0)
		setYaw(yaw + yawOffset);

	float zoomOffset = zoomMotion.update(elapsedTime);
	if (zoomOffset != 0)
		setZoom(zoom + zoomOffset);

	float xOffset = worldLocMotion.update(0, elapsedTime);
	if (xOffset != 0)
		moveHorizontally(xOffset * zoomInfluence);

	float zOffset = worldLocMotion.update(1, elapsedTime);
	if (zOffset != 0)
		moveVertically(zOffset * zoomInfluence);

	if (xOffset != 0 || zOffset != 0)
		updateWorldLocVector();

	if (dirty)
		updateLocVector();

	start();
	updateViewMatrix();
	stop();
}*/