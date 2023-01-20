#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
	initialiseOpenGL();

	// Other OpenGL / render setting should be applied here.
	glEnable(GL_TEXTURE_2D);

	// Initialise scene variables
	//load models
	pineapple.load("models/spongebob's house.obj", "gfx/home.png");
	spongebob.load("models/spongebob.obj", "gfx/spongebob.png");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	patrick.load("models/patrick.obj", "gfx/patrick.png");
	squidHouse.load("models/SquidwardHouse.obj", "gfx/squidwardhouse.png");
	squidward.load("models/squidward.obj", "gfx/squid.png");
	lamp.load("models/lamp1.obj", "gfx/light3.png");
	lamp_off.load("models/lamp1.obj", "gfx/light2.png");
	krustyKrab.load("models/Krusty Krab2.obj", "gfx/krustykrab01.png");
	mrKrabs.load("models/mrkrabs.obj", "gfx/mrkrabs.png");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	plankton.load("models/plankton.obj", "gfx/plankton.png");
	car.load("models/pattywagon.obj", "gfx/car.png");
	weenie.load("models/weenie.obj", "gfx/Tex_0046_0.png");
	weenieSign.load("models/weenieSign.obj", "gfx/Tex_0101_0.png");

	//load textures
	skyboxTex = SOIL_load_OGL_texture
	(
		"gfx/sbskybox.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	skyboxTexN = SOIL_load_OGL_texture
	(
		"gfx/sbskyboxN.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	sun = SOIL_load_OGL_texture
	(
		"gfx/sun.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	sand = SOIL_load_OGL_texture
	(
		"gfx/sand.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	patrickHouse = SOIL_load_OGL_texture
	(
		"gfx/pat2.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	imposter = SOIL_load_OGL_texture
	(
		"gfx/imposter.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	road = SOIL_load_OGL_texture
	(
		"gfx/road2.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	window = SOIL_load_OGL_texture
	(
		"gfx/untitled.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
}

//set plane coords for generating planr shadow
extern float planeVerts[] = { -50.0, -2.0, -50.0,	// Vertex #0 front tl
							-50.0, -2.0, 50.0,		// Vertex #1 front bl
							50.0,  -2.0, 50.0,		// Vertex #2 front br
							50.0,  -2.0, -50.0,		// Vertex #3 front tr	
};


void Scene::handleInput(float dt)
{
	// Handle user input
	//press p for wireframing
	if (input->isKeyDown('p'))
	{
		input->setKeyUp('p');
		wireframe = !wireframe;
		if (wireframe)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		}
	}

	if (input->isKeyDown('n'))
	{
		input->setKeyUp('n');
		night = !night;
	}

	if (input->isKeyDown('c'))
	{
		input->setKeyUp('c');
		drive = !drive;
		if (drive)
		{
			carCamera.setPosition(camera.getPosition().x, -2, camera.getPosition().z);
		}
		else
		{
			camera.setPosition(carCamera.getPosition().x, 0, carCamera.getPosition().z);
		}
	}
}

void Scene::update(float dt)
{
	// update scene related variables.
	camera.update(input, width, height, dt);
	carCamera.update(input, dt);
	// Calculate FPS for output
	calculateFPS();
}

void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the correct camera
	if (!drive)
	{
		gluLookAt(camera.getPosition().x, camera.getPosition().y, camera.getPosition().z, camera.getlookAt().x, camera.getlookAt().y, camera.getlookAt().z, camera.getUp().x, camera.getUp().y, camera.getUp().z);
	}
	else
	{
		gluLookAt(carCamera.getPosition().x, carCamera.getPosition().y + carCamera.getTilt(), carCamera.getPosition().z + 20, carCamera.getPosition().x, carCamera.getPosition().y, carCamera.getPosition().z, carCamera.getUp().x, carCamera.getUp().y, carCamera.getUp().z);
	}

	// Render geometry/scene here -------------------------------------

	//set correct skybox texture
	if (!night)
	{
		glBindTexture(GL_TEXTURE_2D, skyboxTex);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, skyboxTexN);
	}

	//render skybox at users position
	if (!drive)
	{
		skybox.renderSkybox(camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
	}
	else
	{
		skybox.renderSkybox(carCamera.getPosition().x, carCamera.getPosition().y + carCamera.getTilt(), carCamera.getPosition().z + 20);
	}

	//render mirror // I took this out as I could not get this to function as intended
	//renderMirror();

	//render lights
	renderLights();

	//render sun
	if (!night)
	{
		glPushMatrix();
			glTranslatef(0, 12.5, 50);
			glBindTexture(GL_TEXTURE_2D, sun);
			proceduralModel.renderDisc();
		glPopMatrix();
	}

	//setup stencil
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, NULL);
	//render ground
	renderGround();
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	//render shadows
	renderShadows();
	glDisable(GL_STENCIL_TEST);

	//render pineapple
	glPushMatrix();
		glTranslatef(6, -2, 0);
		pineapple.render();
		//render spongebob
		glPushMatrix();
			glTranslatef(-1, 0, 2);
			glScalef(1.1,1.1,1.1);
			spongebob.render();
			//render shadow (imposter)
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, imposter);
				glTranslatef(0.08, 0.02, 0.05); //centre & prevent z-fighting
				glRotatef(90, 1, 0, 0);
				glScalef(0.35,0.35,0.35);
				proceduralModel.renderDisc();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	//render patricks house
	glPushMatrix();
		glTranslatef(-6, -2, 0);
		glScalef(2, 2, 2);
		glBindTexture(GL_TEXTURE_2D, patrickHouse);
		proceduralModel.renderSemiSphere();
		//render patrick
		glPushMatrix();
			glScalef(0.5, 0.5, 0.5);
			glTranslatef(-1, 0, 2.5);
			patrick.render();
			//render shadow (imposter)
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, imposter);
				glTranslatef(0.0, 0.02, 0.00); //centre & prevent z-fighting
				glRotatef(90, 1, 0, 0);
				glScalef(0.5, 0.5, 0.5);
				proceduralModel.renderDisc();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	//render squidward's house
	glPushMatrix();
		glTranslatef(0, -2, 0);
		glScalef(0.4, 0.4, 0.4);
		squidHouse.render();
		//render squidward
		glPushMatrix();
			glTranslatef(-1.5, 0, 6);
			glScalef(0.5, 0.5, 0.5);
			squidward.render();
			//render shadow (imposter)
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, imposter);
				glTranslatef(0.1, 0.06, 0.05); //centre & prevent z-fighting
				glRotatef(90, 1, 0, 0);
				glScalef(2.5, 2.5, 2.5);
				proceduralModel.renderDisc();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	//render krusty krab
	glPushMatrix();
		glTranslatef(12, -2, 5);
		glScalef(0.13, 0.13, 0.13);
		glRotatef(-90, 0, 1, 0);
		krustyKrab.render();
	glPopMatrix();

	//render Mr Krabs
	glPushMatrix();
		glTranslatef(9, -2, 6);
		glScalef(0.1, 0.1, 0.1);
		glRotatef(-90, 0, 1, 0);
		mrKrabs.render();
		//render shadow (imposter)
		glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, imposter);
			glTranslatef(0.1, 0.2, 0.05); //centre & prevent z-fighting
			glRotatef(90, 1, 0, 0);
			glScalef(6, 6, 6);
			proceduralModel.renderDisc();
		glPopMatrix();
	glPopMatrix();

	//render weenie hut jr
	glPushMatrix();
		glTranslatef(-12, -2, 5);
		glRotatef(90, 0, 1, 0);
		glScalef(0.7, 0.7, 0.7);
		weenie.render();
	glPopMatrix();

	//render weenie hut jr sign
	glPushMatrix();
		glTranslatef(-10, 2.5, 5.5);
		glRotatef(90, 0, 1, 0);
		glRotatef(75, 1, 0, 0);
		glScalef(0.7, 0.7, 0.7);
		glScalef(2, 1.4, 1.4);
		weenieSign.render();
	glPopMatrix();

	//render Plankton
	glPushMatrix();
		glTranslatef(12, -2, -14);
		glRotatef(-30, 0, 1, 0);
		glScalef(0.5, 0.5, 0.5);
		plankton.render();
	glPopMatrix();

	//render lamp post
	glPushMatrix();
		glTranslatef(3, -2, 0);
		glScalef(0.04,0.05,0.04);
		if (!night)
		{
			lamp_off.render();
		}
		else
		{
			glDisable(GL_LIGHTING);
			lamp.render();
			glEnable(GL_LIGHTING);
		}
	glPopMatrix();

	//render lamp post 2
	glPushMatrix();
		glTranslatef(-3, -2, 0);
		glScalef(0.04, 0.05, 0.04);
		if (!night)
		{
			lamp_off.render();
		}
		else
		{
			glDisable(GL_LIGHTING);
			lamp.render();
			glEnable(GL_LIGHTING);
		}
	glPopMatrix();

	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void Scene::renderLights()
{
	//setup lights
	GLfloat light_pos[] = { 0,0.25,1,0 };
	GLfloat light1_pos[] = { -3,1.3,0,1 };
	GLfloat light2_pos[] = { 3,1.3,0,1 };
	GLfloat day_diffuse[] = { 3,3,3,1 };
	GLfloat night_diffuse[] = { 1.5,1.5,1.3,0 };
	GLfloat light_ambient[] = { 0.1,0.1,0.1,1 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, day_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, night_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);

	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, night_diffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);

	//turn on appropriate lights
	if (night)
	{
		//disable directional light and enable point lights
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);

	}
	else
	{
		//enable directional light and disable point lights
		glEnable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
	}

	//render patty wagon and lights when drive mode is active
	if (drive)
	{
		//render patty wagon
		glPushMatrix();
			glTranslatef(carCamera.getPosition().x, carCamera.getPosition().y, carCamera.getPosition().z);
			glScalef(0.1, 0.1, 0.1);
			glRotatef(carCamera.getDirection(), 0, 1, 0);
			car.render();
			//render headlights
			glPushMatrix();
				glScalef(10, 10, 10);
				GLfloat car_light_pos[] = { 0.5,1,0,1 };
				GLfloat car_light_pos2[] = { -0.5,1,0,1 };
				GLfloat car_diffuse[] = { 2,2,2,1 };
				GLfloat car_light_ambient[] = { 0.1,0.1,0.1,1 };
				GLfloat spot_Direction[] = { 0.0f, 0.0f, 1.0f };
				glLightfv(GL_LIGHT3, GL_AMBIENT, car_light_ambient);
				glLightfv(GL_LIGHT3, GL_DIFFUSE, car_diffuse);
				glLightfv(GL_LIGHT3, GL_POSITION, car_light_pos);
				glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 30);
				glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_Direction);
				glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 20);
				glEnable(GL_LIGHT3);

				glLightfv(GL_LIGHT4, GL_AMBIENT, car_light_ambient);
				glLightfv(GL_LIGHT4, GL_DIFFUSE, car_diffuse);
				glLightfv(GL_LIGHT4, GL_POSITION, car_light_pos2);
				glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 30);
				glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spot_Direction);
				glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 20);
				glEnable(GL_LIGHT4);
			glPopMatrix();
		glPopMatrix();
	}
	else
	{
		//disable headlights
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHT4);
	}
}

