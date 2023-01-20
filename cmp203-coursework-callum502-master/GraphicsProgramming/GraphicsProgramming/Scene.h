// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
#include "ProceduralModel.h"
#include "Camera.h"
#include "CarCamera.h"
#include "Skybox.h"
#include "Model.h"
#include "Shadow.h"

class Scene{

public:
	Scene(Input *in);
	// Main render function
	void render();
	void renderShadows();
	void renderGround();
	void renderLights();
	void renderMirror();
	// Handle input function that receives delta time from parent.
	void handleInput(float dt);
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);

protected:
	// configure opengl render pipeline
	void initialiseOpenGL();
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	void calculateFPS();

	// draw primitive functions
	ProceduralModel proceduralModel;

	// For access to user input.
	Input* input;
		
	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];


	//camera & skybox
	Camera camera;
	CarCamera carCamera;
	Skybox skybox;

	//textures
	GLuint sand;
	GLuint skyboxTex;
	GLuint skyboxTexN;
	GLuint patrickHouse;
	GLuint sun;
	GLuint imposter;
	GLuint road;
	GLuint window;

	//models
	Model pineapple;
	Model spongebob;
	Model patrick;
	Model squidHouse;
	Model squidward;
	Model lamp;
	Model lamp_off;
	Model krustyKrab;
	Model mrKrabs;
	Model plankton;
	Model car;
	Model weenie;
	Model weenieSign;
	Shadow shadow;

	//booleans for different modes
	bool wireframe, night, drive;
	//for applying rotation
	float rotation;
	//for generating shadow matrices
	float shadowMatrix[16];
};

#endif