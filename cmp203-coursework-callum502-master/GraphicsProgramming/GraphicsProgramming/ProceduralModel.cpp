#include "ProceduralModel.h"
//setup quad vertex arrays
extern float verts[] = { 0.0, 0.0, 0.0,			// Vertex #0  tl
							0.0, 0.0, 1.0,		// Vertex #1  bl
							1.0,  0.0, 1.0,		// Vertex #2  br
							1.0,  0.0, 0.0,		// Vertex #3  tr	
};

extern float norms[] = { 0.0, 1.0, 0.0,		//0
						0.0, 1.0, 0.0,		//1
						0.0, 1.0, 0.0,		//2
						0.0, 1.0, 0.0,		//3
};


extern float texcoords[] = { 0.0, 0.0, 		//0
							0.0, 1.0, 		//1
							1.0, 1.0, 		//2
							1.0, 0.0, 		//3
};

extern GLubyte indices[] = { 0, 1, 2, 3,
};

void ProceduralModel::renderDisc()
{
	//calculate interval
	interval = (2 * M_PI) / segments;
	//render each segment
	for (int i = 0; i < segments; i++)
	{
		//draw triangle
		glBegin(GL_TRIANGLES);
			//set centre vertex
			glNormal3f(0, 0, 1);
			glTexCoord2f(0.5, 0.5);
			glVertex3f(0, 0, 0);

			//set outer vertex
			glNormal3f(0, 0, 1);
			glTexCoord2f((cos(angle) / 2) + 0.5, (sin(angle) / 2) + 0.5);
			glVertex3f(cos(angle), sin(angle), 0);

			//set outer vertex + interval
			glNormal3f(0, 0, 1);
			glTexCoord2f((cos(angle + interval) / 2) + 0.5, (sin(angle + interval) / 2) + 0.5);
			glVertex3f(cos(angle + interval), sin(angle + interval), 0);
			angle += interval;
		glEnd();
	}
	angle = 0; //reset angle
}

void ProceduralModel::renderSphere()
{
	//calculate intervals
	latInterval = (2 * M_PI) / latitude;
	longInterval = M_PI / longitude;
	//render each segment
	for (int i = 0; i < longitude; i++)
	{
		for (int j = latitude; j > 0; j--)
		{
			glBegin(GL_QUADS);
				//set top right vertex
				glTexCoord2f((j * (1 / latitude)) + (1 / latitude), i * (1 / longitude)); 
				glNormal3f(r * cos(latAngle) * sin(longAngle), r * cos(longAngle), r * sin(latAngle) * sin(longAngle));
				glVertex3f(r * cos(latAngle) * sin(longAngle), r * cos(longAngle), r * sin(latAngle) * sin(longAngle));

				//set top left vertex
				glTexCoord2f(j * (1 / latitude), i * (1 / longitude));
				glNormal3f(r * cos(latAngle + latInterval) * sin(longAngle), r * cos(longAngle), r * sin(latAngle + latInterval) * sin(longAngle));
				glVertex3f(r * cos(latAngle + latInterval) * sin(longAngle), r * cos(longAngle), r * sin(latAngle + latInterval) * sin(longAngle));

				//set bottom left vertex
				glTexCoord2f(j * (1 / latitude), (i * (1 / longitude)) + (1 / longitude)); 
				glNormal3f(r * cos(latAngle + latInterval) * sin(longAngle + longInterval), r * cos(longAngle + longInterval), r * sin(latAngle + latInterval) * sin(longAngle + longInterval));
				glVertex3f(r * cos(latAngle + latInterval) * sin(longAngle + longInterval), r * cos(longAngle + longInterval), r * sin(latAngle + latInterval) * sin(longAngle + longInterval));

				//set bottom right vertex
				glTexCoord2f((j * (1 / latitude)) + (1 / latitude), (i * (1 / longitude)) + (1 / longitude));
				glNormal3f(r * cos(latAngle) * sin(longAngle + longInterval), r * cos(longAngle + longInterval), r * sin(latAngle) * sin(longAngle + longInterval));
				glVertex3f(r * cos(latAngle) * sin(longAngle + longInterval), r * cos(longAngle + longInterval), r * sin(latAngle) * sin(longAngle + longInterval));
			glEnd();
			latAngle += latInterval; //add interval
		}
		longAngle += longInterval; //add interval
	}
	latAngle = 0; //reset angles
	longAngle = 0;
}

