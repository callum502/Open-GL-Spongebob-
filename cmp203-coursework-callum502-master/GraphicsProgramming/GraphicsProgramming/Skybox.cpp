#include "Skybox.h"
void Skybox::renderSkybox(float x, float y, float z)
{
	glPushMatrix();
		glTranslatef(x, y, z + 1); //to cam camera.getpos
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);

		//front face
		glBegin(GL_QUADS);
			glTexCoord2f(0.25f, 0.25f);
			glVertex3f(-0.5, 0.5, -1.5); //tl
			glTexCoord2f(0.25f, 0.5f);
			glVertex3f(-0.5, -0.5, -1.5); //bl
			glTexCoord2f(0.5f, 0.5f);
			glVertex3f(0.5, -0.5, -1.5); //br
			glTexCoord2f(0.5f, 0.25f);
			glVertex3f(0.5, 0.5, -1.5); //tr
		glEnd();

		//right face
		glBegin(GL_QUADS);
			glTexCoord2f(0.5f, 0.25f);
			glVertex3f(0.5, 0.5, -1.5); //tl
			glTexCoord2f(0.5f, 0.5f);
			glVertex3f(0.5, -0.5, -1.5); //bl
			glTexCoord2f(0.75f, 0.5f);
			glVertex3f(0.5, -0.5, -0.5); //br
			glTexCoord2f(0.75f, 0.25f);
			glVertex3f(0.5, 0.5, -0.5); //tr
		glEnd();

		//left face
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.25f);
			glVertex3f(-0.5, 0.5, -0.5); //tl
			glTexCoord2f(0.0f, 0.5f);
			glVertex3f(-0.5, -0.5, -0.5); //bl
			glTexCoord2f(0.25f, 0.5f);
			glVertex3f(-0.5, -0.5, -1.5); //br
			glTexCoord2f(0.25f, 0.25f);
			glVertex3f(-0.5, 0.5, -1.5); //tr
		glEnd();

		//bottom face
		glBegin(GL_QUADS);
			glTexCoord2f(0.25f, 0.5f);
			glVertex3f(-0.5, -0.5, -1.5); //tl
			glTexCoord2f(0.25f, 0.75f);
			glVertex3f(-0.5, -0.5, -0.5); //bl
			glTexCoord2f(0.5f, 0.75f);
			glVertex3f(0.5, -0.5, -0.5); //br
			glTexCoord2f(0.5f, 0.5f);
			glVertex3f(0.5, -0.5, -1.5); //tr
		glEnd();

		//top face
		glBegin(GL_QUADS);
			glTexCoord2f(0.25f, 0.0f);
			glVertex3f(-0.5, 0.5, -0.5); //tl
			glTexCoord2f(0.25f, 0.25f);
			glVertex3f(-0.5, 0.5, -1.5); //bl
			glTexCoord2f(0.5f, 0.25f);
			glVertex3f(0.5, 0.5, -1.5); //br
			glTexCoord2f(0.5f, 0.0f);
			glVertex3f(0.5, 0.5, -0.5); //tr
		glEnd();

		//back face
		glBegin(GL_QUADS);
			glTexCoord2f(0.75f, 0.25f);
			glVertex3f(0.5, 0.5, -0.5); //tl
			glTexCoord2f(0.75f, 0.5f);
			glVertex3f(0.5, -0.5, -0.5); //bl
			glTexCoord2f(1.0f, 0.5f);
			glVertex3f(-0.5, -0.5, -0.5); //br
			glTexCoord2f(1.0f, 0.25f);
			glVertex3f(-0.5, 0.5, -0.5); //tr
		glEnd();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}