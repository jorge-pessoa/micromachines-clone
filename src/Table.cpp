//
//  Table.cpp
//  CGproj
//

#include "Table.h"
#include "Logger.h"

Table::Table()
{
}

Table::Table(GLdouble posx, GLdouble posy, GLdouble posz,
	GLdouble rotangle, GLdouble rotx, GLdouble roty, GLdouble rotz,
	GLdouble scalex, GLdouble scaley, GLdouble scalez)
	:StaticObject(posx, posy, posz,
		rotangle, rotx, roty, rotz,
		scalex, scaley, scalez)
{

	GLfloat amb[4] = { 0.15f,0.012f,0.0f,1.0f },
		diff[4] = { 0.12f,0.08f,0.0f,1.0f },
		spec[4] = { 0.0f,0.0f,0.0f,1.0f },
		shine = 80.0f;

	// ---------------------- usar se pretender ter a cor original da textura --------------
	/*GLfloat amb[4] = { 0.15f,0.012f,0.0f,1.0f },
		diff[4] = { 1.0f,1.0f,1.0f,1.0f },
		spec[4] = { 0.0f,0.0f,0.0f,1.0f },
		shine = 0.0f;*/

	setMaterial(amb, diff, spec, shine);

	_cube_size = 2;


	_texture.chooseImage(TEXTURE_PATH);
	_texture.generateTexture();

	if (_texture.isNull())
		printf("ERROR LOADING TEXTURE\n");
}
Table::~Table()
{
}

void Table::render()
{   
	// ------------------ Mesa do Vera (BAD) --------------------
	//glPushMatrix();
    //glTranslatef(-75, -_cube_size*1.5, -75);
	/*for (int u = -75; u < 75; u = u + _cube_size)
	{
		glTranslatef(_cube_size, 0, 0);
		for (int i = -75; i < 75; i = i + _cube_size)
		{
			glTranslatef(0, 0, _cube_size);
			SolidCubeTable(_cube_size);

			//glVertex3d(i*_cube_size / 2, 1.0, i*_cube_size / 2);

		}
		glTranslatef(0, 0, -150);
	}

	glPopMatrix();*/


	// --------------- Mesa do Jorge ------------------
	
	_texture.bindTexture();



	glColor3f(0.30, 0.15, 0.0);

	glPushMatrix();
	
	double size = 0.5;
	float quads = 150 / size;
	float textx = 1 / quads;
	float textz = 1 / quads;

	glTranslatef(-75, -2, -75);
	for (int j = 0; j < quads; j++) {
		glTranslatef(0, 0, size);
		glBegin(GL_QUAD_STRIP);
		glNormal3d(0, 1, 0);

		glTexCoord2f(0, textz * j);
		glVertex3d(0, 0, size);
		
		glTexCoord2f(0, textz * j + textz);
		glVertex3d(0, 0, 0);
		
			for (int i = 0; i < quads; i++) {
				
				glTexCoord2f(textx * i, textz * j + textz);
				glVertex3d(size * i, 0, size);
			
				glTexCoord2f(textx * i, textz * j );
				glVertex3d(size* i, 0, 0);
			
		}
		glEnd();
		
		
	}
	glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
}


void Table::update(GLdouble delta_t) {
	//_position.set(_position._x - delta_t / 200.0, _position._y , _position._z - delta_t / 200.0);
}

