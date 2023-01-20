#pragma once
#include "Vector3.h"
#include "Input.h"
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
class CarCamera
{
public:
	CarCamera();
	void update(Input* input, float dt);
	Vector3 getPosition();
	void setPosition(float x, float y, float z);
	Vector3 getUp();
	float getDirection();
	float getTilt();
private:
	Vector3 rotation = (0, 0, 0), position, up, forward, right;
	float direction, tilt = 25;

};

