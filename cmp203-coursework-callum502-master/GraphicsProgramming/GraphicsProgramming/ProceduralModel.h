#pragma once
#define _USE_MATH_DEFINES
#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include  <math.h>
class ProceduralModel
{
public:
	void renderDisc();
	void renderSphere();
	void renderCylinder();
	void renderSemiSphere();
	void renderQuad();
private:
	float r = 1, angle, interval;
	float latInterval, longInterval, longAngle = 0, latAngle = 0;
	float segments = 100, longitude = 50, latitude = 50;
	float height = 1.5;


};