void Scene::renderGround()
{
	//render plane of sand
	glBindTexture(GL_TEXTURE_2D, sand);
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(-50, -2, -50);
	for (int o = 0; o < 100; o++)
	{
		for (int i = 0; i < 100; i++)
		{
			proceduralModel.renderQuad();
			glTranslatef(1, 0, 0);
		}
		glTranslatef(-100, 0, 1);
	}
	glPopMatrix();

	//render road
	glBindTexture(GL_TEXTURE_2D, road);
	glPushMatrix();
		glTranslatef(-10, -1.99, 4);
		glScalef(2, 2, 2);
		for (int i = 0; i < 10; i++)
		{
			proceduralModel.renderQuad();
			glTranslatef(1, 0, 0);
		}
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1, -1.99, 2);
		glScalef(2, 2, 2);
		for (int i = 0; i < 2; i++)
		{
			proceduralModel.renderQuad();
			glTranslatef(0, 0, -1);
		}
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-7, -1.99, 2);
		glScalef(2, 2, 2);
		for (int i = 0; i < 2; i++)
		{
			proceduralModel.renderQuad();
			glTranslatef(0, 0, -1);
		}
	glPopMatrix();
	glPushMatrix();
		glTranslatef(5, -1.99, 2);
		glScalef(2, 2, 2);
		for (int i = 0; i < 2; i++)
		{
			proceduralModel.renderQuad();
			glTranslatef(0, 0, -1);
		}
	glPopMatrix();
}

