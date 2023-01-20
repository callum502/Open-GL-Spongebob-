#pragma once
#include "Vector3.h"
#include "Input.h"
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
class Camera
{
public:
	Camera();
	void update(Input* input, float width, float height, float dt);
	Vector3 getPosition();
	Vector3 getlookAt();
	Vector3 getUp();
	void setPosition(float x, float y, float z);
private:
	Vector3 rotation = (0, 0, 0), position, lookAt, up, forward, right;
	float xDistance = 0, yDistance = 0;

};