void ProceduralModel::renderCylinder()
{
	//render bottom disc
	//calculate interval
	interval = (2 * M_PI) / segments;
	for (int i = 0; i < segments; i++)
	{
		glBegin(GL_TRIANGLES);
			//set centre vertex
			glNormal3f(0, 0, 1);
			glTexCoord2f(0.5, 0.5);
			glVertex3f(0, 0, 0);

			//set outer vertex
			glNormal3f(0, 0, 1);
			glTexCoord2f((cos(angle + interval) / 2) + 0.5, (sin(angle + interval) / 2) + 0.5);
			glVertex3f(cos(angle + interval), sin(angle + interval), 0);

			//set outer vertex + inteval
			glNormal3f(0, 0, 1);
			glTexCoord2f((cos(angle) / 2) + 0.5, (sin(angle) / 2) + 0.5);
			glVertex3f(cos(angle), sin(angle), 0);
		glEnd();

		//render quads between discs
		glBegin(GL_QUADS);
			//set bottom left vertex
			glTexCoord2f(i * (1 / segments), 1);
			glNormal3f(cos(angle), sin(angle), 0);
			glVertex3f(cos(angle), sin(angle), 0);

			//set bottom right vertex
			glTexCoord2f(i * (1 / segments) + (1 / segments), 1);
			glNormal3f(cos(angle + interval), sin(angle + interval), 0);
			glVertex3f(cos(angle + interval), sin(angle + interval), 0);

			//set top right vertex
			glTexCoord2f(i * (1 / segments), 0);
			glNormal3f(cos(angle + interval) + (1 / segments), sin(angle + interval), height);
			glVertex3f(cos(angle + interval) + (1 / segments), sin(angle + interval), height);

			//set top left vertex
			glTexCoord2f(i * (1 / segments), 0);
			glNormal3f(cos(angle), sin(angle), height);
			glVertex3f(cos(angle), sin(angle), height);
		glEnd();

		//render top disc
		glBegin(GL_TRIANGLES);
			//set centre vertex
			glNormal3f(0, 0, 1);
			glTexCoord2f(0.5, 0.5);
			glVertex3f(0, 0, height);

			//set outer vertex
			glNormal3f(0, 0, 1);
			glTexCoord2f((cos(angle) / 2) + 0.5, (sin(angle) / 2) + 0.5);
			glVertex3f(cos(angle), sin(angle), height);
			
			//set outer vertex + interval
			glNormal3f(0, 0, 1);
			glTexCoord2f((cos(angle + interval) / 2) + 0.5, (sin(angle + interval) / 2) + 0.5);
			glVertex3f(cos(angle + interval), sin(angle + interval), height);
		glEnd();
		angle += interval; //increase interval
	}
	angle = 0; //reset angle
}

void ProceduralModel::renderSemiSphere()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//calculate intervals
	latInterval = (2 * M_PI) / latitude;
	longInterval = M_PI / longitude;
	//render each segment except bottom half
	for (int i = 0; i < longitude/2; i++)
	{
		for (int j = latitude; j > 0; j--)
		{
			glBegin(GL_QUADS);
				//set top right vertex
				glTexCoord2f((j * (1 / latitude)) + (1 / latitude), i * (1 / longitude));
				glNormal3f(r * cos(latAngle) * sin(longAngle), r * cos(longAngle), r * sin(latAngle) * sin(longAngle));
				glVertex3f(r * cos(latAngle) * sin(longAngle), r * cos(longAngle), r * sin(latAngle) * sin(longAngle));

				//set top left vertex
				glTexCoord2f(j * (1 / latitude), i * (1 / longitude));
				glNormal3f(r * cos(latAngle + latInterval) * sin(longAngle), r * cos(longAngle), r * sin(latAngle + latInterval) * sin(longAngle));
				glVertex3f(r * cos(latAngle + latInterval) * sin(longAngle), r * cos(longAngle), r * sin(latAngle + latInterval) * sin(longAngle));

				//set bottom left vertex
				glTexCoord2f(j * (1 / latitude), (i * (1 / longitude)) + (1 / longitude));
				glNormal3f(r * cos(latAngle + latInterval) * sin(longAngle + longInterval), r * cos(longAngle + longInterval), r * sin(latAngle + latInterval) * sin(longAngle + longInterval));
				glVertex3f(r * cos(latAngle + latInterval) * sin(longAngle + longInterval), r * cos(longAngle + longInterval), r * sin(latAngle + latInterval) * sin(longAngle + longInterval));

				//set bottom right vertex
				glTexCoord2f((j * (1 / latitude)) + (1 / latitude), (i * (1 / longitude)) + (1 / longitude));
				glNormal3f(r * cos(latAngle) * sin(longAngle + longInterval), r * cos(longAngle + longInterval), r * sin(latAngle) * sin(longAngle + longInterval));
				glVertex3f(r * cos(latAngle) * sin(longAngle + longInterval), r * cos(longAngle + longInterval), r * sin(latAngle) * sin(longAngle + longInterval));
			glEnd();
			latAngle += latInterval; //add interval
		}
		longAngle += longInterval; //add interval
	}
	latAngle = 0; //reset angles
	longAngle = 0;
}

void ProceduralModel::renderQuad()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

	//draw quad using vertex arrays
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_INDEX_ARRAY);

}