void Scene::renderShadows()
{
	//render day shadows
	if (!night)
	{
		//generate shadow matrix for buildings/plankton (day)
		GLfloat shadow_light_pos[] = { 0,12.5,50,1 };
		shadow.generateShadowMatrix(shadowMatrix, shadow_light_pos, planeVerts);

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		glColor3f(0.1, 0.1, 0.1);
		glPushMatrix();
			glMultMatrixf((GLfloat*)shadowMatrix); //apply shadow tranformation

			//render pineapple shadow
			glPushMatrix();
				glTranslatef(6, -2, 0);
				pineapple.render();
			glPopMatrix();

			//render squidawrd's house shadow
			glPushMatrix();
				glTranslatef(0, -2, 0);
				glScalef(0.4, 0.4, 0.4);
				squidHouse.render();
			glPopMatrix();

			//render patrick's house shadow
			glPushMatrix();
				glTranslatef(-6, -2, 0);
				glScalef(2, 2, 2);
				proceduralModel.renderSemiSphere();
			glPopMatrix();

			//render Krusty krab shadow
			glPushMatrix();
				glTranslatef(12, -2, 5);
				glScalef(0.13, 0.13, 0.13);
				glRotatef(-90, 0, 1, 0);
				krustyKrab.render();
			glPopMatrix();

			//render Plankton shadow
			glPushMatrix();
				glTranslatef(12, -2, -14);
				glRotatef(-30, 0, 1, 0);
				glScalef(0.5, 0.5, 0.5);
				plankton.render();
			glPopMatrix();
	
			//render weenie hut jr shadow
			glPushMatrix();
			glTranslatef(-12, -2, 5);
			glRotatef(90, 0, 1, 0);
			glScalef(0.7, 0.7, 0.7);
			weenie.render();
			glPopMatrix();

			//render weenie hut jr sign shadow
			glPushMatrix();
				glTranslatef(-10, 2.5, 5.5);
				glRotatef(90, 0, 1, 0);
				glRotatef(75, 1, 0, 0);
				glScalef(0.7, 0.7, 0.7);
				glScalef(2, 1.4, 1.4);
				weenieSign.render();
			glPopMatrix();
		glPopMatrix();

		glColor3f(1, 1, 1);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
	}
	else //render night shadows
	{
		//generate shadow matrix for patricks house (night)
		GLfloat shadow_light_pos1[] = { -3,2,0,1 };
		shadow.generateShadowMatrix(shadowMatrix, shadow_light_pos1, planeVerts);

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		glColor3f(0.1, 0.1, 0.1);
		glPushMatrix();
			glMultMatrixf((GLfloat*)shadowMatrix); //apply shadow transformation

			//render patrick's house shadow
			glPushMatrix();
				glTranslatef(-6, -2, 0);
				glScalef(2, 2, 2);
				proceduralModel.renderSemiSphere();
			glPopMatrix();
		glPopMatrix();

		//generate shadow matrix for spongebobs house/weenie hut jr (night)
		GLfloat shadow_light_pos2[] = { -3,5,0,1 };
		shadow.generateShadowMatrix(shadowMatrix, shadow_light_pos2, planeVerts);

		glPushMatrix();
			glMultMatrixf((GLfloat*)shadowMatrix); //apply shadow transformation
			//render spongebobs house shadow
			glPushMatrix();
				glTranslatef(6, -2, 0);
				pineapple.render();
			glPopMatrix();

			//render weenie hut jr shadow
			glPushMatrix();
				glTranslatef(-12, -2, 5);
				glRotatef(90, 0, 1, 0);
				glScalef(0.7, 0.7, 0.7);
				weenie.render();
			glPopMatrix();

			//render weenie hut jr sign shadow
			glPushMatrix();
				glTranslatef(-10, 2.5, 5.5);
				glRotatef(90, 0, 1, 0);
				glRotatef(75, 1, 0, 0);
				glScalef(0.7, 0.7, 0.7);
				glScalef(2, 1.4, 1.4);
				weenieSign.render();
			glPopMatrix();
		glPopMatrix();

		//generate shadow matrix for krusty krab/plankton (night)
		GLfloat shadow_light_pos3[] = { 3,5,0,1 };
		shadow.generateShadowMatrix(shadowMatrix, shadow_light_pos3, planeVerts);

		glPushMatrix();
			glMultMatrixf((GLfloat*)shadowMatrix); //apply shadow transformation 
			//render Krust krab shadow
			glPushMatrix();
				glTranslatef(12, -2, 5);
				glScalef(0.13, 0.13, 0.13);
				glRotatef(-90, 0, 1, 0);
				krustyKrab.render();
			glPopMatrix();
			//render Plankton shadow
			glPushMatrix();
				glTranslatef(12, -2, -14);
				glRotatef(-30, 0, 1, 0);
				glScalef(0.5, 0.5, 0.5);
				plankton.render();
			glPopMatrix();
		glPopMatrix();

		glColor3f(1, 1, 1);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
	}
}

