#include "Camera.h"
Camera::Camera()
{
	//set inital pos
	position.x = 0;
	position.y = 0;
	position.z = 6;
	//centre mouse & hide cursor
	glutWarpPointer(1280 / 2, 720 / 2);
	glutSetCursor(GLUT_CURSOR_NONE);
}
void Camera::update(Input* input, float width, float height, float dt)
{
	float cosR, cosP, cosY;//temp values for sin/cos 
	float sinR, sinP, sinY;

	cosY = cosf(rotation.x * 3.1415 / 180);
	cosP = cosf(rotation.y * 3.1415 / 180);
	cosR = cosf(rotation.z * 3.1415 / 180);
	sinY = sinf(rotation.x * 3.1415 / 180);
	sinP = sinf(rotation.y * 3.1415 / 180);
	sinR = sinf(rotation.z * 3.1415 / 180);

	//forward vector
	forward.x = sinY * cosP;
	forward.y = sinP;
	forward.z = cosP * -cosY;

	// Up Vector
	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;

	// Side Vector (right)
	right = forward.cross(up);

	//apply rotation in appropriate direction if mouse has moved
	if (xDistance > 2)
	{
		rotation.x += 200 * dt;
	}
	if (xDistance < -2)
	{
		rotation.x -= 200 * dt;
	}
	if (yDistance > 2)
	{
		rotation.y -= 200 * dt;
	}
	if (yDistance < -2)
	{
		rotation.y += 200 * dt;
	}
	//centre mouse
	glutWarpPointer(width / 2, height / 2);
	//calculate distance mouse has moved
	xDistance = input->getMouseX() - width / 2;
	yDistance = input->getMouseY() - height / 2;

	//move in appropriate direction when keyboard input is received
	//forwards
	if (input->isKeyDown('w'))
	{
		position.x += (10 * forward.x * dt);
		position.y += (10 * forward.y * dt);
		position.z += (10 * forward.z * dt);
	}
	//backwards
	if (input->isKeyDown('s'))
	{
		position.x -= (10 * forward.x * dt);
		position.y -= (10 * forward.y * dt);
		position.z -= (10 * forward.z * dt);
	}
	//left
	if (input->isKeyDown('a'))
	{
		position.x -= (10 * right.x * dt);
		position.y -= (10 * right.y * dt);
		position.z -= (10 * right.z * dt);
	}
	//right
	if (input->isKeyDown('d'))
	{
		position.x += (10 * right.x * dt);
		position.y += (10 * right.y * dt);
		position.z += (10 * right.z * dt);
	}
	//up
	if (input->isKeyDown(101))//e key
	{
		//position.x += (10 * up.x * dt);
		position.y += (10 * dt);
		//position.z += (10 * up.z * dt);
	}
	//down
	if (input->isKeyDown(113))//q key
	{
		//position.x -= (10 * up.x * dt);
		position.y -= (10 * dt);
		//position.z -= (10 * up.z * dt);
	}
	lookAt = position + forward;
}

//getters & setters
Vector3 Camera::getPosition()
{
	return position;
}

Vector3 Camera::getlookAt()
{
	return lookAt;
}

Vector3 Camera::getUp()
{
	return up;
}

void Camera::setPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}