#include "CarCamera.h"
CarCamera::CarCamera()
{
	//set inital pos
	position.x = 0;
	position.y = 0;
	position.z = 6;
	//centre mouse & hide cursor
	glutWarpPointer(1280 / 2, 720 / 2);
	glutSetCursor(GLUT_CURSOR_NONE);
}
void CarCamera::update(Input* input, float dt)
{
	float cosR, cosP, cosY;//temp values for sin/cos from 
	float sinR, sinP, sinY;

	cosY = cosf(rotation.x * 3.1415 / 180);
	cosP = cosf(rotation.y * 3.1415 / 180);
	cosR = cosf(rotation.z * 3.1415 / 180);
	sinY = sinf(rotation.x * 3.1415 / 180);
	sinP = sinf(rotation.y * 3.1415 / 180);
	sinR = sinf(rotation.z * 3.1415 / 180);

	//forawrd vector
	forward.x = sinY * cosP;
	forward.y = sinP;
	forward.z = cosP * -cosY;

	// Up Vector
	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;

	// Side Vector (right)
	right = forward.cross(up);

	//move in appropriate direction when keyboard input is received
	//forwards
	if (input->isKeyDown('w') && position.z > -50)
	{
		position.x += (20 * forward.x * dt);
		position.y += (20 * forward.y * dt);
		position.z += (20 * forward.z * dt);
		direction = 180;
	}
	//backwards
	if (input->isKeyDown('s') && position.z < 50)
	{
		position.x -= (20 * forward.x * dt);
		position.y -= (20 * forward.y * dt);
		position.z -= (20 * forward.z * dt);
		direction = 0;
	}
	//left
	if (input->isKeyDown('a') && position.x > -50)
	{
		position.x -= (20 * right.x * dt);
		position.y -= (20 * right.y * dt);
		position.z -= (20 * right.z * dt);
		direction = -90;
	}
	//right
	if (input->isKeyDown('d') && position.x < 50)
	{
		position.x += (20 * right.x * dt);
		position.y += (20 * right.y * dt);
		position.z += (20 * right.z * dt);
		direction = 90;
	}

	//increase or decrease tilt of camera
	if (input->isKeyDown('e') && tilt < 50)
	{
		tilt += 1;
	}
	if (input->isKeyDown('q') && tilt > 1)
	{
		tilt -= 1;
	}
}

//getters & setters
Vector3 CarCamera::getPosition()
{
	return position;
}

Vector3 CarCamera::getUp()
{
	return up;
}

float CarCamera::getDirection()
{
	return direction;
}

void CarCamera::setPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

float CarCamera::getTilt()
{
	return tilt;
}