void Scene::renderMirror()
{
	//I could not get this function to work as intended so it was never rendered
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	//render mirror
		glDisable(GL_DEPTH_TEST);
		glPushMatrix();
			glTranslatef(0, 0, 6); //translate for mirror
			glScalef(1, 1, 1); //scale for mirror
			glColor4f(1, 1, 1, 1);
			glBegin(GL_QUADS);
				glVertex3f(0, 0, 0);
				glVertex3f(0, 0, 1);
				glVertex3f(0, 1, 1);
				glVertex3f(0, 1, 0);
			glEnd();
		glPopMatrix();
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glStencilFunc(GL_EQUAL, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

		//render mirror objects
		glPushMatrix();
			glScalef(-1, 1, 1); //scale for all mirror objects
			glPushMatrix();
				glTranslatef(-1, -2.5, 5); //translate for mirror spongebob
				glScalef(1.5, 1.5, 1.5); //scale mirror spongebob
				glRotatef(rotation, 0, 1, 0); //rotate mirror spongebob
				spongebob.render(); //render mirror spongebob
			glPopMatrix();
		glPopMatrix();
		glEnable(GL_BLEND);

		//render regular objects
		glDisable(GL_STENCIL_TEST);
		glPushMatrix();
			glTranslatef(-1, -2.5, 5); //translate for spongebob
			glScalef(1.5, 1.5, 1.5); //scale for spongebob
			glRotatef(rotation, 0, 1, 0); //rotate for spongebob
			spongebob.render(); //render spongebob
		glPopMatrix();
}

void Scene::initialiseOpenGL()
{
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

// Calculates FPS
void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
